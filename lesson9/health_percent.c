#include <stdio.h>
#include <stdint.h>   // uint8_t
#include <math.h>     // fabs, floor（可选）

/*
 * health_to_factor:
 *   将血量百分比 (0~100) 转换为伤害因子 (0.0~1.0)。
 *   health: 当前血量百分比，取值范围 0~100。
 *   return: 伤害因子 = 1.0 - (health / 100.0)。
 *           返回值在 0.0 (满血) 到 1.0 (空血) 之间。
 *
 *   注意：health 是整数，但除以 100.0 会自动转换为 float 运算。
 */
float health_to_factor(uint8_t health)
{
    // 边界检查（防御性编程）：确保 health 不超过 100
    if (health > 100) {
        health = 100;   // 或者返回错误值，这里简单截断
    }

    // 关键：使用 100.0f 确保浮点除法，否则 100 会导致整数除法！
    return 1.0f - (health / 100.0f);
}

/*
 * apply_damage:
 *   根据当前血量百分比和基础伤害，计算剩余血量百分比。
 *   health: 当前血量百分比 (0~100)，通过指针修改原值。
 *   base_damage: 基础伤害值（0~100 之间的整数，表示百分比伤害）。
 *   return: 实际扣除的血量百分比（整数，保守取整）。
 *
 *   类型安全考虑：
 *   - 内部使用 float 运算，最后转换回 uint8_t 时做范围检查和四舍五入。
 */
uint8_t apply_damage(uint8_t *health, uint8_t base_damage)
{
    // 先转换为浮点，乘以伤害因子，再转回整数
    float factor = health_to_factor(*health);
    float actual_damage_f = (float)base_damage * factor;

    // 浮点转整数：加 0.5 实现四舍五入，同时确保不为负且不超过当前血量
    int damage_int = (int)(actual_damage_f + 0.5f);
    if (damage_int < 0) damage_int = 0;
    if (damage_int > *health) damage_int = *health;   // 不能扣超过当前血量

    *health -= damage_int;   // 扣除血量（uint8_t 运算，安全）

    return (uint8_t)damage_int;
}

int main(void)
{
    uint8_t player_health = 100;   // 初始满血
    uint8_t base_dmg = 30;         // 基础伤害百分比

    printf("=== Health Percent & Damage Factor (Game-like) ===\n\n");

    // 1. 显示初始状态
    float factor = health_to_factor(player_health);
    printf("1. Initial health = %u%%\n", player_health);
    printf("   Damage factor = %.3f (no damage bonus when full health)\n", factor);

    // 2. 第一次受伤（满血 → 扣血后因子增大）
    uint8_t lost = apply_damage(&player_health, base_dmg);
    factor = health_to_factor(player_health);
    printf("\n2. After taking %u%% raw damage:\n", base_dmg);
    printf("   Actual damage = %u%%, remaining health = %u%%\n", lost, player_health);
    printf("   New damage factor = %.3f\n", factor);

    // 3. 第二次受伤（血量变低，实际伤害因因子接近1而变大）
    lost = apply_damage(&player_health, base_dmg);
    factor = health_to_factor(player_health);
    printf("\n3. After another %u%% raw damage:\n", base_dmg);
    printf("   Actual damage = %u%%, remaining health = %u%%\n", lost, player_health);
    printf("   Damage factor now = %.3f (closer to 1.0)\n", factor);

    // 4. 模拟回血（直接加）
    player_health += 20;
    if (player_health > 100) player_health = 100;   // 上限保护
    printf("\n4. After healing 20%%: health = %u%%\n", player_health);
    printf("   Damage factor decreases to %.3f\n", health_to_factor(player_health));

    // 5. 极端情况：空血时因子为 1.0
    player_health = 0;
    factor = health_to_factor(player_health);
    printf("\n5. When health = 0%%:\n");
    printf("   Damage factor = %.3f (max damage multiplier)\n", factor);

    return 0;
}