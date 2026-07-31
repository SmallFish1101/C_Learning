/*
 * string_append.c
 * 第28课 作业二：动态字符串拼接
 *
 * 功能：实现 string_append 函数，用 malloc 分配内存，
 *       将两个字符串拼接，返回新字符串。
 *       调用者负责调用 free 释放返回的字符串。
 */

#include <stdio.h>    // printf
#include <stdlib.h>   // malloc, free
#include <string.h>   // strlen, strcpy, strcat

/*
 * string_append:
 *   将两个字符串拼接成一个新的字符串（动态分配内存）。
 *   参数 s1: 第一个字符串（可拼接在开头），若为 NULL 则视为空串
 *   参数 s2: 第二个字符串（追加到末尾），若为 NULL 则视为空串
 *   返回: 指向新字符串的指针；若内存分配失败则返回 NULL
 *
 *   注意: 调用者必须在不再需要时 free 返回的指针。
 */
char *string_append(const char *s1, const char *s2)
{
    // 1. 处理 NULL 输入：将 NULL 视为空字符串
    if (s1 == NULL) s1 = "";
    if (s2 == NULL) s2 = "";

    // 2. 计算拼接后所需的字符数（不含末尾 '\0'）
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    size_t total_len = len1 + len2 + 1;   // +1 为 '\0' 预留空间

    // 3. 动态分配内存
    char *result = (char *)malloc(total_len);
    if (result == NULL) {
        // 内存分配失败，打印错误信息并返回 NULL
        printf("  ERROR: Memory allocation failed.\n");
        return NULL;
    }

    // 4. 将第一个字符串复制到新内存
    strcpy(result, s1);

    // 5. 将第二个字符串追加到新内存末尾
    strcat(result, s2);

    // 6. 返回拼接结果（调用者需要 free）
    return result;
}

// ========== 测试主函数 ==========
int main(void)
{
    printf("=== Dynamic String Append ===\n\n");

    // 测试用例数组
    const char *tests_s1[] = {
        "Hello, ",      // 正常拼接
        "",             // 空串后面接内容
        "Part",         // 部分内容
        NULL,           // NULL 输入（视为空串）
        "Hello, "
    };
    const char *tests_s2[] = {
        "World!",
        "EmptyBeg",
        "",             // 空串追加
        "NullStart",
        "World!"
    };
    int num_tests = sizeof(tests_s1) / sizeof(tests_s1[0]);

    // 保存每个测试的结果指针，以便最后统一释放
    char *results[5] = {NULL};

    for (int i = 0; i < num_tests; i++)
    {
        printf("Test %d: s1=\"%s\", s2=\"%s\"\n",
               i + 1,
               tests_s1[i] ? tests_s1[i] : "(null)",
               tests_s2[i] ? tests_s2[i] : "(null)");

        // 调用拼接函数
        results[i] = string_append(tests_s1[i], tests_s2[i]);

        if (results[i] != NULL) {
            printf("  Result: \"%s\"\n", results[i]);
            printf("  Length: %zu characters\n\n", strlen(results[i]));
        } else {
            printf("  Result: NULL (allocation failed)\n\n");
        }
    }

    // 统一释放所有动态分配的内存
    printf("=== Cleanup ===\n");
    for (int i = 0; i < num_tests; i++)
    {
        if (results[i] != NULL) {
            printf("  Freeing result[%d]: \"%s\"\n", i, results[i]);
            free(results[i]);
            results[i] = NULL;   // 释放后置空，防止悬空指针
        }
    }
    printf("All memory freed.\n");

    return 0;
}