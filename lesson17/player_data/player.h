/*
 * player.h
 * 玩家数据模块的公开接口。
 * 提供获取/设置血量和分数的函数，外部无法直接访问内部变量。
 */

#ifndef PLAYER_H
#define PLAYER_H

/* 获取当前血量 */
int get_hp(void);

/* 设置血量（自动钳位在 0~100） */
void set_hp(int hp);

/* 获取当前分数 */
int get_score(void);

/* 设置分数（不允许为负数） */
void set_score(int score);

#endif