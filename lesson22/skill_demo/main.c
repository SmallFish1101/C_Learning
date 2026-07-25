/*
 * main.c
 * 技能系统测试程序：展示技能的查询与打印。
 */

#include <stdio.h>
#include "skill.h"

int main(void)
{
    printf("=== Skill System Demo ===\n");

    // 1. 打印所有技能
    print_all_skills();

    // 2. 查询并打印单个技能
    printf("\n--- Query single skill ---\n");
    const Skill *sk = get_skill(SKILL_FIREBALL);
    printf("fireball: ");
    print_skill(sk);

    // 3. 测试无效 ID
    printf("\n--- Invalid ID test ---\n");
    const Skill *invalid = get_skill((SkillID)999);
    printf("invalid ID: ");
    print_skill(invalid);

    // 4. 遍历所有技能，统计总冷却时间
    printf("\n--- Stats ---\n");
    int total_cooldown = 0;
    for (SkillID id = 0; id < SKILL_COUNT; id++) {
        const Skill *s = get_skill(id);
        if (s) total_cooldown += s->cooldown;
    }
    printf("Total cooldown of all skills: %d seconds\n", total_cooldown);

    return 0;
}