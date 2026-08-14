/*
 * led_matrix.c
 * LED点阵位图操作与终端渲染实现
 */

#include "led_matrix.h"
#include <stdio.h>

// 清除整个点阵
void dotmatrix_clear(DotMatrix m)
{
    for (int i = 0; i < MATRIX_SIZE; i++) {
        m[i] = 0;
    }
}

// 点亮指定 LED
void dotmatrix_set_on(DotMatrix m, int row, int col)
{
    if (row < 0 || row >= MATRIX_SIZE || col < 0 || col >= MATRIX_SIZE)
        return;
    m[row] |= (uint8_t)(1u << (MATRIX_SIZE - 1 - col));
}

// 熄灭指定 LED
void dotmatrix_set_off(DotMatrix m, int row, int col)
{
    if (row < 0 || row >= MATRIX_SIZE || col < 0 || col >= MATRIX_SIZE)
        return;
    m[row] &= (uint8_t)~(1u << (MATRIX_SIZE - 1 - col));
}

// 翻转指定 LED
void dotmatrix_toggle(DotMatrix m, int row, int col)
{
    if (row < 0 || row >= MATRIX_SIZE || col < 0 || col >= MATRIX_SIZE)
        return;
    m[row] ^= (uint8_t)(1u << (MATRIX_SIZE - 1 - col));
}

// 查询指定 LED 状态
bool dotmatrix_is_on(const DotMatrix m, int row, int col)
{
    if (row < 0 || row >= MATRIX_SIZE || col < 0 || col >= MATRIX_SIZE)
        return false;
    return (m[row] >> (MATRIX_SIZE - 1 - col)) & 1u;
}

// 渲染点阵到终端
void dotmatrix_render(const DotMatrix m)
{
    printf("  +--------+\n");
    for (int row = 0; row < MATRIX_SIZE; row++) {
        printf("  |");
        for (int col = 0; col < MATRIX_SIZE; col++) {
            printf("%s", dotmatrix_is_on(m, row, col) ? "●" : "·");
        }
        printf("|\n");
    }
    printf("  +--------+\n");
}

// 左移一列（最右边补 0）
void dotmatrix_shift_left(DotMatrix m)
{
    for (int row = 0; row < MATRIX_SIZE; row++) {
        m[row] = (uint8_t)(m[row] << 1);
    }
}

// 右移一列（最左边补 0）
void dotmatrix_shift_right(DotMatrix m)
{
    for (int row = 0; row < MATRIX_SIZE; row++) {
        m[row] = (uint8_t)(m[row] >> 1);
    }
}

// 上移一行（最下面补 0）
void dotmatrix_shift_up(DotMatrix m)
{
    for (int row = 0; row < MATRIX_SIZE - 1; row++) {
        m[row] = m[row + 1];
    }
    m[MATRIX_SIZE - 1] = 0;
}

// 下移一行（最上面补 0）
void dotmatrix_shift_down(DotMatrix m)
{
    for (int row = MATRIX_SIZE - 1; row > 0; row--) {
        m[row] = m[row - 1];
    }
    m[0] = 0;
}