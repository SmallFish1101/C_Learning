/*
 * swap_double.c
 * 第18课 练习一：用指针交换两个浮点数
 *
 * 功能：安全读取两个 double 类型数值，
 *       调用 swap_double 函数通过指针交换它们的值，
 *       输出交换前后的结果。
 */

#include <stdio.h>   // printf, fgets, sscanf
#include <stdlib.h>  // exit
#include <string.h>  // strlen（用于去除换行）

/*
 * 函数原型
 */
void swap_double(double *a, double *b);
double read_double(const char *prompt);

int main(void)
{
    printf("=== Swap Double using Pointers ===\n\n");

    // 1. 安全读取两个浮点数
    double x = read_double("Enter first number (x): ");
    double y = read_double("Enter second number (y): ");

    // 2. 打印交换前的值
    printf("\nBefore swap: x = %.2f, y = %.2f\n", x, y);

    // 3. 调用交换函数，传入 x 和 y 的地址
    swap_double(&x, &y);

    // 4. 打印交换后的值，验证结果
    printf("After swap:  x = %.2f, y = %.2f\n", x, y);

    return 0;
}

/*
 * swap_double:
 *   交换两个 double 变量的值（通过指针操作）。
 *   a: 指向第一个变量的指针
 *   b: 指向第二个变量的指针
 */
void swap_double(double *a, double *b)
{
    // 临时变量存储 *a 的值
    double temp = *a;

    // 将 *b 的值赋给 *a
    *a = *b;

    // 将 temp（原来 *a 的值）赋给 *b
    *b = temp;
}

/*
 * read_double:
 *   安全读取一个 double 值（复用第10课的标准模板）。
 *   prompt: 提示信息
 *   return: 用户输入的合法浮点数
 */
double read_double(const char *prompt)
{
    char line[100];   // 输入缓冲区

    while (1)
    {
        printf("%s", prompt);

        // fgets 读取一行，EOF 检查
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            printf("\nEnd of input.\n");
            exit(0);
        }

        double value;
        int pos = 0;   // 解析位置

        // 尝试从字符串中解析一个 double（%lf 是 double 的格式）
        int matched = sscanf(line, "%lf %n", &value, &pos);

        // 检查1：是否成功匹配一个浮点数
        if (matched != 1)
        {
            printf("  ERROR: Please enter a valid number.\n");
            continue;
        }

        // 检查2：行内是否有多余的非空白字符
        if (line[pos] != '\0')
        {
            printf("  ERROR: Extra characters after number.\n");
            continue;
        }

        // 全部通过，返回有效值
        return value;
    }
}