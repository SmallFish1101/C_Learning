/*
 * main.c
 * 模拟 SPI 写入 LED 点阵 —— 演示位图如何被发送到硬件
 */

#include <stdio.h>
#include <stdint.h>
#include "spi_sim.h"

#define MATRIX_SIZE 8
typedef uint8_t DotMatrix[MATRIX_SIZE];

// 构造一个心形图案（与第40课 animations.c 中 pattern_heart 相同）
void make_heart(DotMatrix m)
{
    for (int i = 0; i < MATRIX_SIZE; i++) m[i] = 0;   // 清零

    m[1] = 0b00100100;   // ..#..#..
    m[2] = 0b01111110;   // .######.
    m[3] = 0b11111111;   // ########
    m[4] = 0b11111111;   // ########
    m[5] = 0b01111110;   // .######.
    m[6] = 0b00111100;   // ..####..
    m[7] = 0b00011000;   // ...##...
}

int main(void)
{
    DotMatrix m;
    make_heart(m);

    printf("=== Simulated SPI Write to MAX7219 ===\n");
    printf("Sending heart pattern to 8x8 LED matrix...\n\n");

    for (int row = 0; row < MATRIX_SIZE; row++) {
        spi_sim_send_row(row, m[row]);
    }

    printf("=== Done. %d rows sent. ===\n", MATRIX_SIZE);
    return 0;
}