/*
 * password_check.c
 * 第16课 作业三（选做）：密码验证函数
 *
 * 功能：用户输入密码，程序判断是否与预设密码匹配。
 *       使用 fgets 安全读取，用 strcmp 比较，手动去除换行符。
 */

#include <stdio.h>    // printf, fgets
#include <string.h>   // strcmp, strlen
#include <stdbool.h>  // bool, true, false

#define CORRECT_PASSWORD  "123456"   // 预设密码，修改此处即可更换密码
#define MAX_INPUT_LEN      100       // 输入缓冲区大小

/* ---------- 函数原型 ---------- */
bool check_password(const char *input);

/* ---------- 主函数 ---------- */
int main(void)
{
    char input[MAX_INPUT_LEN];   // 存放用户输入的密码

    printf("=== Password Checker ===\n");
    printf("Enter password: ");

    // fgets 安全读取一行（最多 MAX_INPUT_LEN-1 个字符）
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("\nEnd of input.\n");
        return 1;   // 读取失败，异常退出
    }

    // 去除 fgets 保留的换行符 '\n'
    // 原理：如果最后一个字符是 '\n'，把它替换为 '\0'
    int len = strlen(input);               // 获取输入字符串的长度
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';             // 去掉换行符
    }

    // 调用验证函数，根据返回值输出结果
    if (check_password(input)) {
        printf("Access granted!\n");
    } else {
        printf("Access denied! Incorrect password.\n");
    }

    return 0;
}

/* ---------- 函数定义 ---------- */

/*
 * check_password:
 *   验证用户输入的密码是否与预设密码匹配。
 *   参数 input: 用户输入的字符串（只读，不应被修改）
 *   返回值: true 表示密码正确，false 表示错误
 *
 *   注意：strcmp 比较两个字符串，返回 0 表示完全相同。
 */
bool check_password(const char *input)
{
    // strcmp 返回 0 表示两个字符串内容完全相同
    if (strcmp(input, CORRECT_PASSWORD) == 0) {
        return true;
    } else {
        return false;
    }
    // 上面的 if-else 可以简写为：
    // return (strcmp(input, CORRECT_PASSWORD) == 0);
}