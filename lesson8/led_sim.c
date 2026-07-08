#include <stdio.h>
#include <stdint.h>

#define LED_COUNT 8               // LED 总数，便于修改

// 函数声明：打印一个 uint8_t 的二进制形式
void print_binary(uint8_t value);

int main(void)
{
    uint8_t leds = 0x00;          // 初始：8 个 LED 全灭

    printf("=== 8 LED Simulator ===\n");

    // ------ 1. 点亮全部 LED ------
    // 方法：将 leds 的所有位设为 1。使用按位取反：~0 得到全 1 掩码
    leds = ~0;                    // ~0 对于 8 位就是 1111 1111 (0xFF)
    printf("1. All ON  : ");
    print_binary(leds);
    printf(" (0x%02X)\n", leds);

    // ------ 2. 熄灭全部 LED ------
    // 方法：直接赋值为 0，所有位清零
    leds = 0x00;
    printf("2. All OFF : ");
    print_binary(leds);
    printf(" (0x%02X)\n", leds);

    // ------ 3. 翻转第 3 位（bit 2）的状态 ------
    // 说明：位编号通常从 0 开始，bit 2 对应值 1<<2 = 4
    // 翻转用 XOR：leds ^ (1 << 2)
    leds ^= (1 << 2);
    printf("3. Toggle bit 2: ");
    print_binary(leds);
    printf(" (0x%02X)\n", leds);

    // 再翻转一次，验证它回到 0
    leds ^= (1 << 2);
    printf("   Toggle again : ");
    print_binary(leds);
    printf(" (0x%02X)\n", leds);

    // 手动设置一些状态，进行第 4 步检查
    leds = 0x55;   // 二进制 0101 0101，bit 0,2,4,6 亮
    printf("\nCurrent state : ");
    print_binary(leds);
    printf(" (0x%02X)\n", leds);

    // ------ 4. 检查第 5 位（bit 4）是否亮起 ------
    // 掩码 = 1 << 4 = 16 (0x10)
    if (leds & (1 << 4)) {
        printf("4. Bit 4 is ON.\n");
    } else {
        printf("4. Bit 4 is OFF.\n");
    }

    // 还可以检查任意位，展示位检测的通用写法
    int bit_to_check = 2;
    if (leds & (1 << bit_to_check)) {
        printf("   Bit %d is ON.\n", bit_to_check);
    } else {
        printf("   Bit %d is OFF.\n", bit_to_check);
    }

    return 0;
}

/*
 * 辅助函数：以二进制形式打印 8 位数值
 * 原理：从最高位 (bit 7) 到最低位 (bit 0)，逐位检查是 1 还是 0
 */
void print_binary(uint8_t value)
{
    for (int i = LED_COUNT - 1; i >= 0; i--) {
        // 将 value 右移 i 位，与 1 做 AND，取出该位
        // 根据结果输出字符 '1' 或 '0'
        if ((value >> i) & 1)
            putchar('1');
        else
            putchar('0');

        // 每 4 位加一个空格，便于阅读
        if (i == 4)
            putchar(' ');
    }
}