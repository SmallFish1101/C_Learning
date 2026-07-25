/*
 * bit_ops.c
 * 第23课 练习一：手写寄存器操作函数（函数版，非宏）
 *
 * 功能：实现 set_bit、clear_bit、toggle_bit、get_bit 四个位操作函数，
 *       用 uint32_t 模拟 32 位硬件寄存器，可视化每一步操作后的寄存器状态。
 */

#include <stdio.h>   // printf, putchar
#include <stdint.h>  // uint32_t

// ========== 辅助函数：打印 32 位二进制 ==========
/*
 * print_binary32:
 *   以二进制形式打印 32 位无符号整数，每 4 位加一个空格。
 *   参数 val: 要打印的值（只读）
 *
 *   原理：从 bit 31 到 bit 0，逐位检查是否为 1，
 *         用 (val >> i) & 1U 取出该位。
 */
void print_binary32(uint32_t val)
{
    for (int i = 31; i >= 0; i--)
    {
        // 将 val 右移 i 位，与 1 做 AND，得到该位的值（0 或 1）
        putchar(((val >> i) & 1U) ? '1' : '0');

        // 每 4 位插入一个空格，便于阅读（半字节边界）
        if (i % 4 == 0 && i != 0) {
            putchar(' ');
        }
    }
}

// ========== 位操作函数实现 ==========

/*
 * set_bit:
 *   将寄存器的第 bit 位置为 1，其他位不变。
 *   参数 reg: 指向寄存器的指针（函数会修改外部变量）
 *   参数 bit: 要置位的位索引（0~31）
 *
 *   实现：*reg |= (1U << bit)
 *   用 1U 确保移位在 32 位无符号整数上进行，避免符号扩展问题。
 */
void set_bit(uint32_t *reg, int bit)
{
    *reg |= (1U << bit);
}

/*
 * clear_bit:
 *   将寄存器的第 bit 位清零（设为 0），其他位不变。
 *   参数 reg: 指向寄存器的指针
 *   参数 bit: 要清零的位索引（0~31）
 *
 *   实现：*reg &= ~(1U << bit)
 *   ~(1U << bit) 生成一个只有目标位为 0、其余位为 1 的掩码。
 */
void clear_bit(uint32_t *reg, int bit)
{
    *reg &= ~(1U << bit);
}

/*
 * toggle_bit:
 *   翻转寄存器的第 bit 位（0→1，1→0），其他位不变。
 *   参数 reg: 指向寄存器的指针
 *   参数 bit: 要翻转的位索引（0~31）
 *
 *   实现：*reg ^= (1U << bit)
 *   异或：与 1 异或翻转，与 0 异或不变。
 */
void toggle_bit(uint32_t *reg, int bit)
{
    *reg ^= (1U << bit);
}

/*
 * get_bit:
 *   获取寄存器第 bit 位的当前值，不修改寄存器。
 *   参数 reg: 寄存器的值（值传递，不修改原变量）
 *   参数 bit: 要读取的位索引（0~31）
 *   返回: 该位的值，0 或 1
 *
 *   实现：(reg >> bit) & 1U
 *   将目标位右移到 bit 0，与 1 做 AND，提取该位。
 */
int get_bit(uint32_t reg, int bit)
{
    return (int)((reg >> bit) & 1U);
}

// ========== 主函数：测试所有位操作 ==========
int main(void)
{
    printf("=== Bit Operations via Functions ===\n\n");

    // 初始化一个 32 位寄存器（初始全为 0）
    uint32_t reg = 0x00000000;

    printf("Initial register:\n  ");
    print_binary32(reg);
    printf("  (0x%08X)\n\n", reg);

    // ---------- 测试 1：置位操作 ----------
    printf("--- Test set_bit ---\n");

    set_bit(&reg, 0);          // 置位 bit 0（最低位）
    printf("After set_bit(reg, 0):\n  ");
    print_binary32(reg);
    printf("\n");

    set_bit(&reg, 15);         // 置位 bit 15（中间位）
    printf("After set_bit(reg, 15):\n  ");
    print_binary32(reg);
    printf("\n");

    set_bit(&reg, 31);         // 置位 bit 31（最高位）
    printf("After set_bit(reg, 31):\n  ");
    print_binary32(reg);
    printf("  (0x%08X)\n\n", reg);

    // ---------- 测试 2：检测操作 ----------
    printf("--- Test get_bit ---\n");
    printf("get_bit(reg, 0)  = %d (expected 1)\n", get_bit(reg, 0));
    printf("get_bit(reg, 15) = %d (expected 1)\n", get_bit(reg, 15));
    printf("get_bit(reg, 31) = %d (expected 1)\n", get_bit(reg, 31));
    printf("get_bit(reg, 7)  = %d (expected 0)\n\n", get_bit(reg, 7));

    // ---------- 测试 3：清零操作 ----------
    printf("--- Test clear_bit ---\n");

    clear_bit(&reg, 0);        // 清零 bit 0
    printf("After clear_bit(reg, 0):\n  ");
    print_binary32(reg);
    printf("\n");

    clear_bit(&reg, 31);       // 清零 bit 31
    printf("After clear_bit(reg, 31):\n  ");
    print_binary32(reg);
    printf("  (0x%08X)\n\n", reg);

    // ---------- 测试 4：翻转操作 ----------
    printf("--- Test toggle_bit ---\n");

    toggle_bit(&reg, 15);      // 翻转 bit 15（原为 1 → 0）
    printf("After toggle_bit(reg, 15):\n  ");
    print_binary32(reg);
    printf("\n");

    toggle_bit(&reg, 7);       // 翻转 bit 7（原为 0 → 1）
    printf("After toggle_bit(reg, 7):\n  ");
    print_binary32(reg);
    printf("  (0x%08X)\n\n", reg);

    // 翻转回 bit 15（0 → 1），验证两次翻转恢复原值
    toggle_bit(&reg, 15);
    printf("After toggle_bit(reg, 15) again (should be back):\n  ");
    print_binary32(reg);
    printf("\n\n");

    return 0;
}