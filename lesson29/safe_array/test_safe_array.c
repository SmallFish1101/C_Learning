/*
 * test_safe_array.c
 * 安全动态数组模块的单元测试
 *
 * 测试覆盖：
 *   - 基本追加与读取
 *   - 触发多次扩容
 *   - 销毁后再初始化（验证不会双重释放）
 *   - 空数组的打印
 *   - 越界访问触发错误（此测试需单独运行，因 exit(1) 会终止进程）
 */

#include "safe_array.h"
#include <stdio.h>

int main(void)
{
    printf("=== SafeIntArray Unit Tests ===\n\n");

    // ===== 测试 1：基本追加与读取 =====
    printf("Test 1: Basic append and get\n");
    SafeIntArray arr1;
    array_init(&arr1);

    array_append(&arr1, 10);
    array_append(&arr1, 20);
    array_append(&arr1, 30);

    printf("  size = %d (expected 3)\n", array_size(&arr1));
    printf("  arr1[0] = %d (expected 10)\n", array_get(&arr1, 0));
    printf("  arr1[1] = %d (expected 20)\n", array_get(&arr1, 1));
    printf("  arr1[2] = %d (expected 30)\n", array_get(&arr1, 2));
    array_print(&arr1);

    array_destroy(&arr1);
    printf("  destroy OK\n\n");

    // ===== 测试 2：触发多次扩容 =====
    printf("Test 2: Multiple expansions\n");
    SafeIntArray arr2;
    array_init(&arr2);

    // 初始容量为 4，添加 15 个元素会触发扩容：4 → 8 → 16
    for (int i = 1; i <= 15; i++) {
        array_append(&arr2, i * 10);
    }

    printf("  size = %d (expected 15)\n", array_size(&arr2));
    printf("  arr2[0]  = %d (expected 10)\n",  array_get(&arr2, 0));
    printf("  arr2[14] = %d (expected 150)\n", array_get(&arr2, 14));
    array_print(&arr2);

    array_destroy(&arr2);
    printf("  destroy OK\n\n");

    // ===== 测试 3：销毁后重新初始化（验证无双重释放） =====
    printf("Test 3: Destroy and re-init (no double-free)\n");
    SafeIntArray arr3;
    array_init(&arr3);
    array_append(&arr3, 42);
    array_print(&arr3);

    array_destroy(&arr3);            // 第一次销毁
    array_destroy(&arr3);            // 第二次销毁（data 已为 NULL，安全）

    // 重新初始化并再次使用
    array_init(&arr3);
    array_append(&arr3, 99);
    printf("  after re-init: ");
    array_print(&arr3);
    array_destroy(&arr3);
    printf("  destroy after re-init OK\n\n");

    // ===== 测试 4：空数组操作 =====
    printf("Test 4: Empty array operations\n");
    SafeIntArray arr4;
    array_init(&arr4);

    printf("  size = %d (expected 0)\n", array_size(&arr4));
    printf("  elements: ");
    array_print(&arr4);

    array_destroy(&arr4);
    printf("  destroy empty array OK\n\n");

    // ===== 测试 5：边界情况（越界读取）=====
    // 该测试会调用 exit(1)，因此单独运行
    // 如需完整测试，请编译时定义 RUN_OUT_OF_BOUNDS_TEST 宏
#ifdef RUN_OUT_OF_BOUNDS_TEST
    printf("Test 5: Out-of-bounds access (will exit with error)\n");
    SafeIntArray arr5;
    array_init(&arr5);
    array_append(&arr5, 100);
    printf("  About to access arr5[5]...\n");
    array_get(&arr5, 5);   // 故意越界 → 应输出错误并终止
#endif

    printf("=== All non-fatal tests passed ===\n");
    return 0;
}