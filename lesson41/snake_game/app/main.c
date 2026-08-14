/*
 * main.c
 * 贪吃蛇游戏 —— 游戏循环
 */

#include <stdio.h>
#include <stdlib.h>
#include "snake.h"

int main(void)
{

    // 程序启动时启用 raw mode
    enable_raw_mode();

    GameState gs;
    game_init(&gs);

    printf("=== SNAKE GAME ===\n");
    printf("Use WASD or arrow keys to move.\n");
    printf("Press Q to quit.\n\n");
    sleep_ms(1500);

    int frame_delay_ms = 150;   // 帧率：150ms/帧 ≈ 6.7 FPS

    while (!gs.game_over)
    {
        // 1. 处理键盘输入（非阻塞）
        if (kb_hit()) {
            int key = kb_getch();

            // 方向键在终端中通常返回转义序列（Linux）或特殊键码（Windows）
            // 简化处理：WASD 控制
            switch (key) {
                case 'w': case 'W':
                    if (gs.dir != DIR_DOWN)  gs.dir = DIR_UP;    break;
                case 's': case 'S':
                    if (gs.dir != DIR_UP)    gs.dir = DIR_DOWN;  break;
                case 'a': case 'A':
                    if (gs.dir != DIR_RIGHT) gs.dir = DIR_LEFT;  break;
                case 'd': case 'D':
                    if (gs.dir != DIR_LEFT)  gs.dir = DIR_RIGHT; break;
                case 'q': case 'Q':
                    gs.game_over = true;
                    break;
            }
        }

        // 2. 更新游戏逻辑
        if (!gs.game_over) {
            game_update(&gs);
        }

        // 3. 渲染画面
        game_render(&gs);

        // 4. 延时控制帧率
        if (!gs.game_over) {
            sleep_ms(frame_delay_ms);
        }
    }

    // 最终渲染一次（显示 GAME OVER）
    game_render(&gs);

    game_destroy(&gs);

    // 退出前恢复终端设置
    disable_raw_mode();

    printf("\nThanks for playing!\n");
    return 0;
}