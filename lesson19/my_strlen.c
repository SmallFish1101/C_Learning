/*
 * my_strlen.c
 * 第19课 练习二：手写 strlen 函数（指针自增法）
 *
 * 功能：实现自己的 strlen 函数，用指针遍历字符串并计算长度，
 *       与标准库 strlen 对比验证正确性。
 */

#include <stdio.h>   // printf
#include <string.h>  // strlen（用于对比）

/*
 * my_strlen:
 *   计算字符串的长度（不含末尾的 '\0'）。
 *   实现方式：指针自增遍历，直到遇到空字符。
 *   str: 待测量的字符串（只读）
 *   return: 字符个数（size_t 类型，无符号整数）
 */
size_t my_strlen(const char *str)
{
    // 防御性检查：如果传入空指针，返回 0
    if (str == NULL) {
        return 0;
    }

    const char *ptr = str;   // 保存起始位置，用于最后计算偏移

    // 只要 *ptr 不是结束符，就继续向后移动指针
    while (*ptr != '\0') {
        ptr++;               // 指针指向下一个字符
    }

    // 返回两个指针之间的元素个数，即字符串长度
    return (size_t)(ptr - str);
}

int main(void)
{
    printf("=== My strlen vs Standard strlen ===\n\n");

    // 定义几个测试用例
    const char *tests[] = {
        "",                // 空字符串
        "Hello",           // 普通英文
        "C Programming",   // 含空格
        "嵌入式C语言",      // 含中文（多字节字符，strlen 返回字节数）
        "12345\06789"      // 含数字，中间无空字符
    };
    int num_tests = sizeof(tests) / sizeof(tests[0]);

    int all_passed = 1;   // 标记是否全部测试通过

    for (int i = 0; i < num_tests; i++)
    {
        size_t my_len   = my_strlen(tests[i]);   // 调用自己的函数
        size_t std_len  = strlen(tests[i]);      // 调用标准库

        printf("Test %d: \"%s\"\n", i + 1, tests[i]);
        printf("  my_strlen: %zu\n", my_len);
        printf("  strlen   : %zu\n", std_len);

        if (my_len == std_len) {
            printf("  -> PASS\n\n");
        } else {
            printf("  -> FAIL (should be %zu, got %zu)\n\n", std_len, my_len);
            all_passed = 0;
        }
    }

    if (all_passed) {
        printf("All tests passed!\n");
    } else {
        printf("Some tests failed. Please check your implementation.\n");
    }

    return 0;
}