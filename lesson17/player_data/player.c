/*
 * player.c
 * 玩家数据模块的内部实现。
 * 用 static 全局变量存储数据，通过公开函数提供受控访问。
 */

#include "player.h"

// ========== 私有变量（仅本文件可见） ==========
static int hp = 100;     // 初始血量
static int score = 0;    // 初始分数

// ========== 公开接口实现 ==========

int get_hp(void)
{
    return hp;
}

void set_hp(int new_hp)
{
    // 合法范围检查：血量必须在 0 到 100 之间
    if (new_hp >= 0 && new_hp <= 100) {
        hp = new_hp;
    }
    // 如果超出范围，保持原值不变（也可以选择钳位到边界）
}

int get_score(void)
{
    return score;
}

void set_score(int new_score)
{
    // 分数不能为负数
    if (new_score >= 0) {
        score = new_score;
    }
}