/*
 * calc_funcptr.c
 * 第31课 练习一：用函数指针数组实现命令行计算器
 *
 * 功能：用户输入 "整数 运算符 整数"（如 "10 + 5"），
 *       程序通过函数指针数组调用对应运算并输出结果。
 *       演示了 typedef 简化函数指针声明、函数指针数组、
 *       以及"新增运算只需添加条目"的灵活设计。
 */

#include <stdio.h>    // printf, fgets, sscanf
#include <stdlib.h>   // exit
#include <string.h>   // strlen
#include <stdbool.h>  // bool, true, false

// ========== 1. 定义函数指针类型 ==========
/*
 * ArithOp:
 *   指向 "接受两个 int，返回 int" 的函数的指针类型。
 *   使用 typedef 后，声明函数指针变量或数组就像用普通类型一样。
 */
typedef int (*ArithOp)(int, int);

// ========== 2. 实现各运算函数 ==========
/*
 * 每个函数的签名都必须与 ArithOp 完全匹配：
 *   参数: (int, int)
 *   返回: int
 */

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mul(int a, int b) {
    return a * b;
}

/*
 * div_int:
 *   整数除法。若除数为 0，打印错误并返回 0。
 *   （实际工程中更推荐用 bool 返回值 + 指针传出结果，
 *    但为了保持函数签名统一以便放入函数指针数组，
 *    这里采用简单处理。）
 */
int div_int(int a, int b) {
    if (b == 0) {
        printf("  Error: Division by zero. Returning 0.\n");
        return 0;
    }
    return a / b;
}

/*
 * mod:
 *   取模运算。额外添加此函数展示"新增运算只需加一个函数和对应条目"。
 */
int mod(int a, int b) {
    if (b == 0) {
        printf("  Error: Modulo by zero. Returning 0.\n");
        return 0;
    }
    return a % b;
}

// ========== 3. 主函数 ==========
int main(void)
{
    printf("=== Calculator using Function Pointer Array ===\n");
    printf("Supported operators: +  -  *  /  %%\n");
    printf("Enter expression (e.g., 10 + 5): ");

    // ---- 安全输入：读取整行 ----
    char line[100];
    if (fgets(line, sizeof(line), stdin) == NULL) {
        printf("\nEnd of input.\n");
        return 0;
    }

    // ---- 解析三个部分：左操作数、运算符、右操作数 ----
    int a, b;
    char op;
    int parsed = sscanf(line, "%d %c %d", &a, &op, &b);

    if (parsed != 3) {
        printf("Invalid input format. Use: <number> <operator> <number>\n");
        return 1;
    }

    // ---- 构建函数指针数组与运算符字符数组的映射 ----
    // 两者的索引一一对应：ops[0] 对应 '+'，ops[1] 对应 '-'，以此类推
    ArithOp ops[] = { add, sub, mul, div_int, mod };
    char op_chars[] = { '+', '-', '*', '/', '%' };
    int num_ops = sizeof(ops) / sizeof(ops[0]);

    // ---- 遍历查找匹配的运算符，并通过函数指针调用 ----
    bool found = false;
    for (int i = 0; i < num_ops; i++) {
        if (op_chars[i] == op) {
            // ★ 关键：通过函数指针数组调用对应的运算
            int result = ops[i](a, b);
            printf("%d %c %d = %d\n", a, op, b, result);
            found = true;
            break;   // 找到匹配项后无需继续遍历
        }
    }

    if (!found) {
        printf("Unknown operator: '%c'\n", op);
        printf("Supported: + - * / %%\n");
        return 1;
    }

    return 0;
}