/*
 * can_id.c
 * 第23课 练习二：模拟 CAN 报文解析
 *
 * 功能：用位操作宏提取 CAN 标准帧的 11 位 ID，
 *       设置/清除 RTR（远程请求位），演示协议字段的解析过程。
 *
 * 模拟报文格式（uint16_t，仅用于练习）：
 *   bit 0 ~ 10  : CAN ID（11 位标识符）
 *   bit 4       : RTR（1 = 远程帧，0 = 数据帧）
 *   其余位保留
 */

#include <stdio.h>   // printf, putchar
#include <stdint.h>  // uint16_t

// ========== 寄存器操作宏（复用第23课模板）==========
#define SET_BIT(reg, bit)       ((reg) |= (1U << (bit)))
#define CLEAR_BIT(reg, bit)     ((reg) &= ~(1U << (bit)))
#define GET_BIT(reg, bit)       (((reg) >> (bit)) & 1U)
#define GET_FIELD(reg, start, width)  (((reg) >> (start)) & ((1U << (width)) - 1U))

// ========== 辅助函数：打印 16 位二进制 ==========
/*
 * print_binary16:
 *   以二进制形式打印 16 位无符号整数，每 4 位加空格。
 *   额外标注 ID 域（bit 0~10）和 RTR 位（bit 4）的位置。
 *   参数 val: 要打印的值
 *   参数 label: 说明信息（如 "CAN Header"）
 */
void print_binary16(uint16_t val, const char *label)
{
    printf("%s:\n  ", label);
    for (int i = 15; i >= 0; i--)
    {
        putchar(((val >> i) & 1U) ? '1' : '0');

        if (i % 4 == 0 && i != 0) {
            putchar(' ');   // 半字节分隔
        }
    }
    printf("\n");
    // 打印字段标注
    printf("  |_____________|  |_________|\n");
    printf("   bit 15~11  bit 10~0\n");
    printf("   (reserved)    (CAN ID)\n");
    printf("                    ↑ bit 4 = RTR\n\n");
}

int main(void)
{
    printf("=== CAN Frame Parsing Demo ===\n\n");

    // 1. 初始化报文头部（16位，初始为 0）
    uint16_t can_header = 0x0000;
    print_binary16(can_header, "Initial header");

    // 2. 设置 CAN ID（将 11 位 ID 写入 bit 0~10）
    //    假设 ID = 0x5A3（二进制 101 1010 0011，十进制 1443）
    uint16_t can_id = 0x5A3;   // 11 位 ID 值

    // 直接将 ID 写入低 11 位（因为 ID 占 bit 0~10）
    // 先清空低 11 位，再 OR 写入新值
    can_header &= ~((1U << 11) - 1U);   // 清空 bit 0~10
    can_header |= (can_id & ((1U << 11) - 1U));  // 写入 ID（仅保留低 11 位）

    printf("Set CAN ID to 0x%03X (%u)\n", can_id, can_id);
    print_binary16(can_header, "Header with ID");

    // 3. 提取并打印 ID（用 GET_FIELD 宏）
    uint16_t extracted_id = GET_FIELD(can_header, 0, 11);
    printf("Extracted ID: 0x%03X (%u)\n\n", extracted_id, extracted_id);

    // 4. 设置 RTR = 1（远程帧，bit 4）
    SET_BIT(can_header, 4);
    printf("After SET_BIT(can_header, 4): RTR = 1 (Remote Frame)\n");
    print_binary16(can_header, "Header with RTR=1");

    // 5. 读取 RTR 位
    printf("GET_BIT(can_header, 4) = %u (RTR status)\n\n",
           GET_BIT(can_header, 4));

    // 6. 清除 RTR（改回数据帧）
    CLEAR_BIT(can_header, 4);
    printf("After CLEAR_BIT(can_header, 4): RTR = 0 (Data Frame)\n");
    print_binary16(can_header, "Header with RTR=0");

    // 7. 最终报告
    printf("=== Final Report ===\n");
    printf("CAN ID (bit 0~10): 0x%03X (%u)\n",
           GET_FIELD(can_header, 0, 11),
           GET_FIELD(can_header, 0, 11));
    printf("RTR  (bit 4)    : %u (%s)\n",
           GET_BIT(can_header, 4),
           GET_BIT(can_header, 4) ? "Remote Frame" : "Data Frame");

    return 0;
}