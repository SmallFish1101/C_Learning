/*
 * main.c
 * 通讯录主程序 —— 只负责菜单和调用模块函数。
 *
 * 注意：main.c 只包含 contact.h，不知道 contact.c 的内部实现细节。
 *       这就是模块化的核心价值——调用者只看"说明书"，不关心"内部零件"。
 */

#include "contact.h"

int main(void)
{
    ContactList book;
    contact_init(&book);

    int running = 1;
    while (running)
    {
        printf("\n=== Menu ===\n");
        printf("1. Add\n");
        printf("2. Find\n");
        printf("3. List\n");
        printf("4. Exit\n");
        printf("Choice: ");

        char input[10];
        safe_read_line(input, sizeof(input));

        int choice;
        if (sscanf(input, "%d", &choice) != 1) {
            printf("Invalid input.\n");
            continue;
        }

        switch (choice)
        {
            case 1: contact_add(&book);  break;
            case 2:
                {
                    char name[NAME_LEN];
                    printf("Name to find: ");
                    safe_read_line(name, NAME_LEN);
                    int idx = contact_find(&book, name);
                    if (idx != -1)
                        printf("Found at index %d\n", idx);
                    else
                        printf("Not found.\n");
                }
                break;
            case 3: contact_list(&book); break;
            case 4: running = 0;         break;
            default: printf("Invalid choice.\n");
        }
    }

    return 0;
}