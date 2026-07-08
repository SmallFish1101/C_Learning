#include <stdio.h>
#include <stdint.h>   // 提供 int8_t, uint8_t 等固定宽度类型

int main(void)
{
    printf("=== Analyze Implicit Type Conversions ===\n\n");

    // ----- 1. 整型提升：两个 int8_t 相加 -----
    int8_t a = 100;
    int8_t b = 28;
    // a 和 b 在运算前都被提升为 int（因为 int8_t 比 int 小）
    // 加法在 int 下进行，结果为 128，仍在 int8_t 范围内（-128~127）？
    // 注意：128 实际上是超出 int8_t 的正数范围（最大 127），所以赋值回 int8_t 时会发生“回绕”
    int8_t c = a + b;
    printf("1. int8_t + int8_t\n");
    printf("   a = %d, b = %d\n", a, b);
    printf("   a + b (as int) = %d\n", a + b);          // 提升为 int 计算
    printf("   c = a + b stored in int8_t = %d\n", c); // 截断回 int8_t，可能变成 -128

    // ----- 2. int8_t 与 int 混合 -----
    int8_t d = 70;
    int e = 200;
    // d 提升为 int，然后与 e 相加，结果为 int 270
    int f = d + e;
    printf("\n2. int8_t + int\n");
    printf("   d = %d, e = %d\n", d, e);
    printf("   d + e (as int) = %d\n", f);

    // ----- 3. uint8_t 与 int 混合 -----
    uint8_t g = 200;      // 200 在 0~255 内
    int h = -10;
    // 运算前，g 会提升为 int（因为它比 int 小），此时值为 200
    // h 是 int，两者相加直接用 int，结果为 190
    int i = g + h;
    printf("\n3. uint8_t + int (negative)\n");
    printf("   g = %u, h = %d\n", g, h);
    printf("   g + h (as int) = %d\n", i);

    // ----- 4. 有符号 int 与 无符号 int 混合 -----
    int j = -5;
    unsigned int k = 10;
    // 根据“算术转换”，int 会转换为 unsigned int
    // -5 转换为 unsigned int 会变成一个很大的数（UINT_MAX - 4）
    unsigned int l = j + k;   // 即 (UINT_MAX - 4) + 10，会回绕到 5（因为溢出后模运算）
    printf("\n4. int + unsigned int\n");
    printf("   j = %d, k = %u\n", j, k);
    printf("   j + k (as unsigned int) = %u\n", l);
    // 解释：-5 作为 unsigned int 是 4294967291 (假设 32 位)，加 10 得 4294967301，但只能存 32 位，结果是 5

    // ----- 5. uint32_t 赋值给 uint16_t（截断）-----
    uint32_t m = 0x12345678;   // 32 位值
    uint16_t n = m;            // 只保留低 16 位：0x5678
    printf("\n5. Truncation: uint32_t -> uint16_t\n");
    printf("   m = 0x%08X\n", m);
    printf("   n = 0x%04X (low 16 bits)\n", n);

    // ----- 6. 浮点数转整数（截断小数）-----
    float pi = 3.14159f;
    int pi_int = pi;           // 编译器隐式将 float 转为 int，丢弃小数部分
    printf("\n6. float to int (truncation)\n");
    printf("   pi = %f\n", pi);
    printf("   pi_int = %d\n", pi_int);

    return 0;
}