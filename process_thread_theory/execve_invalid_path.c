#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char *argv[] = {"/usr/bin/ping", "-c", "10", "baidu.com", NULL};
    int val = 100;
    // 环境变量可以不传
    char *envp[] = {NULL};
    int re = execve(argv[0], argv, envp);
    if (re == -1)
    {
        perror("execve");
        return -1;
    }

    return 0;
}