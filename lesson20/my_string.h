/*
 * my_string.h
 * 自定义字符串处理库的公开接口。
 *
 * 提供：长度、复制、拼接、比较、查找、安全拼接等函数。
 * 注意：所有函数都假设传入的字符串是有效的 C 风格字符串。
 */

#ifndef MY_STRING_H
#define MY_STRING_H

#include <stddef.h>   /* size_t */

/* 计算字符串长度（不包括结尾 '\0'） */
size_t my_strlen(const char *s);

/* 复制字符串（危险：不检查目标缓冲区大小） */
char *my_strcpy(char *dest, const char *src);

/* 拼接字符串（危险：不检查目标缓冲区大小） */
char *my_strcat(char *dest, const char *src);

/* 比较两个字符串，返回值为 <0, 0, >0 */
int my_strcmp(const char *s1, const char *s2);

/* 在 haystack 中查找 needle 首次出现的位置，未找到返回 NULL */
char *my_strstr(const char *haystack, const char *needle);

/* 安全拼接字符串：最多在 dest 剩余空间内拼接 src，总是保证 dest 以 '\0' 结尾 */
int safe_strcat(char *dest, size_t dest_size, const char *src);

#endif