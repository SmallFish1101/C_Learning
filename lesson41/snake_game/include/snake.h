/*
 * snake.h
 * 第41课 贪吃蛇游戏 —— 核心接口
 */

#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include <stdio.h>

// ========== 游戏常量 ==========
#define BOARD_WIDTH   20     // 游戏区域宽度（列数）
#define BOARD_HEIGHT  15     // 游戏区域高度（行数）
#define INITIAL_SNAKE_LEN 3  // 蛇的初始长度
#define MAX_SNAKE_LEN (BOARD_WIDTH * BOARD_HEIGHT)  // 理论最大长度

// ========== 方向枚举 ==========
typedef enum {
    DIR_UP = 0,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

// ========== 链表节点 ==========
typedef struct SnakeNode {
    int x;                  // 列坐标（0 ~ BOARD_WIDTH-1）
    int y;                  // 行坐标（0 ~ BOARD_HEIGHT-1）
    struct SnakeNode *next; // 下一节身体
} SnakeNode;

// ========== 游戏状态 ==========
typedef struct {
    SnakeNode *head;        // 蛇头（链表头）
    Direction  dir;         // 当前移动方向
    int        score;       // 得分（吃到的食物数）
    int        food_x;      // 食物列坐标
    int        food_y;      // 食物行坐标
    bool       game_over;   // 游戏是否结束
    bool       won;         // 是否获胜（蛇占满整个棋盘）
} GameState;

// ========== 游戏接口 ==========

/* 初始化游戏（创建蛇、放置第一个食物） */
void game_init(GameState *gs);

/* 释放蛇链表的所有节点 */
void game_destroy(GameState *gs);

/* 更新游戏逻辑（移动、吃食物、碰撞检测），返回 true 表示游戏继续 */
bool game_update(GameState *gs);

/* 渲染游戏画面到终端 */
void game_render(const GameState *gs);

/* 非阻塞键盘输入（跨平台封装） */
bool kb_hit(void);        // 有按键按下返回 true
int  kb_getch(void);      // 读取一个按键（不阻塞）

/* 清屏（跨平台封装） */
void clear_screen(void);

/* 延时指定毫秒（跨平台封装） */
void sleep_ms(int ms);

#endif