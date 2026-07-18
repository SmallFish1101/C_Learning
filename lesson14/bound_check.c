/*
 * bound_check.c
 * 第14课 实例2：观察数组越界的危害
 *
 * 警告：此代码故意制造越界访问，目的是让你亲眼看到后果。
 * 运行结果因编译器和优化级别而异，这正是“未定义行为”的表现。
 */

#include <stdio.h>

int main(void) {
    // 定义三个数组，观察它们在内存中的位置
    int before[2] = {100, 200};     // 在 arr 之前（可能）
    int arr[3]    = {10, 20, 30};   // 目标数组
    int after[2]  = {900, 999};     // 在 arr 之后（可能）

    printf("=== Memory Layout ===\n");
    printf("before: %p %p\n", (void*)&before[0], (void*)&before[1]);
    printf("arr:    %p %p %p\n", (void*)&arr[0], (void*)&arr[1], (void*)&arr[2]);
    printf("after:  %p %p\n", (void*)&after[0], (void*)&after[1]);

    printf("\n=== Before Out-of-Bounds ===\n");
    printf("before[0] = %d, before[1] = %d\n", before[0], before[1]);
    printf("arr[0] = %d, arr[1] = %d, arr[2] = %d\n", arr[0], arr[1], arr[2]);
    printf("after[0] = %d, after[1] = %d\n", after[0], after[1]);

    // 故意越界写入
    printf("\n--- Writing arr[3] = 777 (out of bounds!) ---\n");
    arr[3] = 777;   // 越界！可能覆盖 after[0]

    printf("--- Writing arr[-1] = -999 (out of bounds!) ---\n");
    arr[-1] = -999; // 越界！可能覆盖 before[1]

    printf("\n=== After Out-of-Bounds ===\n");
    printf("before[0] = %d, before[1] = %d\n", before[0], before[1]);
    printf("arr[0] = %d, arr[1] = %d, arr[2] = %d\n", arr[0], arr[1], arr[2]);
    printf("after[0] = %d, after[1] = %d\n", after[0], after[1]);

    printf("\n*** OBSERVE: If 'before' or 'after' values changed, ***\n");
    printf("*** it means our out-of-bounds write corrupted them. ***\n");

    return 0;
}