/*
 * skill.h
 * 第22课 练习三：技能系统模块的公开接口
 *
 * 提供 SkillID 枚举、Skill 结构体，以及查询、打印技能的函数。
 */

#ifndef SKILL_H
#define SKILL_H

// ========== 技能 ID 枚举 ==========
/*
 * SkillID:
 *   游戏中所有可用技能的唯一标识。
 *   最后一项 SKILL_COUNT 用于表示技能总数，不是实际技能。
 */
typedef enum {
    SKILL_ATTACK,      // 普通攻击
    SKILL_HEAL,        // 治疗
    SKILL_FIREBALL,    // 火球术
    SKILL_ICE_BLAST,   // 冰霜冲击
    SKILL_COUNT        // 技能总数（自动为 4）
} SkillID;

// ========== 技能结构体 ==========
/*
 * Skill:
 *   描述一个技能的所有静态数据。
 *   成员 id：技能唯一标识
 *   成员 name：技能名称（字符串字面量，只读）
 *   成员 damage：对敌人造成的基础伤害（治疗则为治疗量）
 *   成员 cooldown：冷却时间（单位：秒）
 *   成员 mana_cost：每次施放消耗的法力值
 */
typedef struct {
    SkillID id;
    const char *name;
    int damage;
    int cooldown;
    int mana_cost;
} Skill;

// ========== 公开函数声明 ==========

/*
 * get_skill:
 *   根据技能 ID 返回对应的技能数据指针。
 *   参数 id: 技能 ID（必须在 0 ~ SKILL_COUNT-1 之间）
 *   返回: 指向技能数据的指针；若 id 无效则返回 NULL
 */
const Skill* get_skill(SkillID id);

/*
 * print_skill:
 *   打印单个技能的详细信息。
 *   参数 sk: 指向技能的指针（只读）
 */
void print_skill(const Skill *sk);

/*
 * print_all_skills:
 *   打印所有可用技能的列表。
 */
void print_all_skills(void);

#endif