/*
 * main.c
 * LED点阵模拟器 —— 主程序
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "animations.h"

void print_menu(void)
{
    printf("=== LED Dot Matrix Simulator ===\n");
    printf("1. Smile (static)\n");
    printf("2. Blink\n");
    printf("3. Marquee\n");
    printf("4. Bounce\n");
    printf("5. Exit\n");
    printf("Choice: ");
}

int main(void)
{
    int running = 1;

    while (running)
    {
        print_menu();
        char input[32];
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        int choice = atoi(input);

        switch (choice)
        {
            case 1: animation_play(ANIM_SMILE,   1,  1000); break;
            case 2: animation_play(ANIM_BLINK,  12,  150);  break;
            case 3: animation_play(ANIM_MARQUEE, 24, 100);  break;
            case 4: animation_play(ANIM_BOUNCE,  60,  50);  break;
            case 5: running = 0; break;
            default: printf("Invalid choice.\n");
        }
    }

    return 0;
}