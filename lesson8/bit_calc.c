#include <stdio.h>
#include <stdint.h>   // 提供 uint8_t 类型

int main(void)
{
    uint8_t value;    // 存放输入的 8 位数值 (0~255)
    int bit;          // 存放输入的位号 (0~7)

    // 1. 获取用户输入
    printf("=== Bit Calculator ===\n");
    printf("Enter an 8-bit unsigned integer (0-255): ");
    scanf("%hhu", &value);          // %hhu 是读取 unsigned char 的格式符

    printf("Enter bit position (0-7): ");
    scanf("%d", &bit);

    // 2. 检查位号是否合法
    if (bit < 0 || bit > 7) {
        printf("Error: bit position must be 0-7.\n");
        return 1;                   // 非正常退出
    }

    // 3. 显示输入信息
    printf("\nOriginal value: %u (0x%02X)\n", value, value);
    printf("Bit position: %d\n", bit);

    // 4. 获取该位的值（读操作）
    //    (1 << bit) 生成只有目标位为 1、其余为 0 的掩码
    //    value & 掩码 若结果非 0，说明该位为 1
    uint8_t bit_value = (value >> bit) & 1;  // 方法一：右移后取最低位
    // 注释：也可写成 (value & (1 << bit)) ? 1 : 0;
    printf("Current value of bit %d: %u\n", bit, bit_value);

    // 5. 置位（Set）—— 将指定位设为 1，不影响其他位
    //    使用 OR 运算：value | (1 << bit)
    uint8_t set_result = value | (1 << bit);
    printf("After setting bit %d to 1: %u (0x%02X)\n", bit, set_result, set_result);

    // 6. 清零（Clear）—— 将指定位设为 0，不影响其他位
    //    使用 AND 运算 + 取反：value & ~(1 << bit)
    //    ~(1 << bit) 生成一个只有目标位为 0、其余位为 1 的掩码
    uint8_t clear_result = value & ~(1 << bit);
    printf("After clearing bit %d to 0: %u (0x%02X)\n", bit, clear_result, clear_result);

    // 7. （附加）翻转（Toggle）—— 将指定位取反
    //    使用 XOR 运算：value ^ (1 << bit)
    uint8_t toggle_result = value ^ (1 << bit);
    printf("After toggling bit %d: %u (0x%02X)\n", bit, toggle_result, toggle_result);

    return 0;
}