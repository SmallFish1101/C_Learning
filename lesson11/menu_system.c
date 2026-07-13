/*
 * menu_system.c
 * 第11课 实例：命令行菜单选择系统
 *
 * 功能：显示菜单，根据用户输入执行不同操作。
 *       综合使用 if-else、switch、三元运算符、安全输入。
 */

#include <stdio.h>
#include <stdbool.h>   // bool, true, false

// 用枚举定义菜单选项（比直接写数字更可读）
typedef enum {
    MENU_ADD    = 1,   // 手动指定从 1 开始
    MENU_DELETE = 2,
    MENU_MODIFY = 3,
    MENU_EXIT   = 4
} MenuOption;

int main(void)
{
    printf("=== Menu System Demo ===\n\n");

    bool running = true;   // 控制主循环

    while (running)
    {
        // 显示菜单
        printf("-------------------\n");
        printf(" 1. Add\n");
        printf(" 2. Delete\n");
        printf(" 3. Modify\n");
        printf(" 4. Exit\n");
        printf("-------------------\n");

        // 安全读取用户选择
        int choice;
        printf("Select (1-4): ");

        char line[100];
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;   // EOF，退出循环
        }

        int pos = 0;
        if (sscanf(line, "%d %n", &choice, &pos) == 1 && line[pos] == '\0')
        {
            // 输入格式合法，用 switch 根据选择分派
            switch (choice)
            {
                case MENU_ADD:
                    printf(">> Performing ADD operation...\n");
                    break;

                case MENU_DELETE:
                    printf(">> Performing DELETE operation...\n");
                    break;

                case MENU_MODIFY:
                    printf(">> Performing MODIFY operation...\n");
                    break;

                case MENU_EXIT:
                    // 三元运算符：用一句话设置退出状态
                    printf("Are you sure? (y/n): ");
                    char confirm_line[10];
                    fgets(confirm_line, sizeof(confirm_line), stdin);
                    // 简化处理：只检查首字母
                    if (confirm_line[0] == 'y' || confirm_line[0] == 'Y') {
                        running = false;
                        printf("Goodbye!\n");
                    } else {
                        printf("Cancelled.\n");
                    }
                    break;

                default:
                    // 输入的是整数，但不在 1-4 范围内
                    printf(">> Invalid choice. Please enter 1-4.\n");
                    break;
            }
        }
        else
        {
            // 输入的根本不是整数，或有多余字符
            printf(">> Invalid input. Please enter a number.\n");
        }
    }

    return 0;
}