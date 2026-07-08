#include <stdio.h>
#include <stdint.h>
int main(void)
{
    // 1. 大整数赋值给小类型（截断）
    uint32_t big_val = 0x12345678;
    uint16_t small_val = big_val;    // 只保留低 16 位：0x5678
    printf("big: 0x%08X, small: 0x%04X\n", big_val, small_val);
    // 2. 有符号整数赋值给无符号类型（值不变，但解读变化）
    int neg = -1;
    unsigned int u = neg;            // u 将得到 UINT_MAX
    printf("negative to unsigned: %u\n", u);
    // 3. 浮点数转整数（小数截断，注意违反直觉的舍入）
    float pi = 3.14f;
    int i_pi = pi;                   // i_pi = 3
    printf("pi to int: %d\n", i_pi);
    // 4. 超出浮点数范围的转换
    float big_float = 1e20f;
    int impossible = big_float;      // 未定义行为？通常实现会取最大/最小值
    printf("large float to int: %d\n", impossible);
    return 0;
}