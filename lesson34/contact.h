/*
 * contact.h
 * 通讯录模块的公开接口。
 *
 * 本文件只包含：宏定义、结构体定义、函数声明。
 * 不包含任何函数实现代码。
 */

#ifndef CONTACT_H
#define CONTACT_H

#include <stdio.h>   // 注意：如果头文件里不需要 printf 等函数，
                     // 只需在用到它们的 .c 中包含即可
                     // 这里放的是结构体和函数声明所需的类型

#define MAX_CONTACTS  100
#define NAME_LEN      50
#define PHONE_LEN     20

/* 单个联系人 */
typedef struct {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    int  age;
} Contact;

/* 通讯录整体 */
typedef struct {
    Contact entries[MAX_CONTACTS];
    int     count;
} ContactList;

/* ---- 公开接口（函数声明）---- */

/* 初始化通讯录 */
void contact_init(ContactList *list);

/* 添加联系人 */
void contact_add(ContactList *list);

/* 查找联系人（返回索引，未找到返回 -1） */
int  contact_find(const ContactList *list, const char *name);

/* 列出所有联系人 */
void contact_list(const ContactList *list);

/* 安全读取一行（去掉换行符） */
int  safe_read_line(char *buffer, int size);

#endif