#include <stdio.h>
#include <stdlib.h>   // exit

/*
 * read_int:
 *   安全地读取一个整数，输入不合法就提示重新输入。
 *   return: 用户输入的合法整数。
 */
int read_int(void) {
    char line[100];       // 存放用户输入的一整行

    while (1) {
        printf("Enter an integer: ");
        // fgets 读取一行（最多 99 个字符，留 1 个给 '\0'）
        // 如果返回 NULL 表示读到文件结尾或错误
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("End of input.\n");
            exit(0);      // 程序正常退出
        }

        int value;
        int pos = 0;      // pos 记录解析停止的位置
        // sscanf 从 line 中解析整数，%n 记下此时读了多少个字符
        // 成功条件：确实读到一个整数，且行内没有多余字符
        if (sscanf(line, "%d %n", &value, &pos) == 1 && line[pos] == '\0') {
            return value; // 输入合法，返回值
        }

        // 输入不合法，提示并继续循环
        printf("  Invalid input. Please enter an integer only.\n");
    }
}

int main(void) {
    printf("=== Safe Input Demo ===\n");

    int age = read_int();
    printf("You entered: %d\n", age);

    int year = read_int();
    printf("You entered: %d\n", year);

    printf("Sum: %d\n", age + year);
    return 0;
}