#include <stdio.h>
#include <stdint.h>

// 模拟一个 16 位的 GPIO 配置寄存器
typedef struct {
    uint16_t pin0_mode  : 2;   // 引脚 0 模式
    uint16_t pin1_mode  : 2;   // 引脚 1 模式
    uint16_t pin2_mode  : 2;   // 引脚 2 模式
    uint16_t pin3_mode  : 2;   // 引脚 3 模式
    uint16_t reserved   : 4;   // 保留
    uint16_t enable     : 1;   // 全局使能
    uint16_t unused     : 3;   // 未使用
} GPIO_Config_Bits;

typedef union {
    GPIO_Config_Bits bits;
    uint16_t         raw;
} GPIO_Config;

int main(void) {
    GPIO_Config config;
    config.raw = 0x0000;         // 整体清零

    config.bits.pin0_mode = 1;   // PA0 → 输出模式
    config.bits.enable    = 1;   // 使能 GPIO

    printf("After config:\n");
    printf("  raw = 0x%04X\n", config.raw);
    printf("  pin0_mode = %u\n", config.bits.pin0_mode);
    printf("  enable    = %u\n", config.bits.enable);

    return 0;
}