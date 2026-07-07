#include <stdio.h>
#include <stdint.h>

#define LED_PIN   3

int main(void) {
    uint8_t port = 0x00;

    // 置位
    port |= (1 << LED_PIN);
    printf("After set:   0x%02X\n", port);

    // 检测
    if (port & (1 << LED_PIN))
        printf("Bit is set.\n");

    // 翻转
    port ^= (1 << LED_PIN);
    printf("After toggle: 0x%02X\n", port);

    // 清零
    port |= (1 << LED_PIN);    // 先点亮
    port &= ~(1 << LED_PIN);   // 再熄灭
    printf("After clear: 0x%02X\n", port);

    return 0;
}