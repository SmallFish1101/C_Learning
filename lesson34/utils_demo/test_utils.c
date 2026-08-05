/*
 * test_utils.c
 * 第34课 练习一：测试 utils 模块的每个函数
 *
 * 测试策略：
 *   - 安全输入函数：通过交互式测试（用户输入正确/错误值）
 *   - 校验函数：通过自动化测试（预设合法/非法数据）
 *   - 随机数函数：生成多组数据，肉眼检查范围
 */

#include <stdio.h>    // printf, putchar
#include <stdlib.h>   // srand
#include <time.h>     // time
#include "utils.h"

// ========== 辅助宏：断言输出 ==========
#define TEST(cond, name) \
    do { \
        if (cond) printf("  [PASS] %s\n", name); \
        else      printf("  [FAIL] %s\n", name); \
    } while(0)

int main(void)
{
    printf("=== Testing utils Library ===\n\n");

    // ===== 1. 测试 safe_read_line =====
    printf("1. safe_read_line:\n");
    {
        printf("   Enter some text (should be echoed below): ");
        char buf[100];
        int len = safe_read_line(buf, sizeof(buf));
        printf("   You entered: \"%s\" (length=%d)\n\n", buf, len);
    }

    // ===== 2. 测试 read_int =====
    printf("2. read_int:\n");
    {
        // 故意输入错误值（如 "abc" 或 "12.5" 或 "12abc"）
        // 然后在提示后输入正确值（如 42）
        int val = read_int("   Enter an integer (try 'abc' first, then 42): ");
        printf("   Got: %d\n\n", val);
    }

    // ===== 3. 测试 read_double =====
    printf("3. read_double:\n");
    {
        double val = read_double("   Enter a number (e.g., 3.14): ");
        printf("   Got: %.2f\n\n", val);
    }

    // ===== 4. 测试 is_valid_name =====
    printf("4. is_valid_name:\n");
    {
        TEST(!is_valid_name("", 50),    "empty name rejected");
        TEST(!is_valid_name("abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz", 50),
             "too long name rejected");
        TEST( is_valid_name("Zhang San", 50), "valid name accepted");
    }
    printf("\n");

    // ===== 5. 测试 is_valid_phone =====
    printf("5. is_valid_phone:\n");
    {
        TEST(!is_valid_phone(""),             "empty phone rejected");
        TEST(!is_valid_phone("138-abc-4567"), "phone with letters rejected");
        TEST( is_valid_phone("13800138000"),   "pure digits accepted");
        TEST( is_valid_phone("138-001-38000"), "phone with hyphens accepted");
    }
    printf("\n");

    // ===== 6. 测试 is_valid_age =====
    printf("6. is_valid_age:\n");
    {
        int age;
        TEST(!is_valid_age("", &age),         "empty age rejected");
        TEST(!is_valid_age("abc", &age),      "non-numeric age rejected");
        TEST(!is_valid_age("20abc", &age),    "age with extra chars rejected");
        TEST(!is_valid_age("0", &age),        "age 0 rejected");
        TEST(!is_valid_age("151", &age),      "age 151 rejected");
        TEST( is_valid_age("20", &age) && age == 20, "valid age (20) accepted");
        TEST( is_valid_age("150", &age) && age == 150, "max age (150) accepted");
        TEST( is_valid_age("1", &age) && age == 1, "min age (1) accepted");
    }
    printf("\n");

    // ===== 7. 测试 random_range =====
    printf("7. random_range:\n");
    {
        srand((unsigned)time(NULL));

        // 生成 10 个 [1, 6] 的随机数（模拟掷骰子）
        printf("   Rolling dice (1-6): ");
        for (int i = 0; i < 10; i++) {
            printf("%d ", random_range(1, 6));
        }
        printf("\n");

        // 生成 5 个 [5, 15] 的随机数（验证范围）
        printf("   Random in [5, 15]: ");
        int all_ok = 1;
        for (int i = 0; i < 5; i++) {
            int r = random_range(5, 15);
            printf("%d ", r);
            if (r < 5 || r > 15) all_ok = 0;
        }
        printf("\n");
        TEST(all_ok, "all values within range [5, 15]");
    }

    printf("\n=== Testing Complete ===\n");
    return 0;
}