#include <stdio.h>

int main(int argc, char const *argv[])
{
    // 打开文件
    FILE * ioFile  = fopen("user.txt","r");
    if (ioFile == NULL)
    {
        printf("不能用只读模式打开不存在的文件\n");
    }

    /**
     * FILE *__restrict __stream: 打开的文件
     * const char *__restrict __format: 带有格式化的字符串 (固定格式接收)
     * ...可变参数: 填写格式化的字符串 (接收数据提前声明的变量)
     * return: 成功匹配到的参数的个数 如果匹配失败返回0  报错或者文件结束EOF
     *  int fscanf (FILE *__restrict __stream,const char *__restrict __format, ...)
    */

    char name[50];
    int age;
    char wife[50];
    int scnafR ;
    

    while ((scnafR = fscanf(ioFile,"%s %d %s",name,&age,wife)) != EOF)
    {
        printf("成功匹配到的参数有%d个\n",scnafR);
        printf("%s在%d岁的时候爱上了%s\n",name,age,wife);
    }
    


    // 关闭文件
    int closeR = fclose(ioFile);
    if (closeR == EOF)
    {
        printf("关闭文件失败\n");
    }
    
    
    return 0;
}
