/*
 * contact.c
 * 通讯录模块的具体实现。
 *
 * 包含自己的头文件，实现其中声明的函数。
 * 内部辅助函数和变量用 static 隐藏。
 */

#include "contact.h"   // ★ 先包含自己的头文件（用于检查声明与定义是否一致）
#include <string.h>    // strlen, strcmp, strcpy
#include <stdlib.h>    // exit

// ========== 内部函数（static，外部不可见）==========

/*
 * prompt_and_read:
 *   通用的"提示→读取一行→去掉换行"模板。
 *   设为 static 因为它只是模块内部使用的辅助函数。
 */
static void prompt_and_read(const char *prompt, char *buffer, int size)
{
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) == NULL) {
        printf("\nEnd of input.\n");
        exit(0);
    }
    int len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

// ========== 公开函数的实现 ==========

void contact_init(ContactList *list)
{
    list->count = 0;
}

void contact_add(ContactList *list)
{
    if (list->count >= MAX_CONTACTS) {
        printf("  List is full!\n");
        return;
    }

    Contact c;
    prompt_and_read("  Name : ", c.name, NAME_LEN);

    if (c.name[0] == '\0') {
        printf("  Name cannot be empty.\n");
        return;
    }

    prompt_and_read("  Phone: ", c.phone, PHONE_LEN);

    printf("  Age  : ");
    char age_buf[10];
    if (fgets(age_buf, sizeof(age_buf), stdin) != NULL) {
        sscanf(age_buf, "%d", &c.age);
    }

    list->entries[list->count] = c;
    list->count++;

    printf("  Contact '%s' added.\n", c.name);
}

int contact_find(const ContactList *list, const char *name)
{
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->entries[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void contact_list(const ContactList *list)
{
    if (list->count == 0) {
        printf("  (empty)\n");
        return;
    }
    for (int i = 0; i < list->count; i++) {
        printf("  [%d] %s  %s  %d\n", i + 1,
               list->entries[i].name,
               list->entries[i].phone,
               list->entries[i].age);
    }
}

int safe_read_line(char *buffer, int size)
{
    if (fgets(buffer, size, stdin) == NULL) {
        printf("\nEnd of input.\n");
        exit(0);
    }
    int len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    return len;
}