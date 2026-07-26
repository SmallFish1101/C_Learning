/*
 * float_inspect.c
 * 第23课 练习三（选做）：用位域 + 联合体分解浮点数（IEEE 754）
 *
 * 功能：输入一个 float，用位域提取符号、指数、尾数，
 *       与标准库函数 signbit / frexp 对比验证。
 */

#include <stdio.h>   // printf, putchar
#include <stdint.h>  // uint32_t
#include <math.h>    // signbit, frexp (需链接 -lm)
#include <float.h>   // FLT_RADIX (=2)

// ========== 1. 位域定义（依赖 GCC/MinGW 的分配顺序）==========
/*
 * FloatBits:
 *   将一个 32 位浮点数按 IEEE 754 布局拆为三个字段。
 *   注意：位域分配的位序依赖编译器实现，本练习以 GCC 下
 *   小端字节序的布局为准（低位在先）。
 */
typedef struct {
    unsigned int mantissa : 23;   // 尾数（bit 0 ~ 22）
    unsigned int exponent : 8;    // 指数（bit 23 ~ 30）
    unsigned int sign     : 1;    // 符号（bit 31）
} FloatBits;

// ========== 2. 联合体：同一内存两种解读方式 ==========
/*
 * FloatInspector:
 *   value: 按浮点数读写
 *   bits : 按位域查看内部细节
 */
typedef union {
    float     value;
    FloatBits bits;
} FloatInspector;

// ========== 3. 辅助函数：打印 32 位二进制 ==========
/*
 * print_binary32:
 *   以二进制形式打印一个 32 位无符号整数。
 *   同时标注符号、指数、尾数的区间。
 */
void print_binary32(uint32_t val)
{
    // 逐位打印，bit 31 到 bit 0
    for (int i = 31; i >= 0; i--)
    {
        putchar(((val >> i) & 1U) ? '1' : '0');

        // 在字段分界线处添加分隔符
        if (i == 31) {                  // 刚打完符号位
            printf(" | ");
        } else if (i == 23) {           // 打完指数位
            printf(" | ");
        } else if (i % 4 == 0 && i != 0) {
            putchar(' ');               // 半字节分隔
        }
    }
    printf("\n");
    printf("  ^ sign   ^ exponent (8 bits)  ^ mantissa (23 bits)\n");
}

int main(void)
{
    printf("=== IEEE 754 Float Inspector ===\n\n");

    // 测试几个浮点数
    float test_values[] = {
         3.14f,
        -3.14f,
         0.0f,
        -0.0f,      // 负零，符号位为 1
         1.0f,
         2.0f,
        FLT_MIN,    // 最小规约正浮点数
        FLT_MAX     // 最大有限浮点数
    };
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);

    for (int idx = 0; idx < num_tests; idx++)
    {
        FloatInspector fi;
        fi.value = test_values[idx];

        // 获取原始 32 位整数（用于二进制打印）
        // 通过强制类型转换将 float 的地址解释为 uint32_t*
        uint32_t raw = *(uint32_t*)&fi.value;

        printf("--- float: %g ---\n", fi.value);
        printf("  binary: ");
        print_binary32(raw);

        printf("  sign    : %u (%s)\n",
               fi.bits.sign, fi.bits.sign ? "negative" : "positive");

        printf("  exponent: 0x%02X (%u) -> actual exponent = %d\n",
               fi.bits.exponent, fi.bits.exponent,
               (int)fi.bits.exponent - 127);

        printf("  mantissa: 0x%06X (%u)\n",
               fi.bits.mantissa, fi.bits.mantissa);

        // ===== 与标准库函数对比 =====
        // signbit(f) 返回非零值若 f 为负
        int std_sign = signbit(fi.value) ? 1 : 0;
        printf("  stdlib signbit: %d (match=%s)\n",
               std_sign,
               (std_sign == (int)fi.bits.sign) ? "yes" : "NO");

        // frexp(f, &exp) 将 f 分解为 frac * 2^exp
        int frexp_exp;
        float frac = frexpf(fi.value, &frexp_exp);
        // 注意: frexp 返回的指数与 IEEE 编码的指数差一个偏置关系
        // IEEE 指数 E 存的是 (实际指数 + 127)
        // frexp 返回的是实际指数（使得 0.5 <= |frac| < 1）
        // 对于规约数：IEEE_exponent = frexp_exp + 126
        // 因为 frexp 返回的尾数在 [0.5, 1)，而 IEEE 尾数隐含前导 1 在 [1, 2)
        int ieee_actual_exp = (int)fi.bits.exponent - 127;

        printf("  frexp: frac=%.6f exp=%d (expected IEEE actual=%d)\n\n",
               frac, frexp_exp, ieee_actual_exp);
    }

    printf("=== Done ===\n");
    return 0;
}