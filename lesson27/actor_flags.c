/*
 * actor_flags.c
 * 第27课 练习三（选做·游戏方向）：用位域压缩角色状态标志
 *
 * 功能：用位域定义角色状态，实现一个高效的状态管理系统。
 *       所有状态压缩到一个 uint32_t 内，提供读写接口。
 */

#include <stdio.h>   // printf, putchar
#include <stdint.h>  // uint32_t
#include <stdbool.h> // bool, true, false

// ========== 1. 位域结构体（紧凑布局） ==========
/*
 * ActorStateBits:
 *   一个 32 位变量中各位的分配（GCC 小端：先定义的字段占低地址低位）。
 *   is_alive    : bit 0   — 是否存活
 *   has_shield  : bit 1   — 是否有护盾
 *   is_jumping  : bit 2   — 是否跳跃中
 *   is_crouched : bit 3   — 是否蹲下中
 *   weapon_ready: bit 4   — 武器是否就绪
 *   reserved    : bit 5~31 — 预留扩展（27 位，无名位域）
 */
typedef struct __attribute__((packed)) {
    uint32_t is_alive     : 1;   // bit 0
    uint32_t has_shield   : 1;   // bit 1
    uint32_t is_jumping   : 1;   // bit 2
    uint32_t is_crouched  : 1;   // bit 3
    uint32_t weapon_ready : 1;   // bit 4
    uint32_t              : 27;  // 预留位（无名位域，不可访问）
} ActorStateBits;

// ========== 2. 联合体：整体与字段双视角 ==========
/*
 * ActorState:
 *   bits: 按位域逐字段读写（高可读性）
 *   raw : 按 32 位整体读写（便于网络传输、日志打印、内存拷贝）
 *
 *   sizeof(ActorState) = 4 字节，可替代 32 个独立的 bool 变量。
 */
typedef union {
    ActorStateBits bits;
    uint32_t       raw;
} ActorState;

// ========== 3. 操作接口（宏函数） ==========
/*
 * 以下宏函数提供类似 UE5 中 EObjectFlags 的操作体验。
 *
 * 用法示例：
 *   ActorState state;
 *   state.raw = 0;
 *   ACTOR_SET_FLAG(state, is_alive);
 *   if (ACTOR_CHECK_FLAG(state, has_shield)) { ... }
 *
 * 注意：宏参数 state 在展开时会被多次计算，因此不要传入带副作用的表达式
 *       如 ACTOR_SET_FLAG(arr[i++], is_jumping)。如果需要安全版本，
 *       可以改用内联函数（见练习后思考题）。
 */
#define ACTOR_SET_FLAG(state, flag)    ((state).bits.flag = 1)
#define ACTOR_CLEAR_FLAG(state, flag)  ((state).bits.flag = 0)
#define ACTOR_TOGGLE_FLAG(state, flag) ((state).bits.flag = !(state).bits.flag)
#define ACTOR_CHECK_FLAG(state, flag)  ((state).bits.flag != 0)

// ========== 4. 辅助函数：打印状态 ==========
/*
 * print_actor_state:
 *   格式化打印 ActorState 的所有标志位。
 *   参数 title: 标题字符串
 *   参数 state: 要打印的角色状态
 */
void print_actor_state(const char *title, const ActorState *state)
{
    printf("=== %s ===\n", title);
    printf("  is_alive     : %s\n", ACTOR_CHECK_FLAG(*state, is_alive) ? "YES" : "NO");
    printf("  has_shield   : %s\n", ACTOR_CHECK_FLAG(*state, has_shield) ? "YES" : "NO");
    printf("  is_jumping   : %s\n", ACTOR_CHECK_FLAG(*state, is_jumping) ? "YES" : "NO");
    printf("  is_crouched  : %s\n", ACTOR_CHECK_FLAG(*state, is_crouched) ? "YES" : "NO");
    printf("  weapon_ready : %s\n", ACTOR_CHECK_FLAG(*state, weapon_ready) ? "YES" : "NO");
    printf("  raw value    : 0x%08X\n", state->raw);
    printf("\n");
}

// ========== 5. 主函数：模拟游戏流程 ==========
int main(void)
{
    printf("=== Actor State Flags (Bitfield Compression) ===\n\n");

    // 初始化：所有标志清零
    ActorState player;
    player.raw = 0x00000000;

    // 1. 角色诞生
    ACTOR_SET_FLAG(player, is_alive);
    ACTOR_SET_FLAG(player, weapon_ready);
    print_actor_state("1. Player spawned", &player);

    // 2. 按下跳跃键
    ACTOR_SET_FLAG(player, is_jumping);
    print_actor_state("2. Jump key pressed", &player);

    // 3. 角色受伤（检测护盾）
    printf("[Event] Player takes damage!\n");
    if (ACTOR_CHECK_FLAG(player, has_shield)) {
        printf("  Shield absorbed the damage!\n");
        ACTOR_CLEAR_FLAG(player, has_shield);
    } else {
        printf("  No shield. HP decreased.\n");
    }
    printf("\n");

    // 4. 角色捡起护盾
    printf("[Event] Player picks up a shield.\n");
    ACTOR_SET_FLAG(player, has_shield);
    print_actor_state("3. Shield picked up", &player);

    // 5. 松开跳跃键
    ACTOR_CLEAR_FLAG(player, is_jumping);
    printf("[Event] Jump key released.\n\n");

    // 6. 再次受伤（这次有护盾）
    printf("[Event] Player takes damage again!\n");
    if (ACTOR_CHECK_FLAG(player, has_shield)) {
        printf("  Shield absorbed the damage!\n");
        ACTOR_CLEAR_FLAG(player, has_shield);
    } else {
        printf("  No shield. HP decreased.\n");
    }
    print_actor_state("4. After second hit", &player);

    // 7. 验证整体与字段的一致性
    printf("=== Verification ===\n");
    printf("sizeof(ActorState) = %zu bytes (expected 4)\n", sizeof(ActorState));
    printf("The same 4 bytes can replace 32 separate bool variables.\n");

    return 0;
}