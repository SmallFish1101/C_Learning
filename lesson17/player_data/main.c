/*
 * main.c
 * 玩家数据模块的使用示例。
 * 通过 player.h 提供的接口操作玩家数据，无法直接访问内部静态变量。
 */

#include <stdio.h>
#include "player.h"

int main(void)
{
    printf("=== Player Data Module Demo ===\n\n");

    // 初始化状态：内部默认 hp=100, score=0
    printf("Initial HP: %d\n", get_hp());
    printf("Initial Score: %d\n", get_score());

    // 模拟受伤
    printf("\n--- Player takes 30 damage ---\n");
    set_hp(get_hp() - 30);
    printf("Current HP: %d\n", get_hp());

    // 模拟加分
    printf("\n--- Player scores 50 points ---\n");
    set_score(get_score() + 50);
    printf("Current Score: %d\n", get_score());

    // 试图设置非法值（HP 超出范围）
    printf("\n--- Trying to set HP to 150 (should be clamped) ---\n");
    set_hp(150);
    printf("HP after invalid set: %d (should be 100)\n", get_hp());

    // 试图设置负分
    printf("\n--- Trying to set Score to -10 (should be rejected) ---\n");
    set_score(-10);
    printf("Score after invalid set: %d (should still be 50)\n", get_score());

    // 以下代码如果取消注释，编译时会报错，因为 hp 和 score 被 static 隐藏了
    // printf("HP: %d\n", hp);        // error: 'hp' undeclared
    // printf("Score: %d\n", score);  // error: 'score' undeclared

    return 0;
}