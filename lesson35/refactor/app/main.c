/*
 * main.c
 * 通讯录主程序 —— 只负责菜单和调度。
 *
 * 依赖：contact.h
 * 不触碰 Contact / ContactList 的内部细节。
 */

#include "contact.h"

// ========== 菜单枚举 ==========
typedef enum {
    MENU_ADD    = 1,
    MENU_DELETE = 2,
    MENU_FIND   = 3,
    MENU_MODIFY = 4,
    MENU_LIST   = 5,
    MENU_SAVE   = 6,
    MENU_LOAD   = 7,
    MENU_EXIT   = 8
} MenuOption;

// ========== 打印菜单 ==========
void print_menu(void)
{
    printf("\n========================\n");
    printf("  Dynamic Contact Book\n");
    printf("========================\n");
    printf(" 1. Add contact\n");
    printf(" 2. Delete contact\n");
    printf(" 3. Find contact\n");
    printf(" 4. Modify contact\n");
    printf(" 5. List all contacts\n");
    printf(" 6. Save to file\n");
    printf(" 7. Load from file\n");
    printf(" 8. Exit\n");
    printf("------------------------\n");
    printf("Your choice: ");
}

// ========== 主循环 ==========
int main(void)
{
    ContactList book;
    contact_init(&book);

    printf("Welcome to the Dynamic Contact Book!\n");

    int running = 1;
    while (running)
    {
        print_menu();

        char input[10];
        safe_read_line(input, sizeof(input));

        int choice;
        if (sscanf(input, "%d", &choice) != 1) {
            printf("Invalid input.\n");
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
                    printf("  Name to find: ");
                    safe_read_line(name, NAME_LEN);
                    int idx = contact_find(&book, name);
                    if (idx != -1) {
                        printf("  Found at index %d\n", idx);
                    } else {
                        printf("  '%s' not found.\n", name);
                    }
                }
                break;

            case MENU_MODIFY:
                contact_modify(&book);
                break;

            case MENU_LIST:
                contact_list(&book);
                break;

            case MENU_SAVE:
                {
                    char filename[100];
                    printf("  Filename to save: ");
                    safe_read_line(filename, sizeof(filename));
                    contact_save_to_file(&book, filename);
                }
                break;

            case MENU_LOAD:
                {
                    char filename[100];
                    printf("  Filename to load: ");
                    safe_read_line(filename, sizeof(filename));
                    contact_load_from_file(&book, filename);
                }
                break;

            case MENU_EXIT:
                printf("Goodbye!\n");
                running = 0;
                break;

            default:
                printf("Invalid choice. Please enter 1-8.\n");
        }
    }

    contact_destroy(&book);
    return 0;
}