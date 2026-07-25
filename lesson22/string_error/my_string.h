/*
 * my_string.h
 * 自定义字符串处理库的公开接口（增强版）。
 *
 * 新增 StringError 枚举，使 safe_strcat 的返回值更有意义。
 */

#ifndef MY_STRING_H
#define MY_STRING_H

#include <stddef.h>   /* size_t */

// ========== 原有函数声明 ==========
size_t my_strlen(const char *s);
char *my_strcpy(char *dest, const char *src);
char *my_strcat(char *dest, const char *src);
int my_strcmp(const char *s1, const char *s2);
char *my_strstr(const char *haystack, const char *needle);

// ========== 新增错误码枚举 ==========
/*
 * StringError:
 *   字符串操作的错误码。
 *   STRING_OK             : 操作成功完成，无截断
 *   STRING_NULL_POINTER   : 传入的 dest 或 src 为 NULL
 *   STRING_TRUNCATED      : 目标缓冲区空间不足，源串被截断
 *   STRING_NO_SPACE       : 目标缓冲区无可用空间（已满）
 */
typedef enum {
    STRING_OK = 0,
    STRING_NULL_POINTER,
    STRING_TRUNCATED,
    STRING_NO_SPACE
} StringError;

// ========== 修改 safe_strcat 的接口 ==========
// 返回值从 int 改为 StringError
StringError safe_strcat(char *dest, size_t dest_size, const char *src);

#endif