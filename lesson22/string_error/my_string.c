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

/*
 * safe_strcat（修改版）：
 *   安全拼接字符串，返回 StringError 错误码。
 *   如果目标缓冲区空间不足，尽可能复制并保证 '\0' 结尾。
 */
StringError safe_strcat(char *dest, size_t dest_size, const char *src)
{
    // 1. 参数检查
    if (dest == NULL || src == NULL) {
        return STRING_NULL_POINTER;
    }
    if (dest_size == 0) {
        return STRING_NO_SPACE;
    }

    // 2. 计算 dest 现有长度（同时检查是否为合法 C 字符串）
    size_t dest_len = 0;
    while (dest_len < dest_size && dest[dest_len] != '\0') {
        dest_len++;
    }

    // 如果 dest_len 达到 dest_size，说明 dest 不是以 '\0' 结尾的合法字符串
    if (dest_len == dest_size) {
        dest[dest_size - 1] = '\0';
        return STRING_NO_SPACE;
    }

    // 3. 计算剩余空间（至少保留 1 字节给 '\0'）
    size_t remaining = dest_size - dest_len;
    if (remaining < 1) {
        return STRING_NO_SPACE;
    }

    // 4. 复制 src
    size_t max_copy = remaining - 1;   // 最多复制这么多字符
    size_t copied = 0;
    char *p = dest + dest_len;

    while (*src != '\0' && copied < max_copy) {
        *p++ = *src++;
        copied++;
    }
    *p = '\0';

    // 5. 判断是否发生截断
    if (*src != '\0') {
        return STRING_TRUNCATED;   // 源串还有字符未复制
    }

    return STRING_OK;
}