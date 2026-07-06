#include<stdio.h>

int main(void){
    // 1. 打印各基本类型的大小
    printf("=== 基本数据类型大小 (Byte) ===\n");
    printf("Size of char: %zu bytes\n", sizeof(char));
    printf("Size of short: %zu bytes\n", sizeof(short));
    printf("Size of int: %zu bytes\n", sizeof(int));
    printf("Size of long: %zu bytes\n", sizeof(long));
    printf("Size of long long: %zu bytes\n", sizeof(long long));
    printf("Size of float: %zu bytes\n", sizeof(float));
    printf("Size of double: %zu bytes\n", sizeof(double));
    printf("Size of long double: %zu bytes\n", sizeof(long double));
    
    // 2. 观察变量地址
    printf("\n=== 变量地址与大小 ===\n");
    int a = 0x12345678;
    char b = 'B';
    double c = 3.14;
    printf("Address of a (int)    : %p, size: %zu\n", (void*)&a, sizeof a);
    printf("Address of b (char)   : %p, size: %zu\n", (void*)&b, sizeof b);
    printf("Address of c (double) : %p, size: %zu\n", (void*)&c, sizeof c);

     // 3. 额外体验：指针自身的大小（与系统位数相关）
    int *p = &a;
    printf("\nSize of pointer (int*) : %zu\n", sizeof(p));

    
    return 0;
}

