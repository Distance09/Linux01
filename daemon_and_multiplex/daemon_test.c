#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <syslog.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

pid_t pid;

int is_shutdown = 0;

void signal_handler(int sig)
{
    switch (sig)
    {
    case SIGHUP:
        syslog(LOG_WARNING, "收到SIGHUP信号...");
        break;
    case SIGTERM:
        syslog(LOG_NOTICE, "接收到终止信号，准备退出守护进程...");
        syslog(LOG_NOTICE, "向子进程发送SIGTERM信号...");
        is_shutdown = 1;
        kill(pid, SIGTERM);
        break;
    default:
        syslog(LOG_INFO, "Received unhandled signal");
    }
}

void my_daemonize()
{
    pid_t pid;

    // 先fork创建两个进程
    pid = fork();

    if (pid < 0)
        exit(EXIT_FAILURE);

    // 马上关闭调父进程
    // 当前进程会变为孤儿进程  挂到祖先
    if (pid > 0)
        exit(EXIT_SUCCESS);
    // 设置新的会话ID -> 摆脱和当前窗口的联系
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    // 处理 SIGHUP、SIGTERM 信号
    signal(SIGHUP, signal_handler);
    signal(SIGTERM, signal_handler);
    
    // 再次fork
    pid = fork();

    if (pid < 0)
        exit(EXIT_FAILURE);

    // 再次退出父进程 -> 当前不再是会话的领导  永远不会受到窗口的影响
    if (pid > 0)
        exit(EXIT_SUCCESS);

    // 重置umask
    umask(0);

    // 将工作目录切换为根目录
    chdir("/");

    // 关闭所有打开的文件描述符
    for (int x = 0; x <= sysconf(_SC_OPEN_MAX); x++)
    {
        close(x);
    }
    // 开启系统日志
    openlog("this is our daemonize process: ", LOG_PID, LOG_DAEMON);
}

int main()
{
    // 初始化守护进程
    my_daemonize();

    while (1)
    {
        pid = fork();

        if (pid > 0)
        {
            syslog(LOG_INFO, "守护进程正在监听服务端进程...");
            waitpid(-1, NULL, 0);
            if (is_shutdown) {
                syslog(LOG_NOTICE, "子进程已被回收，即将关闭syslog连接，守护进程退出");
                closelog();
                exit(EXIT_SUCCESS);
            }
            syslog(LOG_ERR, "服务端进程终止，3s后重启...");
            sleep(3);
        }
        else if (pid == 0)
        {
            syslog(LOG_INFO, "子进程fork成功");
            syslog(LOG_INFO, "启动服务端进程");

            char *path = "/home/atguigu/daemon_and_multiplex/tcp_server";
            char *argv[] = {"my_tcp_server", NULL};
            errno = 0;
            execve(path, argv, NULL);

            char buf[1024];
            sprintf(buf, "errno: %d", errno);
            syslog(LOG_ERR, "%s", buf);

            syslog(LOG_ERR, "服务端进程启动失败");
            exit(EXIT_FAILURE);
        }
        else
        {
            syslog(LOG_ERR, "子进程fork失败");
        }
    }
    
    return EXIT_SUCCESS;
}