/*
 * spi_sim.c
 * 模拟 SPI 写入的实现
 */

#include "spi_sim.h"
#include <stdio.h>

// 打印一个字节的二进制表示（8位）
static void print_binary8(uint8_t byte)
{
    for (int i = 7; i >= 0; i--) {
        putchar((byte >> i) & 1 ? '1' : '0');
    }
}

void spi_sim_send(uint8_t byte)
{
    // 真实硬件：写 GPIO 寄存器、翻转时钟线
    // 模拟：打印二进制
    printf("    TX byte: 0x%02X (binary: ", byte);
    print_binary8(byte);
    printf(")\n");
}

void spi_sim_send_row(uint8_t row, uint8_t data)
{
    printf("  [Row %d] Register=%d, Data=0x%02X\n", row, row + 1, data);
    // 真实 SPI 发送两个字节：寄存器地址 + 数据
    spi_sim_send(row + 1);   // 寄存器地址
    spi_sim_send(data);       // 数据
    printf("\n");
}