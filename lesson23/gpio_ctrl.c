#include <stdio.h>
#include <stdint.h>

// 模拟 GPIO 控制寄存器的位域定义
typedef struct {
    uint32_t pin0_mode  : 2;   // 引脚 0 模式：0=输入，1=输出，2=复用，3=模拟
    uint32_t pin1_mode  : 2;   // 引脚 1 模式
    uint32_t pin2_mode  : 2;   // 引脚 2 模式
    uint32_t reserved   : 2;   // 保留
    uint32_t enable     : 1;   // 全局使能
    uint32_t unused     : 23;  // 未使用
} GPIO_CTRL_Bits;

// 联合体：既可整体读/写，也可按位域操作
typedef union {
    uint32_t        raw;
    GPIO_CTRL_Bits  bits;
} GPIO_CTRL_Register;

int main(void) {
    GPIO_CTRL_Register reg;
    reg.raw = 0x00000000;   // 初始全清零

    // 通过位域配置
    reg.bits.pin0_mode = 1;    // 引脚 0 设为输出模式
    reg.bits.enable    = 1;    // 使能端口

    printf("After config:\n");
    printf("  reg.raw       = 0x%08X\n", reg.raw);
    printf("  pin0_mode     = %u\n", reg.bits.pin0_mode);
    printf("  enable        = %u\n", reg.bits.enable);

    // 整体清零
    reg.raw = 0x00000000;
    printf("After clear: reg.raw = 0x%08X\n", reg.raw);

    return 0;
}