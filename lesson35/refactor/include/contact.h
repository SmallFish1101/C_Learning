/*
 * contact.h
 * 第35课 练习一：通讯录模块 —— 公开接口（多目录版本）
 *
 * 本文件放置在 include/ 目录下，作为库的"说明书"。
 * 任何需要调用通讯录功能的源文件，只需 #include "contact.h"。
 *
 * 与第34课版本完全一致，未做任何功能修改。
 */

#ifndef CONTACT_H
#define CONTACT_H

#include <stdio.h>    // FILE, printf, fgets, sscanf, perror
#include <stdlib.h>   // malloc, realloc, free, exit
#include <string.h>   // strlen, strcmp, strcpy, strspn
#include <stdbool.h>  // bool, true, false

// ========== 配置常量 ==========
#define INITIAL_CAPACITY  2
#define NAME_LEN         50
#define PHONE_LEN        20
#define FILE_LINE_LEN   256

// ========== 结构体定义 ==========

typedef struct {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    int  age;
} Contact;

typedef struct {
    Contact *entries;
    int      count;
    int      capacity;
} ContactList;

// ========== 核心操作（公开函数声明）==========

void contact_init(ContactList *list);
void contact_destroy(ContactList *list);

void contact_add(ContactList *list);
void contact_delete(ContactList *list);
int  contact_find(const ContactList *list, const char *name);
void contact_modify(ContactList *list);
void contact_list(const ContactList *list);

void contact_save_to_file(const ContactList *list, const char *filename);
void contact_load_from_file(ContactList *list, const char *filename);

int  safe_read_line(char *buffer, int size);
int  read_int(const char *prompt);

bool is_valid_name(const char *name);
bool is_valid_phone(const char *phone);
bool is_valid_age(const char *age_str, int *age_out);

#endif // CONTACT_H