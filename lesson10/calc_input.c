/*
 * calc_input.c
 * 第10课 作业三：简单计算器 —— 使用安全输入模式
 *
 * 功能：读取两个浮点数和一个运算符，执行 + - * / 运算，
 *       处理除以零、无效运算符、格式错误等异常。
 */

#include <stdio.h>   // printf, fgets, sscanf
#include <stdlib.h>  // exit
#include <math.h>    // fabs    （用于判断除数是否接近零）
#include <string.h>  // strlen  （用于检查字符串长度）
#include <ctype.h>   // isspace （用于跳过空白，本作业未使用但保留）

/*
 * read_double:
 *   安全读取一个 double 类型的浮点数。
 *   prompt: 提示信息（如 "Enter first number"）。
 *   return: 用户输入的合法浮点数。
 */
double read_double(const char *prompt)
{
    char line[100];   // 输入缓冲区

    while (1) {
        printf("%s: ", prompt);

        // fgets 读取一整行（最多 99 个字符）
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nEnd of input detected.\n");
            exit(0);   // 遇到 EOF，退出程序
        }

        double value;
        int pos = 0;   // 记录 sscanf 解析消耗的字符数

        // sscanf 尝试从 line 中解析一个 double
        // %lf 是 double 的格式控制符（l = long，f = float）
        int matched = sscanf(line, "%lf %n", &value, &pos);

        // 检查 1：是否成功匹配到一个浮点数
        if (matched != 1) {
            printf("  ERROR: Please enter a valid number.\n");
            continue;   // 重新输入
        }

        // 检查 2：行内是否有多余的非空白字符（如 "3.14abc"）
        if (line[pos] != '\0') {
            printf("  ERROR: Extra characters after number.\n");
            continue;
        }

        // 输入合法，返回结果
        return value;
    }
}

/*
 * read_operator:
 *   安全读取一个运算符（+ - * /）。
 *   return: 合法的运算符字符。
 */
char read_operator(void)
{
    char line[100];   // 输入缓冲区

    while (1) {
        printf("Enter operator (+, -, *, /): ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nEnd of input detected.\n");
            exit(0);
        }

        // 去掉 fgets 保留的换行符
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';   // 把换行符替换为 '\0'
            len--;                   // 长度减 1
        }

        // 检查 1：输入不能为空
        if (len == 0) {
            printf("  ERROR: Operator cannot be empty.\n");
            continue;
        }

        // 检查 2：输入长度只能为 1（恰好一个字符）
        if (len != 1) {
            printf("  ERROR: Please enter exactly one character (+, -, *, /).\n");
            continue;
        }

        // 检查 3：字符必须是四种运算符之一
        char op = line[0];
        if (op == '+' || op == '-' || op == '*' || op == '/') {
            return op;   // 合法运算符
        } else {
            printf("  ERROR: '%c' is not a valid operator. Use +, -, *, or /.\n", op);
            continue;
        }
    }
}

/*
 * ask_continue:
 *   询问用户是否继续计算。
 *   return: 1 表示继续，0 表示退出。
 */
int ask_continue(void)
{
    char line[100];

    while (1) {
        printf("\nContinue? (y/n): ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            return 0;   // EOF，默认退出
        }

        // 去掉换行符
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        // 只接受恰好一个字符 'y' 或 'n'
        if (len == 1) {
            if (line[0] == 'y' || line[0] == 'Y') return 1;
            if (line[0] == 'n' || line[0] == 'N') return 0;
        }

        printf("  Please enter 'y' or 'n'.\n");
    }
}

int main(void)
{
    printf("=== Simple Calculator (Safe Input) ===\n");
    printf("Supports: +  -  *  /\n\n");

    int continue_calc = 1;   // 控制外层循环

    while (continue_calc) {
        // 1. 读取第一个操作数
        double num1 = read_double("Enter first number");

        // 2. 读取第二个操作数
        double num2 = read_double("Enter second number");

        // 3. 读取运算符
        char op = read_operator();

        // 4. 执行运算并输出结果
        double result;
        int valid = 1;   // 标志：运算是否有效

        // 使用 switch 根据运算符分派（第11课会系统学习 switch）
        switch (op) {
            case '+':
                result = num1 + num2;
                break;

            case '-':
                result = num1 - num2;
                break;

            case '*':
                result = num1 * num2;
                break;

            case '/':
                // 检查除数是否接近零（使用 fabs 避免浮点精度问题）
                // fabs(num2) 返回 num2 的绝对值
                // 1e-9 是一个非常小的数（0.000000001）
                if (fabs(num2) < 1e-9) {
                    printf("\n  ERROR: Division by zero is not allowed.\n");
                    valid = 0;   // 标记无效
                } else {
                    result = num1 / num2;
                }
                break;

            default:
                // 这不应该发生，因为 read_operator 已经保证了运算符合法
                printf("\n  ERROR: Unknown operator.\n");
                valid = 0;
                break;
        }

        // 5. 如果运算有效，打印结果
        if (valid) {
            // %g 会自动选择 %f 或 %e 中最紧凑的格式
            // %.10g 表示最多保留 10 位有效数字
            printf("\n  Result: %g %c %g = %.10g\n", num1, op, num2, result);
        }

        // 6. 询问是否继续
        continue_calc = ask_continue();
    }

    printf("\nGoodbye!\n");
    return 0;
}