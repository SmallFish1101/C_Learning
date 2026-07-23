/*
 * my_string.c
 * 自定义字符串处理库的实现。
 * 所有函数均使用纯指针操作，不依赖标准库（除 NULL 定义）。
 */

#include "my_string.h"

/* ---------- my_strlen ---------- */
size_t my_strlen(const char *s)
{
    const char *p = s;
    while (*p) p++;
    return (size_t)(p - s);
}

/* ---------- my_strcpy ---------- */
char *my_strcpy(char *dest, const char *src)
{
    char *ret = dest;
    while ((*dest++ = *src++));
    return ret;
}

/* ---------- my_strcat ---------- */
char *my_strcat(char *dest, const char *src)
{
    char *ret = dest;
    while (*dest) dest++;          /* 找到 dest 的末尾 */
    while ((*dest++ = *src++));     /* 复制 src */
    return ret;
}

/* ---------- my_strcmp ---------- */
int my_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

/* ---------- my_strstr ---------- */
char *my_strstr(const char *haystack, const char *needle)
{
    if (*needle == '\0') return (char *)haystack;
    while (*haystack) {
        const char *h = haystack;
        const char *n = needle;
        while (*h && *n && (*h == *n)) {
            h++; n++;
        }
        if (*n == '\0') return (char *)haystack;
        haystack++;
    }
    return NULL;
}

/* ---------- safe_strcat ---------- */
int safe_strcat(char *dest, size_t dest_size, const char *src)
{
    if (dest == NULL || src == NULL || dest_size == 0) return 0;

    /* 计算 dest 现有长度 */
    size_t dest_len = 0;
    while (dest_len < dest_size && dest[dest_len] != '\0') dest_len++;

    /* 如果 dest 不是合法字符串，强制终止 */
    if (dest_len == dest_size) {
        dest[dest_size - 1] = '\0';
        return 0;
    }

    /* 剩余空间不足 1 字节（连 '\0' 都放不下） */
    if (dest_len + 1 >= dest_size) return 0;

    size_t max_copy = dest_size - dest_len - 1;   /* 可复制字符数 */
    size_t copied = 0;
    char *p = dest + dest_len;

    while (*src && copied < max_copy) {
        *p++ = *src++;
        copied++;
    }
    *p = '\0';
    return (int)copied;
}