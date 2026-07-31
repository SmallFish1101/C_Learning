/*
 * enemy_manager.c
 * 第28课 作业三（选做·游戏方向）：动态敌人管理器
 *
 * 功能：用动态数组管理敌人实体，支持添加（自动扩容）、
 *       删除最后一个敌人、列出所有敌人。
 *       使用 malloc / realloc / free 管理内存。
 */

#include <stdio.h>    // printf
#include <stdlib.h>   // malloc, realloc, free, rand, srand, exit
#include <time.h>     // time
#include <string.h>   // strlen (用于去换行符)

#define INITIAL_CAPACITY  2    // 初始容量（故意小，方便测试扩容）

// ========== 敌人结构体 ==========
typedef struct {
    int   id;       // 唯一编号
    int   hp;       // 生命值
    float x;        // X 坐标
    float y;        // Y 坐标
} Enemy;

// ========== 敌人管理器结构体 ==========
typedef struct {
    Enemy *enemies;     // 指向动态分配的数组
    int    count;       // 当前敌人数量
    int    capacity;    // 当前数组容量
    int    next_id;     // 下一个敌人将获得的 ID
} EnemyManager;

// ========== 函数原型 ==========
void manager_init(EnemyManager *mgr);
void manager_destroy(EnemyManager *mgr);
void manager_add_enemy(EnemyManager *mgr);
void manager_remove_last(EnemyManager *mgr);
void manager_list_all(const EnemyManager *mgr);

// ========== 辅助函数 ==========
/*
 * random_int:
 *   返回 [min, max] 之间的随机整数（包含两端）。
 */
int random_int(int min, int max)
{
    return min + rand() % (max - min + 1);
}

/*
 * random_float:
 *   返回 [min, max] 之间的随机浮点数。
 */
float random_float(float min, float max)
{
    float scale = (float)rand() / (float)RAND_MAX;   // 0.0 ~ 1.0
    return min + scale * (max - min);
}

/*
 * safe_read_line:
 *   用 fgets 读取一行，去掉末尾的换行符。
 *   返回：实际读取到的字符数（不含 '\0'），EOF 时退出。
 */
int safe_read_line(char *buffer, int size)
{
    if (fgets(buffer, size, stdin) == NULL) {
        printf("\nEnd of input.\n");
        exit(0);
    }
    int len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    return len;
}

// ========== 管理器初始化 ==========
void manager_init(EnemyManager *mgr)
{
    // 分配初始数组
    mgr->enemies = (Enemy *)malloc(INITIAL_CAPACITY * sizeof(Enemy));
    if (mgr->enemies == NULL) {
        printf("Fatal: Failed to allocate initial memory.\n");
        exit(1);
    }
    mgr->count    = 0;
    mgr->capacity = INITIAL_CAPACITY;
    mgr->next_id  = 1;   // ID 从 1 开始
}

// ========== 管理器销毁 ==========
void manager_destroy(EnemyManager *mgr)
{
    free(mgr->enemies);
    mgr->enemies  = NULL;   // 防止悬空指针
    mgr->count    = 0;
    mgr->capacity = 0;
    mgr->next_id  = 0;
}

// ========== 添加敌人 ==========
void manager_add_enemy(EnemyManager *mgr)
{
    // 1. 检查是否需要扩容
    if (mgr->count >= mgr->capacity) {
        int new_capacity = mgr->capacity * 2;

        // 安全模式：用临时指针接收 realloc 结果
        Enemy *tmp = (Enemy *)realloc(mgr->enemies,
                                      new_capacity * sizeof(Enemy));
        if (tmp == NULL) {
            printf("  Memory allocation failed. Cannot add more enemies.\n");
            return;
        }

        // 扩容成功：更新指针和容量
        mgr->enemies  = tmp;
        mgr->capacity = new_capacity;

        printf("  (enemy list expanded to %d)\n", mgr->capacity);
    }

    // 2. 创建新敌人并填充随机属性
    Enemy e;
    e.id = mgr->next_id++;
    e.hp = random_int(50, 100);
    e.x  = random_float(0.0f, 100.0f);
    e.y  = random_float(0.0f, 100.0f);

    // 3. 将新敌人存入动态数组末尾
    mgr->enemies[mgr->count] = e;
    mgr->count++;

    printf("  Enemy #%d spawned! HP=%d, Position=(%.1f, %.1f)\n",
           e.id, e.hp, e.x, e.y);
}

// ========== 删除最后一个敌人 ==========
void manager_remove_last(EnemyManager *mgr)
{
    if (mgr->count == 0) {
        printf("  No enemies to remove.\n");
        return;
    }

    // 敌人信息（用于提示）
    Enemy *last = &mgr->enemies[mgr->count - 1];
    printf("  Enemy #%d removed! (HP=%d, Pos=(%.1f, %.1f))\n",
           last->id, last->hp, last->x, last->y);

    // 从数组中移除：直接减少 count，无需移动数据
    mgr->count--;
    // 注意：最后一个元素仍然占用内存，但下一次添加会覆盖它
}

// ========== 列出所有敌人 ==========
void manager_list_all(const EnemyManager *mgr)
{
    if (mgr->count == 0) {
        printf("  (no enemies)\n");
        return;
    }

    printf("  %-4s %-6s %-8s %-8s\n", "ID", "HP", "X", "Y");
    printf("  ---  ------  --------  --------\n");
    for (int i = 0; i < mgr->count; i++) {
        Enemy *e = &mgr->enemies[i];
        printf("  %-4d %-6d %-8.1f %-8.1f\n", e->id, e->hp, e->x, e->y);
    }
    printf("  Total: %d enemy(ies), capacity: %d\n", mgr->count, mgr->capacity);
}

// ========== 主菜单 ==========
void print_menu(void)
{
    printf("\n");
    printf("========================\n");
    printf("  Enemy Manager\n");
    printf("========================\n");
    printf(" 1. Add enemy\n");
    printf(" 2. Remove last enemy\n");
    printf(" 3. List all enemies\n");
    printf(" 4. Exit\n");
    printf("------------------------\n");
    printf("Your choice: ");
}

// ========== 主函数 ==========
int main(void)
{
    // 用当前时间初始化随机数种子
    srand((unsigned)time(NULL));

    printf("=== Dynamic Enemy Manager ===\n");
    printf("Welcome! Manage enemy entities with dynamic memory.\n");

    EnemyManager mgr;
    manager_init(&mgr);   // 分配初始数组

    int running = 1;
    while (running)
    {
        print_menu();

        char input[10];
        safe_read_line(input, sizeof(input));

        int choice;
        if (sscanf(input, "%d", &choice) != 1) {
            printf("Invalid input. Please enter a number 1-4.\n");
            continue;
        }

        switch (choice)
        {
            case 1:
                manager_add_enemy(&mgr);
                break;

            case 2:
                manager_remove_last(&mgr);
                break;

            case 3:
                manager_list_all(&mgr);
                break;

            case 4:
                printf("Goodbye!\n");
                running = 0;
                break;

            default:
                printf("Invalid choice. Please enter 1-4.\n");
                break;
        }
    }

    // ★ 关键：退出前释放所有动态分配的内存
    manager_destroy(&mgr);

    return 0;
}