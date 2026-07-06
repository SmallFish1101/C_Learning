#include <stdio.h>

int main(void) {

    // 示例1：累加 0.1 十次 vs 直接写 1.0
    float sum = 0.0f;
    for (int i = 0; i < 10; ++i) {
        sum += 0.1f;
    }
    printf("Test 1: sum of 10 * 0.1 vs 1.0\n");
    printf("  sum  = %.20f\n", sum);
    printf("  1.0  = %.20f\n", 1.0f);
    if (sum == 1.0f) {
        printf("  Result: EQUAL (unexpected)\n");
    } else {
        printf("  Result: NOT EQUAL (correct due to error)\n");
    }


    // 示例2：double 下的 0.1 + 0.2 == 0.3
    double a = 0.1;
    double b = 0.2;
    double c = 0.3;
    printf("\nTest 2: 0.1 + 0.2 vs 0.3 (double)\n");
    printf("  0.1 + 0.2 = %.20f\n", a + b);
    printf("  0.3       = %.20f\n", c);
    if (a + b == c) {
        printf("  Result: EQUAL\n");
    } else {
        printf("  Result: NOT EQUAL (typical floating-point error)\n");
    }

    // 正确姿势：差值比较
    double diff = (a + b) - c;
    printf("\nThe correct way: check if difference is very small\n");
    printf("  diff = %e\n", diff);
    if (diff < 1e-9 && diff > -1e-9) {
        printf("  APPROXIMATELY EQUAL (good for engineering)\n");
    } else {
        printf("  Not close enough.\n");
    }

    return 0;
}