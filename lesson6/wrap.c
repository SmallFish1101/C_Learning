#include <stdio.h>
#include <limits.h>    // 用于 USHRT_MAX 等宏（可选）

int main(void) {
    // 无符号短整型：2 字节，范围 0 ~ 65535
    unsigned short x = 0;
    printf("Initial x = %hu\n", x);

    x = x - 1;          // 下溢：0 - 1 回环到最大值
    printf("After x - 1: x = %hu\n", x);

    // 验证最大值
    printf("USHRT_MAX = %hu (expected)\n", USHRT_MAX);

    unsigned short y = 65535;
    printf("Initial y = %hu\n", y);

    y = y + 1;          // 上溢：65535 + 1 回环到 0
    printf("After y + 1: y = %hu\n", y);

    return 0;
}