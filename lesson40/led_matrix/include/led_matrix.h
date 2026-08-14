/*
 * led_matrix.h
 * 第40课 LED点阵模拟器 —— 位图操作核心接口
 */

#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <stdint.h>
#include <stdbool.h>

#define MATRIX_SIZE 8   // 8×8 点阵

// ========== 点阵类型 ==========

/* 8×8 点阵位图：每个 uint8_t 表示一行，8 个元素表示 8 行 */
typedef uint8_t DotMatrix[MATRIX_SIZE];

// ========== 位操作函数 ==========

/* 清除整个点阵（全部熄灭） */
void dotmatrix_clear(DotMatrix m);

/* 点亮第 row 行、第 col 列的 LED */
void dotmatrix_set_on(DotMatrix m, int row, int col);

/* 熄灭第 row 行、第 col 列的 LED */
void dotmatrix_set_off(DotMatrix m, int row, int col);

/* 翻转第 row 行、第 col 列的 LED */
void dotmatrix_toggle(DotMatrix m, int row, int col);

/* 查询第 row 行、第 col 列的 LED 是否亮着 */
bool dotmatrix_is_on(const DotMatrix m, int row, int col);

/* 渲染点阵到终端：'●' 表示亮，'·' 表示灭 */
void dotmatrix_render(const DotMatrix m);

/* 将点阵向左/右/上/下滚动一列/一行（用于跑马灯动画） */
void dotmatrix_shift_left(DotMatrix m);
void dotmatrix_shift_right(DotMatrix m);
void dotmatrix_shift_up(DotMatrix m);
void dotmatrix_shift_down(DotMatrix m);

#endif