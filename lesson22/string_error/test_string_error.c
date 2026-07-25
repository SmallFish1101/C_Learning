/*
 * test_string_error.c
 * 测试 safe_strcat 在各种边界条件下的错误码返回值。
 */

#include <stdio.h>
#include <string.h>   // strcpy, strcmp
#include "my_string.h"

#define TEST(cond, name) \
    do { \
        if (cond) printf("  [PASS] %s\n", name); \
        else      printf("  [FAIL] %s\n", name); \
    } while(0)

int main(void)
{
    printf("=== Testing safe_strcat with StringError ===\n\n");

    char buf[20];
    StringError err;

    // ---------- 测试 1：正常拼接 ----------
    strcpy(buf, "Hello ");
    err = safe_strcat(buf, sizeof(buf), "World!");
    TEST(err == STRING_OK && strcmp(buf, "Hello World!") == 0,
         "normal concat returns STRING_OK");

    // ---------- 测试 2：空串拼接 ----------
    strcpy(buf, "Hello");
    err = safe_strcat(buf, sizeof(buf), "");
    TEST(err == STRING_OK && strcmp(buf, "Hello") == 0,
         "empty src returns STRING_OK (no change)");

    // ---------- 测试 3：dest 为 NULL ----------
    err = safe_strcat(NULL, 100, "test");
    TEST(err == STRING_NULL_POINTER,
         "NULL dest returns STRING_NULL_POINTER");

    // ---------- 测试 4：src 为 NULL ----------
    strcpy(buf, "Hello");
    err = safe_strcat(buf, sizeof(buf), NULL);
    TEST(err == STRING_NULL_POINTER && strcmp(buf, "Hello") == 0,
         "NULL src returns STRING_NULL_POINTER (dest unchanged)");

    // ---------- 测试 5：dest_size 为 0 ----------
    err = safe_strcat(buf, 0, "test");
    TEST(err == STRING_NO_SPACE,
         "dest_size=0 returns STRING_NO_SPACE");

    // ---------- 测试 6：目标缓冲区刚好满（无空间拼接）----------
    // buf 大小 20，填入 "1234567890123456789" (19个字符) + '\0' 刚好满
    strcpy(buf, "1234567890123456789");   // 19 个字符
    err = safe_strcat(buf, sizeof(buf), "X");
    TEST(err == STRING_NO_SPACE && strcmp(buf, "1234567890123456789") == 0,
         "full dest returns STRING_NO_SPACE");

    // ---------- 测试 7：空间不足，发生截断 ----------
    strcpy(buf, "Hello");   // 5 字符，剩余 14 字节（保留1字节给'\0'，最多复制13字符）
    err = safe_strcat(buf, sizeof(buf), " World!!!!!!!!");  // 源串 13 个字符（空格+12个叹号），刚好放下
    // 先验证刚好放下的情况
    if (err == STRING_OK) {
        printf("  [INFO] 'Hello' + ' World!!!!!!!!' fit exactly (no truncation)\n");
    } else {
        // 如果源串更长，例如 14 个字符，则截断。这里我们换一个更长的源串测试截断
        strcpy(buf, "Hello");
        err = safe_strcat(buf, sizeof(buf), " World!!!!!!!!!");   // 14 个字符 > 13，截断
        TEST(err == STRING_TRUNCATED && strcmp(buf, "Hello World!!!!!!!!") == 0,
             "truncated result returns STRING_TRUNCATED");
    }

    printf("\n=== Testing Complete ===\n");
    return 0;
}