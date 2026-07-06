#include <stdio.h>
#include <limits.h>

int main(void) {
    // 无符号整数下溢：0 - 1 → 最大值
    unsigned int x = 0;
    x = x - 1;
    printf("unsigned 0 - 1 = %u\n", x);

    // 有符号整数上溢：INT_MAX + 1 → 通常变成 INT_MIN
    int y = INT_MAX;
    printf("INT_MAX = %d\n", y);
    y = y + 1;
    printf("INT_MAX + 1 = %d\n", y);

    return 0;
}