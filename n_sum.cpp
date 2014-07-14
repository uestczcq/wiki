/*********************************************************
 *  http://www.cnblogs.com/lanxuezaipiao/p/3544963.html  *
 *  面试题之发散思维能力：如何用非常规方法求1+2+···+n
 *题目：求1+2+···+n，要求不能使用乘除法、for、while、if、
 * else、switch、case等关键字及条件判断语句（A?B:C）。
 * 
 *递归角度:一个函数充当原递归函数中递归的角色，另一个函数处理递归终止的情况，我们需要做的就是在两个函数里二选一。从二选一我们很自然的想到布尔变量，比如值为true（1）的时候调用第一个函数，值为false（0）的时候调用第二个函数
 *********************************************************/
#include <stdio.h>

typedef unsigned int (*fun)(unsigned int);

unsigned int sum_terminator(unsigned int n)
{
    return 0;
}

unsigned int sum_recursion(unsigned int n)
{
    fun f[2] = {sum_terminator, sum_recursion};
    return f[!!n](n-1) + n;
}

int main(int argc, char *argv[])
{
    unsigned int n;
    while(scanf("%d",&n))
    {
        printf("num:%d sum is:%d\n", n, sum_recursion(n));
    }
    return 0;
}
