/*
 * contact.h
 * 第28课 作业一：动态通讯录 —— 数据结构与接口声明
 */

#ifndef CONTACT_H
#define CONTACT_H

#include <stdio.h>   // printf, fgets, sscanf
#include <string.h>  // strcmp, strcpy, strlen
#include <stdlib.h>  // malloc, realloc, free, exit

// ========== 宏定义 ==========
#define INITIAL_CAPACITY  2     // 初始容量（故意设小便于测试扩容）
#define NAME_LEN         50     // 姓名缓冲区大小
#define PHONE_LEN        20     // 电话缓冲区大小

// ========== 结构体定义 ==========

/* 单个联系人 */
typedef struct {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    int  age;
} Contact;

/* 通讯录整体（动态版本） */
typedef struct {
    Contact *entries;    // 指向动态分配的数组
    int      count;      // 当前联系人数量
    int      capacity;   // 当前数组容量
} ContactList;

// ========== 函数原型 ==========

/* 初始化通讯录（分配初始内存） */
void contact_init(ContactList *list);

/* 销毁通讯录（释放动态内存） */
void contact_destroy(ContactList *list);

/* 添加联系人（自动扩容） */
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

/* 校验函数（来自第24课练习一） */
int is_valid_name(const char *name);
int is_valid_phone(const char *phone);
int is_valid_age(const char *age_str, int *age_out);

#endif