/*
 * skill.c
 * 技能系统的内部实现。
 *
 * 使用 static 数组存储所有技能数据，外部只能通过公开接口访问。
 * 这种模式在游戏中常用于配置表（数据与逻辑分离）。
 */

#include <stdio.h>   // printf
#include "skill.h"

// ========== 技能数据库（私有，外部不可见）==========
// 使用 static 确保本文件外的代码无法直接访问此数组
static const Skill skill_database[SKILL_COUNT] = {
    // id                name          damage  cooldown  mana_cost
    { SKILL_ATTACK,      "Attack",     15,     0,        0   },
    { SKILL_HEAL,        "Heal",       -20,    8,        15  },   // damage 为负数表示治疗量
    { SKILL_FIREBALL,    "Fireball",   45,     12,       25  },
    { SKILL_ICE_BLAST,   "Ice Blast",  35,     10,       20  },
};

// ========== 接口实现 ==========

const Skill* get_skill(SkillID id)
{
    // 检查 id 是否在有效范围内
    if (id >= 0 && id < SKILL_COUNT) {
        return &skill_database[id];
    }
    return NULL;   // 无效 ID，返回空指针
}

void print_skill(const Skill *sk)
{
    if (sk == NULL) {
        printf("  Invalid skill.\n");
        return;
    }

    // 格式化打印技能信息
    printf("  %-15s", sk->name);
    if (sk->id == SKILL_HEAL) {
        // 治疗技能的特殊显示
        printf("Heal: %d HP", -sk->damage);
    } else {
        printf("Damage: %d", sk->damage);
    }
    printf("  |  Cooldown: %2ds", sk->cooldown);
    printf("  |  Mana: %2d\n", sk->mana_cost);
}

void print_all_skills(void)
{
    printf("\n=== All Skills ===\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < SKILL_COUNT; i++) {
        printf("  [%d] ", i);
        print_skill(&skill_database[i]);
    }
    printf("--------------------------------------------\n");
}