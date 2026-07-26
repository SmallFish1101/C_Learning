/*
 * contact.h
 * 第24课 命令行通讯录 —— 数据结构与接口声明
 */

#ifndef CONTACT_H
#define CONTACT_H

#include <stdio.h>   // printf, fgets, sscanf
#include <string.h>  // strcmp, strcpy, strlen
#include <stdlib.h>  // exit

// ========== 宏定义 ==========
#define MAX_CONTACTS  100      // 最大联系人数量
#define NAME_LEN      50       // 姓名缓冲区大小
#define PHONE_LEN     20       // 电话缓冲区大小

// ========== 结构体定义 ==========

/* 单个联系人 */
typedef struct {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    int  age;
} Contact;

/* 通讯录整体 */
typedef struct {
    Contact entries[MAX_CONTACTS];
    int     count;             // 当前联系人数量
} ContactList;

// ========== 函数原型 ==========

/* 初始化通讯录 */
void contact_init(ContactList *list);

/* 添加联系人 */
void contact_add(ContactList *list);

/* 删除联系人（按姓名） */
void contact_delete(ContactList *list);

/* 查找联系人（按姓名），返回索引，未找到返回 -1 */
int  contact_find(const ContactList *list, const char *name);

/* 修改联系人信息 */
void contact_modify(ContactList *list);

/* 列出所有联系人 */
void contact_list(const ContactList *list);

/* 安全读取一行（去掉换行符） */
int  safe_read_line(char *buffer, int size);

#endif

// 在 contact.h 末尾添加（原内容不变）
/* 校验函数 */
int is_valid_name(const char *name);
int is_valid_phone(const char *phone);
int is_valid_age(const char *age_str, int *age_out);