/*
 * safe_strcat.c
 * 第20课 练习二：安全字符串拼接函数
 *
 * 功能：实现安全的字符串拼接，避免传统 strcat 的缓冲区溢出。
 *       若目标缓冲区空间不足，将截断 src 并保证 dest 以 '\0' 结尾。
 */

#include <stdio.h>   // printf
#include <string.h>  // strlen（用于测试对比）
#include <stddef.h>  // size_t（通常已被上述头文件包含）

/*
 * safe_strcat:
 *   将 src 拼接到 dest 末尾，并保证不会超出 dest_size 限制。
 *   函数总是确保 dest 以 '\0' 结尾（即使在截断的情况下）。
 *
 *   参数:
 *     dest      : 目标字符数组
 *     dest_size : 目标数组的总大小（字节数）
 *     src       : 要拼接的源字符串
 *
 *   返回值:
 *     实际追加到 dest 中的字符数（不含结尾 '\0'）。
 *     如果发生截断，返回值可能小于 strlen(src)。
 */
int safe_strcat(char *dest, size_t dest_size, const char *src)
{
    // 1. 参数检查：任一指针为空则直接返回 0
    if (dest == NULL || src == NULL) {
        return 0;
    }

    // 2. 找到 dest 中原有字符串的末尾位置（dest_len 为已用字符数，不含 '\0'）
    size_t dest_len = 0;
    while (dest[dest_len] != '\0') {
        dest_len++;
        // 为防止 dest 不是一个合法的字符串（没有 '\0'），当扫描到 dest_size 时强制停止
        if (dest_len >= dest_size) {
            // dest 没有以 '\0' 结尾，强行设置并返回
            if (dest_size > 0) {
                dest[dest_size - 1] = '\0';
            }
            return 0;
        }
    }

    // 3. 计算剩余可用空间（包括结尾 '\0'，所以最多可容纳 remaining-1 个字符）
    size_t remaining = dest_size - dest_len;

    // 4. 如果剩余空间不足 1（即连 '\0' 都放不下），无法拼接任何字符
    if (remaining < 1) {
        return 0;
    }

    // 5. 复制 src 到 dest 的末尾，最多复制 remaining - 1 个字符
    size_t copied = 0;           // 实际复制的字符数
    char *p = dest + dest_len;   // 指向 dest 末尾 '\0' 的位置

    // 复制直到遇到 src 的 '\0' 或者达到最大可复制字符数
    while (*src != '\0' && copied < remaining - 1) {
        *p++ = *src++;   // 复制一个字符并移动两个指针
        copied++;
    }

    // 6. 添加结尾的 '\0'
    *p = '\0';

    // 7. 返回实际复制的字符数
    return (int)copied;
}

// ========== 测试用例 ==========
int main(void)
{
    printf("=== Safe strcat Demo ===\n\n");

    // 测试用例结构
    struct {
        char init[50];          // 目标缓冲区初始内容
        size_t buf_size;        // 缓冲区总大小
        const char *src;        // 要拼接的字符串
        const char *expected;   // 期望结果（整个 dest）
        int expected_ret;       // 期望返回值
    } tests[] = {
        // 1. 正常拼接，空间充足
        {"Hello ", 50, "World!", "Hello World!", 6},
        // 2. 目标初始就是空串
        {"", 20, "Hi", "Hi", 2},
        // 3. 空间刚好够（dest_len + src_len + 1 == dest_size）
        {"AB", 5, "CD", "ABCD", 2},   // "AB"(2) + 2 + 1 = 5
        // 4. 空间不足，发生截断（只复制部分字符）
        {"Hello", 10, " World!!!!", "Hello Wor", 4},   // 剩余5字节，复制4个字符，留1个给'\0'
        // 5. 缓冲区只剩 1 字节（只能放 '\0'，无法拼接）
        {"Hello", 6, " World", "Hello", 0},   // dest_len=5, remaining=1，无法复制
        // 6. src 为空串
        {"Hello", 50, "", "Hello", 0},
        // 7. 缓冲区大小非常小，只有 1 字节，初始为空
        {"", 1, "abc", "", 0},           // 只能放 '\0'
        // 8. 测试 dest 刚好装满（dest_len == dest_size）
        // 这里手动构造一个没有空间的情况：buffer 大小为 5，内容 "1234" 已用4字节，加上 '\0' 刚好满
        // 但我们的初始化字符串是 "1234"，自动带 '\0'，所以 dest_len=4，remaining=1，无法拼接
        {"1234", 5, "5", "1234", 0},
    };

    int num_tests = sizeof(tests) / sizeof(tests[0]);
    int all_passed = 1;

    for (int i = 0; i < num_tests; i++)
    {
        // 复制初始内容到可修改的缓冲区
        char buffer[50];
        strcpy(buffer, tests[i].init);   // 确保 buffer 以 '\0' 开头
        // 但要注意：如果 init 长度超过 buffer 大小（比如测试7），strcpy 会溢出，我们手动限制
        // 为测试安全，用 strncpy 并手动加 '\0'
        // 简化：因为 init 都在测试范围内，直接 strcpy 没问题

        size_t buf_size = tests[i].buf_size;
        const char *src = tests[i].src;

        // 调用 safe_strcat
        int ret = safe_strcat(buffer, buf_size, src);

        // 获取实际结果
        const char *actual = buffer;
        const char *expected = tests[i].expected;

        printf("Test %d:\n", i + 1);
        printf("  init=\"%s\", buf_size=%zu, src=\"%s\"\n",
               tests[i].init, buf_size, src);
        printf("  result   : \"%s\" (ret=%d)\n", actual, ret);
        printf("  expected : \"%s\" (ret=%d)\n", expected, tests[i].expected_ret);

        int match = (strcmp(actual, expected) == 0) && (ret == tests[i].expected_ret);
        if (match) {
            printf("  => PASS\n\n");
        } else {
            printf("  => FAIL\n\n");
            all_passed = 0;
        }
    }

    if (all_passed) {
        printf("All tests passed!\n");
    } else {
        printf("Some tests failed. Check implementation.\n");
    }

    return 0;
}