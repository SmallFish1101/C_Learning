#include <stdio.h>
#include <stdint.h>

#define LED_RED     2   // 红色 LED 接在 bit 2
#define LED_GREEN   4   // 绿色 LED 接在 bit 4

int main(void)
{
    uint8_t port = 0x00;                // 所有 LED 初始都熄灭

    // 1. 点亮红色 LED（置位操作）
    port |= (1 << LED_RED);             // 将 port 的第 2 位置为 1，其他位不变
    printf("Red on:   0x%02X\n", port); // 应输出 0x04

    // 2. 同时点亮红、绿 LED
    port |= (1 << LED_GREEN);           // 再将第 4 位置为 1
    printf("Both on:  0x%02X\n", port); // 应输出 0x14 (二进制 0001 0100)

    // 3. 检查红色 LED 是否亮着（位检测）
    if (port & (1 << LED_RED))          // 如果第 2 位为 1，条件成立
        printf("Red LED is ON\n");

    // 4. 熄灭绿色 LED（清零操作）
    port &= ~(1 << LED_GREEN);          // 将第 4 位清零，其他位不变
    printf("Green off: 0x%02X\n", port); // 应输出 0x04

    // 5. 翻转红色 LED 的状态（取反）
    port ^= (1 << LED_RED);             // 如果原来是 1 变成 0，原来是 0 变成 1
    printf("Red toggle: 0x%02X\n", port); // 应输出 0x00

    return 0;
}