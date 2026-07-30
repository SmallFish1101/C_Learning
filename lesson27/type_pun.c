#include <stdio.h>
#include <stdint.h>

typedef union {
    float    f_val;
    uint32_t u_val;
} FloatPun;

int main(void) {
    FloatPun data;
    data.f_val = 3.14f;

    printf("Float: %.2f\n", data.f_val);
    printf("As hex: 0x%08X\n", data.u_val);
    // 在调试时可以用 u_val 查看浮点数在内存中的原始二进制
    return 0;
}