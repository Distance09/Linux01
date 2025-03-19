#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    // 打开文件
    int fd = open("io123.txt",O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer[1024]; //用于存放读取的数据
    ssize_t bytes_read;
    /**
     * int __fd: 文件描述符
     * void *__buf: 存放数据
     * size_t __nbytes: 读取数据的长度
     * return: ssize_t -> long int : 读取到数据的字节长度 成功大于0  失败-1
     * ssize_t read (int __fd, void *__buf, size_t __nbytes)
    */
    while ((bytes_read = read(fd,buffer,sizeof(buffer))) > 0)
    {
        // 文件描述符类型的 stdin -> 0
        // stdout -> 1  stderr -> 2
        /**
         * int __fd: 文件描述符
         * const void *__buf: 要写出的数据
         * size_t __n: 写出的长度
         * return: 成功返回写出数据的长度 失败返回-1
         * ssize_t write (int __fd, const void *__buf, size_t __n)
        */
        write(STDOUT_FILENO,buffer,bytes_read);
    }
    
    if (bytes_read == -1)
    {
        perror("read");
        /**
         * 关闭打开的文件描述符
         * return: 成功返回0 失败返回-1
        */
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    close(fd);
 
    return 0;
}
