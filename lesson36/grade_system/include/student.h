/*
 * student.h
 * 第36课 学生成绩管理系统 —— 核心模块公开接口
 *
 * 本文件只包含：宏定义、结构体定义、函数声明。
 * 不包含任何函数实现代码。
 */

#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>    // FILE, printf, fgets, sscanf, perror
#include <stdlib.h>   // malloc, realloc, free, exit
#include <string.h>   // strlen, strcmp, strcpy, strspn
#include <stdbool.h>  // bool, true, false

// ========== 配置常量 ==========
#define INITIAL_CAPACITY  2      // 初始容量（故意小，便于测试扩容）
#define NAME_LEN         32     // 姓名最大长度
#define FILE_LINE_LEN   256     // 文件读取行缓冲区大小
#define GRADE_MIN         0     // 成绩下限
#define GRADE_MAX       100     // 成绩上限

// ========== 菜单选项（供 main.c 使用）==========
typedef enum {
    MENU_ADD      = 1,
    MENU_DELETE   = 2,
    MENU_MODIFY   = 3,
    MENU_FIND_ID  = 4,    // 按学号查找
    MENU_FIND_NAME = 5,   // 按姓名查找
    MENU_STATS    = 6,    // 统计
    MENU_SORT     = 7,    // 排序子菜单
    MENU_LIST     = 8,    // 列表显示
    MENU_SAVE     = 9,    // 保存到文件
    MENU_LOAD     = 10,   // 从文件加载
    MENU_EXIT     = 11
} MenuOption;

// ========== 排序方式枚举 ==========
typedef enum {
    SORT_BY_ID_ASC,        // 学号升序
    SORT_BY_TOTAL_DESC,    // 总分降序（排名）
    SORT_BY_CHINESE_DESC,  // 语文降序
    SORT_BY_MATH_DESC,     // 数学降序
    SORT_BY_ENGLISH_DESC   // 英语降序
} SortMethod;

// ========== 结构体定义 ==========

/* 单个学生 */
typedef struct {
    int   id;
    char  name[NAME_LEN];
    int   chinese;
    int   math;
    int   english;
    int   total;       // 总分（冗余存储，避免每次排序重新计算）
    float average;     // 平均分
    int   rank;        // 排名（在排序后更新）
} Student;

/* 成绩管理系统整体 */
typedef struct {
    Student *students;   // 动态数组
    int      count;      // 当前学生数量
    int      capacity;   // 当前数组容量
    bool     sorted;     // 数组当前是否有序（影响查找算法选择）
} StudentManager;

// ========== 核心操作（公开函数声明）==========

/* 初始化与销毁 */
void manager_init(StudentManager *mgr);
void manager_destroy(StudentManager *mgr);

/* CRUD 操作 */
void manager_add_student(StudentManager *mgr);
void manager_delete_student(StudentManager *mgr);
void manager_modify_student(StudentManager *mgr);
int  manager_find_by_id(const StudentManager *mgr, int id);
void manager_find_by_name(const StudentManager *mgr, const char *name);

/* 统计 */
void manager_show_stats(const StudentManager *mgr);

/* 排序 */
void manager_sort(StudentManager *mgr, SortMethod method);

/* 列表显示 */
void manager_list_students(const StudentManager *mgr);

/* 文件持久化 */
void manager_save_to_file(const StudentManager *mgr, const char *filename);
void manager_load_from_file(StudentManager *mgr, const char *filename);

#endif