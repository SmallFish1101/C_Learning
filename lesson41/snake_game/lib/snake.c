/*
 * snake.c
 * 贪吃蛇游戏核心逻辑实现
 */

#include "snake.h"
#include <stdlib.h>    // malloc, free, rand
#include <time.h>      // time

#ifdef _WIN32
    #include <conio.h>       // _kbhit, _getch
    #include <windows.h>     // Sleep, system
    #define CLEAR_CMD "cls"
#else
    #include <termios.h>     // 终端设置
    #include <unistd.h>      // read, usleep
    #include <fcntl.h>       // fcntl
    #include <sys/select.h>  // select
    #define CLEAR_CMD "clear"
#endif

// ========== 跨平台输入输出封装 ==========

bool kb_hit(void)
{
#ifdef _WIN32
    return _kbhit() != 0;
#else
    // Linux：使用 select 检查 stdin 是否有数据可读
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    struct timeval tv = {0, 0};   // 立即返回，不阻塞
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
#endif
}

int kb_getch(void)
{
#ifdef _WIN32
    return _getch();
#else
    // Linux：从 stdin 读取一个字符
    unsigned char ch;
    if (read(STDIN_FILENO, &ch, 1) == 1)
        return ch;
    return -1;
#endif
}

void clear_screen(void)
{
    system(CLEAR_CMD);
}

void sleep_ms(int ms)
{
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

// ========== 游戏逻辑 ==========

void game_init(GameState *gs)
{
    // 创建初始蛇：水平方向，头在右，尾在左
    gs->head = NULL;
    for (int i = 0; i < INITIAL_SNAKE_LEN; i++) {
        SnakeNode *node = (SnakeNode *)malloc(sizeof(SnakeNode));
        node->x = INITIAL_SNAKE_LEN - 1 - i;   // 头在 x=2，尾在 x=0
        node->y = BOARD_HEIGHT / 2;
        node->next = gs->head;   // 头插法：新节点指向旧头
        gs->head = node;
    }

    gs->dir = DIR_RIGHT;
    gs->score = 0;
    gs->game_over = false;
    gs->won = false;

    // 放置第一个食物
    srand((unsigned)time(NULL));
    gs->food_x = rand() % BOARD_WIDTH;
    gs->food_y = rand() % BOARD_HEIGHT;
}

void game_destroy(GameState *gs)
{
    SnakeNode *p = gs->head;
    while (p != NULL) {
        SnakeNode *next = p->next;
        free(p);
        p = next;
    }
    gs->head = NULL;
}

bool game_update(GameState *gs)
{
    // 1. 计算新蛇头位置
    int new_x = gs->head->x;
    int new_y = gs->head->y;

    switch (gs->dir) {
        case DIR_UP:    new_y--; break;
        case DIR_DOWN:  new_y++; break;
        case DIR_LEFT:  new_x--; break;
        case DIR_RIGHT: new_x++; break;
    }

    // 2. 墙壁碰撞检测
    if (new_x < 0 || new_x >= BOARD_WIDTH ||
        new_y < 0 || new_y >= BOARD_HEIGHT) {
        gs->game_over = true;
        return false;
    }

    // 3. 自身碰撞检测（新蛇头不能撞到已有的蛇身，但允许撞到要删除的蛇尾）
    for (SnakeNode *p = gs->head; p != NULL; p = p->next) {
        if (p->x == new_x && p->y == new_y) {
            // 如果撞到的是蛇尾，且蛇尾即将被删除，则不算碰撞
            // 简化处理：直接 game over
            gs->game_over = true;
            return false;
        }
    }

    // 4. 在头部插入新节点
    SnakeNode *new_head = (SnakeNode *)malloc(sizeof(SnakeNode));
    new_head->x = new_x;
    new_head->y = new_y;
    new_head->next = gs->head;
    gs->head = new_head;

    // 5. 检查是否吃到食物
    if (new_x == gs->food_x && new_y == gs->food_y) {
        gs->score++;
        // 生成新食物（不覆盖蛇身）
        bool valid_food = false;
        while (!valid_food) {
            valid_food = true;
            gs->food_x = rand() % BOARD_WIDTH;
            gs->food_y = rand() % BOARD_HEIGHT;
            for (SnakeNode *p = gs->head; p != NULL; p = p->next) {
                if (p->x == gs->food_x && p->y == gs->food_y) {
                    valid_food = false;
                    break;
                }
            }
        }
        // 吃到食物，蛇尾不删除（长度 +1）

        // 检查是否胜利
        int len = 0;
        for (SnakeNode *p = gs->head; p != NULL; p = p->next) len++;
        if (len >= MAX_SNAKE_LEN) {
            gs->won = true;
            gs->game_over = true;
            return false;
        }
    } else {
        // 没吃到食物：删除蛇尾
        SnakeNode *p = gs->head;
        if (p->next == NULL) {
            // 只剩蛇头（理论上不会发生，因为初始长度≥3）
            free(p);
            gs->head = NULL;
        } else {
            while (p->next->next != NULL) {
                p = p->next;
            }
            free(p->next);
            p->next = NULL;
        }
    }

    return true;
}

void game_render(const GameState *gs)
{
    clear_screen();
    printf("=== SNAKE GAME ===  Score: %d\n\n", gs->score);

    // 创建棋盘（用二维数组表示，蛇身标记为 'O'，食物标记为 '*'，空白为 '.'）
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    for (int y = 0; y < BOARD_HEIGHT; y++)
        for (int x = 0; x < BOARD_WIDTH; x++)
            board[y][x] = '.';

    // 标记蛇身
    for (SnakeNode *p = gs->head; p != NULL; p = p->next) {
        if (p->y >= 0 && p->y < BOARD_HEIGHT &&
            p->x >= 0 && p->x < BOARD_WIDTH) {
            board[p->y][p->x] = (p == gs->head) ? '@' : 'O';
        }
    }

    // 标记食物
    board[gs->food_y][gs->food_x] = '*';

    // 打印棋盘（带边框）
    printf("  +");
    for (int x = 0; x < BOARD_WIDTH; x++) printf("--");
    printf("+\n");

    for (int y = 0; y < BOARD_HEIGHT; y++) {
        printf("  |");
        for (int x = 0; x < BOARD_WIDTH; x++) {
            printf("%c ", board[y][x]);
        }
        printf("|\n");
    }

    printf("  +");
    for (int x = 0; x < BOARD_WIDTH; x++) printf("--");
    printf("+\n");

    if (gs->game_over) {
        if (gs->won)
            printf("\n  *** YOU WIN! ***\n");
        else
            printf("\n  *** GAME OVER ***\n");
    } else {
        printf("\n  WASD/方向键控制移动，按 Q 退出\n");
    }
}