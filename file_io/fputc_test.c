#include <stdio.h>

int main(int argc, char const *argv[])
{
    /**
     * char *__restrict __filename: 字符串表示要打开的文件名称
     * const char *__restrict __modes: 访问模式
     *      (1) r: 只读模式 如果没有文件报错
     *      (2) w: 只写模式 如果文件存在清空文件 如果不存在创建新文件
     *      (3) a: 只追加写模式 如果文件存在末尾追加写 如果不存在创建新文件
     *      (4) r+: 读写模式 文件必须存在 写入是从头一个一个覆盖
     *      (5) w+: 读写模式 如果文件存在清空文件 如果不存在创建新文件 
     *      (6) a+: 读追加写模式 如果文件存在末尾追加写 如果不存在创建新文件
     * return: FILE * 结构体指针 表示一个文件
     *          报错返回NULL
     * FILE *fopen (const char *__restrict __filename,
		    const char *__restrict __modes)
    */
    char *filename = "io.txt";
    FILE * ioFile =  fopen(filename,"r");
    if (ioFile == NULL)
    {
        printf("failed 打开文件失败\n");
    }else{
        printf("success 打开文件成功\n");
    }

    /**
     * 读写权限记录在fopen方法中的参数
     * int __c: ASCII码对应的char
     * FILE *__stream: 打开的一个文件
     * return: 成功返回的char 失败返回EOF
     * int fputc (int __c, FILE *__stream);
    */
    int put_result = fputc(97,ioFile);
    if (put_result == EOF)
    {
        printf("写入文件失败\n");
    }else {
        printf("写入%c成功\n",put_result);
    }
    

    /**FILE *__stream: 需要关闭的文件
     * return: 成功返回0 失败返回EOF(负数) 通常关闭文件失败会直接报错
     * int fclose (FILE *__stream)
    */
    int result =  fclose(ioFile);
    if (result == EOF)
    {
        printf("关闭文件失败\n");
    }else if (result== 0)
    {
        printf("关闭文件成功\n");
    }
    
    
    return 0;
}
