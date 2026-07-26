/*
 * main.c
 * 第24课 命令行通讯录 —— 主菜单与程序入口
 */

#include "contact.h"

// ========== 菜单选项枚举 ==========
typedef enum {
    MENU_ADD         = 1,
    MENU_DELETE      = 2,
    MENU_FIND        = 3,
    MENU_FIND_PREFIX = 7,     // 新增：前缀查找
    MENU_MODIFY      = 4,
    MENU_LIST        = 5,
    MENU_EXIT        = 8      // 原来为 6，现改为 8
} MenuOption;

// ========== 打印菜单 ==========
void print_menu(void)
{
    printf("\n");
    printf("==========================\n");
    printf("   Contact Book Menu\n");
    printf("==========================\n");
    printf(" 1. Add contact\n");
    printf(" 2. Delete contact\n");
    printf(" 3. Find contact\n");
    printf(" 4. Modify contact\n");
    printf(" 5. List all contacts\n");
    printf(" 7. Find by name prefix\n");   // 新增
    printf(" 8. Exit\n");                   // 原 6 改为 8
    printf("--------------------------\n");
    printf("Your choice: ");
}

// ========== 主函数 ==========
int main(void)
{
    ContactList book;
    contact_init(&book);

    printf("Welcome to the Contact Book!\n");

    int running = 1;
    while (running)
    {
        print_menu();

        char input[10];
        safe_read_line(input, sizeof(input));

        int choice;
        if (sscanf(input, "%d", &choice) != 1) {
            printf("Invalid input. Please enter a number 1-6.\n");
            continue;
        }

        switch (choice)
        {
            case MENU_ADD:
                contact_add(&book);
                break;

            case MENU_DELETE:
                contact_delete(&book);
                break;

            case MENU_FIND:
                {
                    char name[NAME_LEN];
                    printf("  Enter name to find: ");
                    safe_read_line(name, NAME_LEN);
                    int idx = contact_find(&book, name);
                    if (idx != -1) {
                        printf("  Found: %s, %s, %d years old\n",
                               book.entries[idx].name,
                               book.entries[idx].phone,
                               book.entries[idx].age);
                    } else {
                        printf("  Contact '%s' not found.\n", name);
                    }
                }
                break;

            case MENU_MODIFY:
                contact_modify(&book);
                break;

            case MENU_LIST:
                contact_list(&book);
                break;

            case MENU_EXIT:
                printf("Goodbye!\n");
                running = 0;
                break;

            default:
                printf("Invalid choice. Please enter 1-6.\n");
        }
    }

    return 0;
}