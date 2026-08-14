/*
 * animations.c
 * 内置动画效果实现
 */

#include "animations.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN()  system("cls")
    #define SLEEP_MS(ms)    Sleep(ms)
#else
    #include <unistd.h>
    #define CLEAR_SCREEN()  system("clear")
    #define SLEEP_MS(ms)    usleep((ms) * 1000)
#endif

// ---------- 内置图案 ----------

static void pattern_smile(DotMatrix m)
{
    dotmatrix_clear(m);
    // 眼睛（两个点）
    dotmatrix_set_on(m, 2, 2);
    dotmatrix_set_on(m, 2, 5);
    // 嘴巴（一条向上弯曲的弧线）
    for (int col = 1; col <= 6; col++) {
        dotmatrix_set_on(m, 5, col);
    }
    dotmatrix_set_on(m, 4, 0);
    dotmatrix_set_on(m, 4, 7);
}

static void pattern_heart(DotMatrix m)
{
    dotmatrix_clear(m);
    // 心形图案
    dotmatrix_set_on(m, 1, 2); dotmatrix_set_on(m, 1, 5);
    dotmatrix_set_on(m, 2, 1); dotmatrix_set_on(m, 2, 6);
    dotmatrix_set_on(m, 3, 1); dotmatrix_set_on(m, 3, 6);
    dotmatrix_set_on(m, 4, 2); dotmatrix_set_on(m, 4, 5);
    dotmatrix_set_on(m, 5, 3); dotmatrix_set_on(m, 5, 4);
    dotmatrix_set_on(m, 6, 4); dotmatrix_set_on(m, 6, 3);
}

// ---------- 动画实现 ----------

void animation_play(AnimType type, int frames, int frame_delay_ms)
{
    DotMatrix m;
    dotmatrix_clear(m);

    switch (type)
    {
        // ----- 静态笑脸 -----
        case ANIM_SMILE:
            pattern_smile(m);
            CLEAR_SCREEN();
            printf("  SMILE\n\n");
            dotmatrix_render(m);
            SLEEP_MS(2000);
            break;

        // ----- 眨眼 -----
        case ANIM_BLINK:
        {
            for (int f = 0; f < frames; f++) {
                CLEAR_SCREEN();
                printf("  BLINK  (frame %d)\n\n", f);
                pattern_smile(m);

                // 每隔 3 帧闭一次眼（熄灭眼睛的两个点）
                if (f % 3 == 0) {
                    dotmatrix_set_off(m, 2, 2);
                    dotmatrix_set_off(m, 2, 5);
                }

                dotmatrix_render(m);
                SLEEP_MS(frame_delay_ms);
            }
            break;
        }

        // ----- 跑马灯 -----
        case ANIM_MARQUEE:
        {
            dotmatrix_clear(m);
            // 初始：最左边一列全亮
            for (int row = 0; row < MATRIX_SIZE; row++) {
                dotmatrix_set_on(m, row, 0);
            }

            for (int f = 0; f < frames; f++) {
                CLEAR_SCREEN();
                printf("  MARQUEE  (frame %d)\n\n", f);
                dotmatrix_render(m);

                // 每帧右移一列，如果超出边界则回到最左边
                dotmatrix_shift_right(m);
                if (f % MATRIX_SIZE == 0) {
                    for (int row = 0; row < MATRIX_SIZE; row++) {
                        dotmatrix_set_on(m, row, 0);
                    }
                }

                SLEEP_MS(frame_delay_ms);
            }
            break;
        }

        // ----- 弹跳球 -----
        case ANIM_BOUNCE:
        {
            int ball_row = 3, ball_col = 3;
            int d_row = 1, d_col = 1;

            for (int f = 0; f < frames; f++) {
                CLEAR_SCREEN();
                printf("  BOUNCE  (frame %d)\n\n", f);

                // 清除上一帧的球
                dotmatrix_clear(m);
                // 画新位置的球
                dotmatrix_set_on(m, ball_row, ball_col);
                dotmatrix_render(m);

                // 更新位置
                ball_row += d_row;
                ball_col += d_col;

                // 边界反弹
                if (ball_row <= 0 || ball_row >= MATRIX_SIZE - 1)
                    d_row = -d_row;
                if (ball_col <= 0 || ball_col >= MATRIX_SIZE - 1)
                    d_col = -d_col;

                SLEEP_MS(frame_delay_ms);
            }
            break;
        }
    }
}