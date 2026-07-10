#include <stdio.h>   // printf, fgets, sscanf
#include <stdlib.h>  // exit
#include <string.h>  // strlen
#include <ctype.h>   // isdigit

/*
 * read_age:
 *   安全读取一个 0~150 之间的整数年龄。
 *   return: 合法的年龄值。
 */
int read_age(void)
{
    char line[100];   // 缓冲区，存放用户输入的一整行

    while (1) {
        printf("Please enter your age (0-150): ");

        // fgets 读取一行（最多 99 个字符，留 1 个给 '\0'）
        if (fgets(line, sizeof(line), stdin) == NULL) {
            // 如果读到 EOF（Ctrl+Z 或 Ctrl+D），直接退出程序
            printf("End of input detected.\n");
            exit(0);
        }

        int age;
        int pos = 0;   // 记录 sscanf 解析停止的位置

        // sscanf 尝试从 line 中解析整数，%n 记下当前消耗的字符数
        int matched = sscanf(line, "%d %n", &age, &pos);

        // 检查 1：是否成功匹配到一个整数
        if (matched != 1) {
            printf("  ERROR: Please enter a valid integer.\n");
            continue;   // 跳到 while 循环开头，重新输入
        }

        // 检查 2：行内是否有多余的字符（如 "20abc"）
        if (line[pos] != '\0') {
            printf("  ERROR: Extra characters after number.\n");
            continue;
        }

        // 检查 3：年龄范围
        if (age < 0 || age > 150) {
            printf("  ERROR: Age must be between 0 and 150.\n");
            continue;
        }

        // 全部通过，返回合法年龄
        return age;
    }
}

/*
 * read_name:
 *   安全读取姓名（不能为空，不能包含数字）。
 *   buffer: 存放结果的字符数组，由调用者分配。
 *   size:   buffer 的大小（字节数）。
 */
void read_name(char *buffer, int size)
{
    char line[200];   // 临时缓冲区，放用户输入

    while (1) {
        printf("Please enter your name: ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("End of input detected.\n");
            exit(0);
        }

        // 去掉 fgets 保留的换行符（如果有的话）
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';   // 把换行符替换成字符串结束符
        }

        // 检查 1：是否为空
        if (strlen(line) == 0) {
            printf("  ERROR: Name cannot be empty.\n");
            continue;
        }

        // 检查 2：是否包含数字
        int has_digit = 0;   // 标志：0 表示没有数字，1 表示有数字
        for (int i = 0; line[i] != '\0'; i++) {
            if (isdigit(line[i])) {         // isdigit 检测字符是否为 '0'~'9'
                has_digit = 1;
                break;                      // 找到一个数字就可以停止了
            }
        }
        if (has_digit) {
            printf("  ERROR: Name must not contain digits.\n");
            continue;
        }

        // 全部通过，将合法姓名复制到调用者的 buffer 中
        int i;
        for (i = 0; line[i] != '\0' && i < size - 1; i++) {
            buffer[i] = line[i];
        }
        buffer[i] = '\0';   // 确保字符串以 '\0' 结尾
        return;
    }
}

int main(void)
{
    printf("=== Safe Input Demo ===\n\n");

    // 读取年龄
    int age = read_age();

    // 读取姓名（分配 50 字节的数组）
    char name[50];
    read_name(name, sizeof(name));

    // 格式化输出结果
    printf("\n========================\n");
    printf("Name: %s\n", name);
    printf("Age:  %d\n", age);
    printf("========================\n");

    return 0;
}