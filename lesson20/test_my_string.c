/*
 * test_my_string.c
 * 测试自定义字符串处理库的每个函数。
 * 测试策略：将自定义函数的结果与标准库或预期值比较，打印 PASS/FAIL。
 */

#include <stdio.h>      /* printf */
#include <string.h>     /* strlen, strcpy, strcat, strcmp, strstr */
#include "my_string.h"

/* 辅助宏：若条件为真则打印 PASS，否则打印 FAIL */
#define TEST(cond, name) \
    do { \
        if (cond) printf("  [PASS] %s\n", name); \
        else      printf("  [FAIL] %s\n", name); \
    } while(0)

int main(void)
{
    printf("=== Testing my_string Library ===\n\n");

    /* ========== 1. my_strlen ========== */
    printf("1. my_strlen:\n");
    TEST(my_strlen("") == strlen(""), "empty string");
    TEST(my_strlen("hello") == strlen("hello"), "hello (5)");
    TEST(my_strlen("C programming") == strlen("C programming"), "with space");

    /* ========== 2. my_strcpy ========== */
    printf("\n2. my_strcpy:\n");
    {
        char buf[50];
        my_strcpy(buf, "world");
        TEST(strcmp(buf, "world") == 0, "copy 'world'");
    }

    /* ========== 3. my_strcat ========== */
    printf("\n3. my_strcat:\n");
    {
        char buf[50] = "Hello ";
        my_strcat(buf, "World!");
        TEST(strcmp(buf, "Hello World!") == 0, "concat 'Hello ' + 'World!'");
    }

    /* ========== 4. my_strcmp ========== */
    printf("\n4. my_strcmp:\n");
    TEST(my_strcmp("abc", "abc") == 0, "identical strings");
    TEST(my_strcmp("abc", "abd") < 0, "abc < abd");
    TEST(my_strcmp("abc", "abb") > 0, "abc > abb");

    /* ========== 5. my_strstr ========== */
    printf("\n5. my_strstr:\n");
    {
        const char *hay = "Hello, world!";
        TEST(my_strstr(hay, "world") == strstr(hay, "world"), "find 'world'");
        TEST(my_strstr(hay, "xyz") == NULL, "find 'xyz' (not found)");
        TEST(my_strstr(hay, "") == hay, "empty needle returns haystack");
    }

    /* ========== 6. safe_strcat ========== */
    printf("\n6. safe_strcat:\n");
    {
        char buf[10];
        int ret;

        /* 正常拼接 */
        strcpy(buf, "AB");
        ret = safe_strcat(buf, sizeof(buf), "CD");
        TEST(ret == 2 && strcmp(buf, "ABCD") == 0, "normal concat 'AB'+'CD'");

        /* 空间刚好够 */
        strcpy(buf, "12");
        ret = safe_strcat(buf, sizeof(buf), "34567"); /* 5个字符，剩余空间 10-3=7，足够 */
        /* 注意：剩余空间 = 10 - 3 = 7，max_copy = 6，可放下"34567"（5字符） */
        TEST(ret == 5 && strcmp(buf, "1234567") == 0, "fit exactly");

        /* 空间不足，截断 */
        strcpy(buf, "Hello"); /* 5字符 + \0，剩余 4 字节，max_copy=3 */
        ret = safe_strcat(buf, sizeof(buf), " World!"); /* 期望复制 " Wo" (3字符) */
        TEST(ret == 3 && strcmp(buf, "Hello Wo") == 0, "truncate when no space");
    }

    printf("\n=== Testing Complete ===\n");
    return 0;
}