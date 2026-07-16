/*
 * data_clean.c
 * 第13课 练习二：数据清洗 —— 使用 continue 过滤负数
 *
 * 功能：读取一系列整数（0 结束），
 *       忽略所有负数，统计正数的个数、总和与平均值。
 */

#include <stdio.h>   // printf, fgets, sscanf
#include <stdlib.h>  // exit

/*
 * read_int:
 *   安全读取一个整数（与第10课模板完全一致）。
 *   return: 用户输入的整数。
 */
int read_int(void)
{
    char line[100];   // 输入缓冲区

    while (1) {
        printf("Enter an integer (0 to finish): ");

        // fgets 读取一整行
        if (fgets(line, sizeof(line), stdin) == NULL) {
            // 遇到 EOF（Ctrl+Z 或 Ctrl+D），安全退出
            printf("\nEnd of input.\n");
            exit(0);
        }

        int value;
        int pos = 0;   // 记录 sscanf 解析停止的位置

        // sscanf 尝试从 line 中解析整数，%n 记下消耗的字符数
        int matched = sscanf(line, "%d %n", &value, &pos);

        // 检查 1：是否成功匹配到一个整数
        if (matched != 1) {
            printf("  ERROR: Please enter a valid integer.\n");
            continue;   // 回到 while 开头，重新输入
        }

        // 检查 2：行内不能有多余字符（如 "5abc"）
        if (line[pos] != '\0') {
            printf("  ERROR: Extra characters after number.\n");
            continue;
        }

        // 输入合法，返回该整数
        return value;
    }
}

int main(void)
{
    printf("=== Data Cleaner ===\n");
    printf("Enter integers one by one (0 to stop).\n");
    printf("Negative numbers will be ignored.\n\n");

    int count = 0;   // 正数的个数
    int sum   = 0;   // 正数的总和

    // 主循环：不断读取整数
    while (1) {
        int num = read_int();

        // 终止条件：用户输入 0
        if (num == 0) {
            break;   // 退出循环，开始输出统计结果
        }

        // 过滤条件：负数跳过
        if (num < 0) {
            printf("  -> Ignored (negative)\n");
            continue;   // 跳过本次循环剩余部分，不累加到 sum 和 count
        }

        // 如果能执行到这里，num 一定是正数
        count++;
        sum += num;
    }

    // 输出统计结果
    printf("\n=== Results ===\n");

    if (count == 0) {
        printf("No positive numbers were entered.\n");
    } else {
        double average = (double)sum / count;   // 浮点除法，用强制转换确保精度
        printf("Count of positive numbers: %d\n", count);
        printf("Sum:                       %d\n", sum);
        printf("Average:                   %.2f\n", average);
    }

    return 0;
}