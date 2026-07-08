#include<stdio.h>
#include<stdint.h>
int main(void)
{
    // 1. 整型提升：char 先转为 int 再运算
    char a = 100;
    char b = 50;
    char c = a + b;          // a + b 结果为 150 (int)，截断为 char
    printf("char + char = %d\n", c);
    // 2. 有符号与无符号混合：int + unsigned int
    int si = -5;
    unsigned int ui = 10;
    // 按照规则，int 转为 unsigned int 再相加
    // -5 转为 unsigned int 会变成一个很大的正数
    unsigned int result = si + ui;
    printf("signed + unsigned = %u\n", result); // 输出可能是 5 或者更大的数，取决于实现
    // 为什么？因为 -5 转换为 unsigned int 是 UINT_MAX - 4，加 10 后回绕
    // 3. 浮点与整数混合
    float f = 5.5f;
    int i = 2;
    float sum = f + i;       // i 自动转为 float
    printf("float + int = %f\n", sum);
    return 0;
}