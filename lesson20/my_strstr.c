/*
 * my_strstr.c
 * 第20课 练习一：手写 strstr 函数
 *
 * 功能：在 haystack 字符串中查找首次出现 needle 子串的位置，
 *       完全使用指针操作，不调用标准库函数。
 */

#include <stdio.h>   // printf
#include <string.h>  // strstr（用于对比验证）

/*
 * my_strstr:
 *   在 haystack 中查找首次出现 needle 子串的位置。
 *   参数:
 *     haystack : 被搜索的字符串（只读）
 *     needle   : 要查找的子串（只读）
 *   返回值:
 *     指向 haystack 中匹配子串的首字符地址；若未找到或 needle 为空则返回 NULL。
 *     当 needle 为空串 ("") 时，返回 haystack（与标准库行为一致）。
 */
char *my_strstr(const char *haystack, const char *needle)
{
    // 1. 空子串的特殊处理：标准要求返回 haystack
    if (*needle == '\0') {
        return (char *)haystack;
    }

    // 2. 外层循环：遍历 haystack 的每个可能的起始位置
    //    当 *haystack 不为 '\0' 时继续（直到 haystack 结束）
    while (*haystack != '\0')
    {
        // 用两个临时指针分别指向当前起始位置和子串开头
        const char *h = haystack;
        const char *n = needle;

        // 3. 内层循环：从当前位置开始，逐个字符与 needle 比较
        //    条件：字符相等 且 needle 未到结束符
        while (*h != '\0' && *n != '\0' && *h == *n)
        {
            h++;   // 移动到 haystack 的下一个字符
            n++;   // 移动到 needle 的下一个字符
        }

        // 如果 needle 的指针 n 已经指向 '\0'，说明整个 needle 匹配成功
        if (*n == '\0') {
            return (char *)haystack;   // 返回匹配起始位置
        }

        // 否则，从 haystack 的下一个字符重新开始尝试匹配
        haystack++;
    }

    // 如果遍历完整个 haystack 仍未找到，返回 NULL
    return NULL;
}

int main(void)
{
    printf("=== my_strstr Demo ===\n\n");

    // 测试用例数组：{ haystack, needle, 期望结果描述 }
    struct {
        const char *haystack;
        const char *needle;
        const char *expected_result;   // 期望子串起始内容（若找不到，传 NULL）
    } tests[] = {
        {"Hello, world!", "world", "world!"},
        {"Hello, world!", "Hello", "Hello, world!"},
        {"Hello, world!", "xyz", NULL},          // 不存在
        {"abcdef", "", "abcdef"},               // 空子串
        {"aaaa", "aa", "aaaa"},                 // 重叠匹配
        {"C programming", "pro", "programming"},
        {"embedded", "bed", "bedded"},
        {"", "abc", NULL},                      // haystack 为空
        {"abc", "", "abc"},                     // needle 为空
        {"123456", "456", "456"},
    };
    int num_tests = sizeof(tests) / sizeof(tests[0]);

    int all_passed = 1;

    for (int i = 0; i < num_tests; i++)
    {
        const char *haystack = tests[i].haystack;
        const char *needle   = tests[i].needle;
        const char *expected = tests[i].expected_result;

        char *my_result   = my_strstr(haystack, needle);
        char *std_result  = strstr(haystack, needle);   // 标准库对照

        printf("Test %d: haystack=\"%s\", needle=\"%s\"\n", i + 1, haystack, needle);

        // 打印我的结果
        if (my_result != NULL)
            printf("  my_strstr   : \"%s\"\n", my_result);
        else
            printf("  my_strstr   : NULL\n");

        // 打印标准库结果
        if (std_result != NULL)
            printf("  std_strstr  : \"%s\"\n", std_result);
        else
            printf("  std_strstr  : NULL\n");

        // 验证：如果 expected 为 NULL，则 my_result 也应为 NULL
        // 否则，比较 my_result 指向的字符串是否与 expected 一致
        int pass = 0;
        if (expected == NULL) {
            pass = (my_result == NULL);
        } else {
            pass = (my_result != NULL) && 
                   (strcmp(my_result, expected) == 0);
        }

        if (pass)
            printf("  => PASS\n\n");
        else {
            printf("  => FAIL (expected \"%s\")\n\n", expected ? expected : "NULL");
            all_passed = 0;
        }
    }

    if (all_passed)
        printf("All tests passed!\n");
    else
        printf("Some tests failed. Check implementation.\n");

    return 0;
}