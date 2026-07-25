#include <stdio.h>
#include <stdint.h>

// 寄存器操作宏定义
#define SET_BIT(reg, bit)       ((reg) |= (1U << (bit)))
#define CLEAR_BIT(reg, bit)     ((reg) &= ~(1U << (bit)))
#define TOGGLE_BIT(reg, bit)    ((reg) ^= (1U << (bit)))
#define GET_BIT(reg, bit)       (((reg) >> (bit)) & 1U)

// 打印 8 位二进制
void print_binary8(uint8_t val) {
    for (int i = 7; i >= 0; i--)
        putchar((val & (1U << i)) ? '1' : '0');
}

int main(void) {
    uint8_t port = 0x00;   // 模拟一个 8 位 GPIO 端口

    printf("Initial:       "); print_binary8(port); printf("\n");

    SET_BIT(port, 2);       // 点亮 bit 2 的 LED
    printf("After set bit2: "); print_binary8(port); printf("\n");

    SET_BIT(port, 5);       // 点亮 bit 5 的 LED
    printf("After set bit5: "); print_binary8(port); printf("\n");

    CLEAR_BIT(port, 2);     // 熄灭 bit 2
    printf("After clear bit2: "); print_binary8(port); printf("\n");

    TOGGLE_BIT(port, 5);    // 翻转 bit 5（亮→灭）
    printf("After toggle bit5: "); print_binary8(port); printf("\n");

    printf("Bit 5 is %s\n", GET_BIT(port, 5) ? "SET" : "CLEAR");

    return 0;
}