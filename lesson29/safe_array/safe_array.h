/*
 * safe_array.h
 * 第29课 练习二：安全整数动态数组模块 —— 公开接口
 *
 * 设计原则：
 *   1. 指针初始化即为 NULL
 *   2. 所有分配操作均检查返回值
 *   3. free 后立即置 NULL
 *   4. realloc 永远使用临时指针接收
 */

#ifndef SAFE_ARRAY_H
#define SAFE_ARRAY_H

#include <stdio.h>   // printf（调试用）
#include <stdlib.h>  // malloc, realloc, free, exit

// 扩容策略常量
#define SAFE_ARRAY_INIT_CAPACITY  4    // 首次分配时的默认容量
#define SAFE_ARRAY_GROWTH_FACTOR  2    // 每次扩容的倍数

/* 安全动态数组结构体 */
typedef struct {
    int *data;       // 动态分配的数组（未分配时为 NULL）
    int  count;      // 当前已存储元素个数
    int  capacity;   // 当前总容量（元素个数，非字节数）
} SafeIntArray;

/* 初始化：所有字段归零/NULL */
void array_init(SafeIntArray *arr);

/* 追加元素：自动扩容，成功返回 1，失败返回 0 */
int  array_append(SafeIntArray *arr, int value);

/* 销毁数组：释放内存，字段归零 */
void array_destroy(SafeIntArray *arr);

/* 安全读取第 index 个元素（越界时输出错误并调用 exit(1)） */
int  array_get(const SafeIntArray *arr, int index);

/* 返回当前元素个数 */
int  array_size(const SafeIntArray *arr);

/* 打印所有元素（调试用） */
void array_print(const SafeIntArray *arr);

#endif