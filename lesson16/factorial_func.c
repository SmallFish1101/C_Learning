/*
 * factorial_func.c
 * 第16课 练习一：阶乘函数
 *
 * 功能：安全读取整数 n (0~20)，调用函数计算 n!，
 *       并在乘法前检测溢出。所有逻辑被封装为独立函数。
 */

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
/* ---------- 函数原型 ---------- */
// 计算 n!，若溢出则返回 0
unsigned long long factorial(int n);
int read_positive_int(void);

/* ---------- 主函数 ---------- */
int main(void) {
    printf("=== Factorial Function ===\n\n");
    int n = read_positive_int();
    unsigned long long result = factorial(n);
    if (result == 0 && n > 0) {
        // 若 n>0 却得到 0，说明溢出或输入非法
        if(n>20){
            printf("\n%d! is too large (overflow) for unsigned long long.\n", n);
        }
        else{
            printf("\nInvalid input or overflow occurred.\n");
        }
    }
    else {
        printf("\n%d! = %llu\n", n, result);
    }
    return 0;
}
/* ---------- 函数定义 ---------- */
/*
 * factorial:
 *   计算 n 的阶乘，带有溢出检测。
 *   参数 n: 非负整数
 *   返回值: n! 的结果，若输入非法(n<0)或溢出返回 0
 */
unsigned long long factorial(int n)
{
    if (n < 0) return 0;           // 非法输入
    unsigned long long result = 1; // 0! = 1
    for (int i = 2; i <= n; i++) {
        // 溢出检测：result * i > ULLONG_MAX
        // 等价于 result > ULLONG_MAX / i
        if (result > ULLONG_MAX / i) {
            return 0;               // 溢出，返回 0 表示错误
        }
        result *= i;
    }
    return result;
}
/*
 * read_positive_int:
 *   安全读取 0~20 之间的整数，用于阶乘输入。
 *   返回值: 用户输入的合法整数
 */
int read_positive_int(void)
{
    char line[100];
    while (1) {
        printf("Enter a positive integer (0-20): ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nEnd of input.\n");
            exit(0);
        }
        int value;
        int pos = 0;
        int matches = sscanf(line, "%d %n", &value, &pos);
        if (matches != 1 || line[pos] != '\0') {
            printf("  ERROR: Please enter an integer.\n");
            continue;
        }
        if (value < 0 || value > 20) {
            printf("  ERROR: Number must be between 0 and 20 (otherwise overflow).\n");
            continue;
        }
        return value;
    }
}