#include <stdio.h>

// 在x的作用域结束时自动执行指定的方法，入参是x的地址
#define _cleanup_(x) __attribute__((__cleanup__(x)))

void cleanup_function(int *mr_varibale)
{
    printf("Oh, I dead at %d\n", *mr_varibale);
}

void variable_life()
{
    _cleanup_(cleanup_function) int mr_variable = 100;
}

int main()
{
    variable_life();
    return 0;
}

