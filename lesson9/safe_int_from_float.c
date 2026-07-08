#include <stdio.h>
#include <math.h>      // floor, round, fabs
#include <limits.h>    // INT_MAX, INT_MIN
#include <stdbool.h>   // bool, true, false

/*
 * safe_int_from_float:
 *   安全地将 float 转换为 int，如果溢出则返回 false。
 *   value:  要转换的浮点数
 *   result: 输出参数，存放转换结果（仅当 safe 返回 true 时有效）
 *   return: true 表示转换成功，false 表示溢出或无效输入
 *
 *   原理：先用比较确保 value 在 [INT_MIN, INT_MAX] 范围内，
 *         然后用 (int) 截断小数（也可以换成 floor 或 round）。
 */
bool safe_int_from_float(float value, int *result)
{
    // 检查 NaN（非数）：NaN 与任何值比较都返回 false，因此自我比较可判别
    if (value != value) {
        return false;              // NaN 不能转为 int
    }

    // 检查是否在 int 可表示范围内
    // 注意：直接写成 value > INT_MAX 可能因浮点精度而误判，
    // 但在此类教学中可以接受。
    if (value > (float)INT_MAX || value < (float)INT_MIN) {
        return false;              // 超出 int 范围，拒绝转换
    }

    *result = (int)value;          // 安全截断小数（也可用 floor 或 round）
    return true;
}

int main(void)
{
    float f;
    int safe_val;

    printf("=== Safe Float to Int Conversion ===\n\n");

    // ---- 1. 正常转换 ----
    f = 3.14f;
    if (safe_int_from_float(f, &safe_val)) {
        printf("1. %.2f -> %d (safe)\n", f, safe_val);
    } else {
        printf("1. %.2f conversion failed!\n", f);
    }

    // ---- 2. 负数转换 ----
    f = -7.89f;
    if (safe_int_from_float(f, &safe_val)) {
        printf("2. %.2f -> %d (safe)\n", f, safe_val);
    } else {
        printf("2. %.2f conversion failed!\n", f);
    }

    // ---- 3. 边界值：INT_MAX ----
    f = (float)INT_MAX;            // 2,147,483,647.0f 可能被舍入
    if (safe_int_from_float(f, &safe_val)) {
        printf("3. INT_MAX float -> %d (safe)\n", safe_val);
    } else {
        printf("3. INT_MAX conversion failed! (might exceed int range due to float precision)\n");
    }

    // ---- 4. 超出 int 范围（溢出）----
    f = 1e20f;                     // 1 * 10^20，远超 int 范围
    if (safe_int_from_float(f, &safe_val)) {
        printf("4. 1e20 -> %d (should not happen!)\n", safe_val);
    } else {
        printf("4. 1e20 conversion correctly rejected (overflow)\n");
    }

    // ---- 5. 比较直接截断、floor、round 的效果 ----
    f = -3.7f;
    printf("\n--- Comparison of rounding methods ---\n");
    printf("   Original value: %.2f\n", f);
    printf("   Direct cast (int)   : %d (truncation towards zero)\n", (int)f);
    printf("   floor(f)            : %.0f (towards negative infinity)\n", floor(f));
    printf("   round(f)            : %.0f (nearest integer)\n", round(f));

    f = 3.7f;
    printf("   Original value: %.2f\n", f);
    printf("   Direct cast (int)   : %d\n", (int)f);
    printf("   floor(f)            : %.0f\n", floor(f));
    printf("   round(f)            : %.0f\n", round(f));

    return 0;
}