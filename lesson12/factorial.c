/*
 * factorial.c
 * 第12课 练习一：计算阶乘 (n!)
 *
 * 功能：安全读取一个正整数 n (1~20)，计算并输出 n!。
 *       使用 unsigned long long 类型存储结果，
 *       并在乘法前检测溢出。
 */

#include <stdio.h>    // printf, fgets, sscanf
#include <stdlib.h>   // exit
#include <string.h>   // strlen (用于去除换行符，但本函数未使用)
#include <limits.h>   // ULLONG_MAX

/*
 * read_positive_int:
 *   安全读取一个正整数（≥1），输入不合法或超出范围则重试。
 *   由于阶乘增长极快，此处限制 n 不超过 20，
 *   否则 unsigned long long 会溢出。
 *
 *   return: 用户输入的合法整数 (1~20)
 */
int read_positive_int(void)
{
    char line[100];   // 输入缓冲区

    while (1) {
        printf("Enter a positive integer (1-20) to calculate its factorial: ");

        // 读取一整行
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nEnd of input.\n");
            exit(0);   // 遇到 EOF 时退出
        }

        int n;
        int pos = 0;   // 记录 sscanf 解析停止的位置

        // 尝试从 line 中解析整数
        // %d 读取整数，%n 记下消耗的字符数
        int matched = sscanf(line, "%d %n", &n, &pos);

        // 检查 1：必须成功匹配一个整数
        if (matched != 1) {
            printf("  ERROR: Please enter a valid integer.\n");
            continue;
        }

        // 检查 2：行内不能有残余字符（如 "5abc"）
        if (line[pos] != '\0') {
            printf("  ERROR: Extra characters after number.\n");
            continue;
        }

        // 检查 3：必须在 1~20 之间（20! 不溢出，21! 会溢出）
        if (n < 1 || n > 20) {
            printf("  ERROR: Number must be between 1 and 20 (otherwise overflow).\n");
            continue;
        }

        return n;   // 输入合法
    }
}

/*
 * compute_factorial:
 *   计算 n 的阶乘，并检测溢出。
 *   参数 n: 1~20 的整数。
 *   参数 out_result: 输出结果的指针（存储计算结果）。
 *   返回值: 1 表示计算成功，0 表示溢出。
 */
int compute_factorial(int n, unsigned long long *out_result)
{
    unsigned long long result = 1;   // 初始值 1

    // for 循环从 1 乘到 n
    for (int i = 1; i <= n; i++) {
        // 检查乘法是否会溢出：result * i > ULLONG_MAX
        // 等价于 result > ULLONG_MAX / i
        if (result > ULLONG_MAX / i) {
            return 0;   // 溢出
        }
        result *= i;    // 安全相乘
    }

    *out_result = result;
    return 1;          // 成功
}

int main(void)
{
    printf("=== Factorial Calculator ===\n\n");

    int n = read_positive_int();   // 获取合法输入 n (1~20)

    unsigned long long factorial;
    int success = compute_factorial(n, &factorial);

    if (success) {
        // %llu 打印 unsigned long long
        printf("\n  %d! = %llu\n", n, factorial);
    } else {
        printf("\n  Overflow: %d! is too large to compute with unsigned long long.\n", n);
    }

    return 0;
}