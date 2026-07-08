#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>   // 使用 bool 类型

// ---------- 定义标志位掩码 ----------
// 每个宏代表一个二进制位：1<<n 只让第n位为1，其余为0
#define FLAG_JUMPING    (1 << 0)   // bit 0: 是否正在跳跃
#define FLAG_CROUCHING  (1 << 1)   // bit 1: 是否正在蹲下
#define FLAG_SHIELD     (1 << 2)   // bit 2: 是否有护盾

// ---------- 功能函数声明 ----------
void set_flag(uint8_t *flags, uint8_t mask);
void clear_flag(uint8_t *flags, uint8_t mask);
bool check_flag(uint8_t flags, uint8_t mask);
void print_status(uint8_t flags);

int main(void)
{
    uint8_t player_flags = 0x00;   // 初始：所有标志位为0（无任何状态）

    printf("=== Player Flag System ===\n\n");

    // 1. 按下跳跃键，置位 JUMPING 标志
    printf("[Action] Press JUMP key\n");
    set_flag(&player_flags, FLAG_JUMPING);
    print_status(player_flags);

    // 2. 角色获得护盾
    printf("[Action] Pick up SHIELD\n");
    set_flag(&player_flags, FLAG_SHIELD);
    print_status(player_flags);

    // 3. 按下蹲下键（但跳跃时不允许蹲下，这里仅演示置位）
    printf("[Action] Press CROUCH key\n");
    set_flag(&player_flags, FLAG_CROUCHING);
    print_status(player_flags);

    // 4. 松开跳跃键，清除 JUMPING 标志
    printf("[Action] Release JUMP key\n");
    clear_flag(&player_flags, FLAG_JUMPING);
    print_status(player_flags);

    // 5. 角色受到伤害，检查护盾
    printf("[Action] Take damage!\n");
    if (check_flag(player_flags, FLAG_SHIELD)) {
        printf("  Shield absorbed the damage!\n");
        clear_flag(&player_flags, FLAG_SHIELD);   // 消耗护盾
    } else {
        printf("  No shield! Health decreased.\n");
    }
    print_status(player_flags);

    // 6. 再次受伤，护盾已消失
    printf("[Action] Take damage again!\n");
    if (check_flag(player_flags, FLAG_SHIELD)) {
        printf("  Shield absorbed the damage!\n");
        clear_flag(&player_flags, FLAG_SHIELD);
    } else {
        printf("  No shield! Health decreased.\n");
    }
    print_status(player_flags);

    return 0;
}

// ---------- 函数实现 ----------

/*
 * set_flag: 置位 flags 中由 mask 指定的位（设成1，不影响其他位）
 * flags: 指向标志变量的指针（因为要修改原值）
 * mask:  要设置的位掩码
 */
void set_flag(uint8_t *flags, uint8_t mask)
{
    *flags |= mask;   // 按位或：目标位变1，其余位保留原值
}

/*
 * clear_flag: 清零 flags 中由 mask 指定的位（设成0，不影响其他位）
 */
void clear_flag(uint8_t *flags, uint8_t mask)
{
    *flags &= ~mask;  // 按位与 + 取反：目标位变0，其余位保留原值
}

/*
 * check_flag: 检查 flags 中由 mask 指定的位是否为1
 * 返回 true (位为1) 或 false (位为0)
 */
bool check_flag(uint8_t flags, uint8_t mask)
{
    return (flags & mask) != 0;  // 按位与：掩码位为1，结果非0表示目标位为1
}

/*
 * print_status: 逐位检查并打印玩家当前状态
 */
void print_status(uint8_t flags)
{
    printf("  [Status] ");

    if (check_flag(flags, FLAG_JUMPING))
        printf("JUMPING ");
    if (check_flag(flags, FLAG_CROUCHING))
        printf("CROUCHING ");
    if (check_flag(flags, FLAG_SHIELD))
        printf("SHIELD ");

    // 如果一个标志都没设置，打印 NONE
    if ((flags & (FLAG_JUMPING | FLAG_CROUCHING | FLAG_SHIELD)) == 0)
        printf("NONE");

    printf("(0x%02X)\n", flags);
}