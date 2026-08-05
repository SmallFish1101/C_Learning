/*
 * contact.h
 * 第34课 练习二：通讯录模块 —— 公开接口
 *
 * 功能：动态通讯录 + 文件持久化
 *   使用 malloc / realloc / free 管理动态数组（第28课）
 *   提供文件保存和加载（第32课）
 *   所有用户可见的功能都通过本头文件声明
 */

#ifndef CONTACT_H
#define CONTACT_H

#include <stdio.h>    // FILE, printf, fgets, sscanf, perror
#include <stdlib.h>   // malloc, realloc, free, exit
#include <string.h>   // strlen, strcmp, strcpy, strspn
#include <stdbool.h>  // bool, true, false

// ========== 配置常量 ==========
#define INITIAL_CAPACITY  2     // 初始容量（故意设小，便于测试扩容）
#define NAME_LEN         50
#define PHONE_LEN        20
#define FILE_LINE_LEN   256     // 文件读取行缓冲区大小

// ========== 结构体定义 ==========

/* 单个联系人 */
typedef struct {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    int  age;
} Contact;

/* 通讯录整体（动态版本） */
typedef struct {
    Contact *entries;    // 动态分配的数组
    int      count;      // 当前已存储数量
    int      capacity;   // 当前数组容量
} ContactList;

// ========== 核心操作（公开函数声明）==========

/* 初始化与销毁 */
void contact_init(ContactList *list);
void contact_destroy(ContactList *list);

/* CRUD 操作 */
void contact_add(ContactList *list);
void contact_delete(ContactList *list);
int  contact_find(const ContactList *list, const char *name);
void contact_modify(ContactList *list);
void contact_list(const ContactList *list);

/* 文件持久化 */
void contact_save_to_file(const ContactList *list, const char *filename);
void contact_load_from_file(ContactList *list, const char *filename);

/* 安全输入辅助（对外暴露，供 main.c 使用） */
int  safe_read_line(char *buffer, int size);
int  read_int(const char *prompt);

// ========== 数据校验（对外暴露，供其他模块使用）==========
bool is_valid_name(const char *name);
bool is_valid_phone(const char *phone);
bool is_valid_age(const char *age_str, int *age_out);

#endif