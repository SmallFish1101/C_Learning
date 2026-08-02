/*
 * skill_chain.c
 * 第31课 练习三（选做·游戏方向）：技能效果回调链
 *
 * 功能：使用函数指针数组模拟游戏技能系统。
 *       一个技能可顺序触发多个效果（伤害、治疗、护盾等），
 *       效果函数通过回调链依次执行。
 */

#include <stdio.h>   // printf

// ========== 1. 定义技能效果回调类型 ==========
/*
 * SkillEffect:
 *   指向 "接受目标ID和效果数值，无返回值" 的函数的指针类型。
 *   所有技能效果（伤害、治疗、Buff等）都必须遵循此签名。
 */
typedef void (*SkillEffect)(int target_id, int value);

// ========== 2. 具体效果函数 ==========

/*
 * damage_effect:
 *   对目标造成伤害。
 *   参数 target_id: 目标编号
 *   参数 value    : 伤害值
 */
void damage_effect(int target_id, int value)
{
    printf("  -> Target %d takes %d damage!\n", target_id, value);
}

/*
 * heal_effect:
 *   为目标恢复生命。
 *   参数 target_id: 目标编号
 *   参数 value    : 治疗量
 */
void heal_effect(int target_id, int value)
{
    printf("  -> Target %d recovers %d HP!\n", target_id, value);
}

/*
 * shield_effect:
 *   为目标添加护盾。
 *   参数 target_id: 目标编号
 *   参数 value    : 护盾值
 */
void shield_effect(int target_id, int value)
{
    printf("  -> Target %d gains %d shield!\n", target_id, value);
}

// ========== 3. 技能执行框架 ==========
/*
 * skill_execute:
 *   按顺序执行技能的所有效果（回调链）。
 *
 *   参数 target_id  : 技能作用的目标编号
 *   参数 effects[]  : 效果回调函数指针数组
 *   参数 values[]   : 每个效果对应的数值数组（与 effects 一一对应）
 *   参数 num_effects: 效果的数量（数组长度）
 *
 *   设计优势：调用者只需准备两个数组，即可定义任意技能，
 *             主框架完全不需要修改。
 */
void skill_execute(int target_id,
                   SkillEffect effects[], const int values[],
                   int num_effects)
{
    printf("  Executing skill on target %d...\n", target_id);

    for (int i = 0; i < num_effects; i++) {
        // 安全检查：跳过 NULL 回调（防御性编程）
        if (effects[i] != NULL) {
            // ★ 核心：通过函数指针调用效果
            effects[i](target_id, values[i]);
        }
    }
    printf("\n");
}

// ========== 4. 辅助函数：打印分隔线 ==========
/*
 * print_separator:
 *   打印一条装饰分隔线，纯视觉辅助。
 *   用 static 限制为本文件内部使用，不对外暴露。
 */
static void print_separator(void)
{
    printf("-------------------------------------------\n");
}

// ========== 5. 主函数：定义并执行三个示例技能 ==========
int main(void)
{
    printf("\n=== Skill Effect Callback Chain ===\n\n");

    // ---- 技能 1：火球术（单一效果）----
    printf("[Skill] Fireball\n");
    print_separator();
    {
        SkillEffect effects[] = { damage_effect };
        int values[]           = { 45 };
        int num_effects = sizeof(effects) / sizeof(effects[0]);
        skill_execute(/* target_id */ 100, effects, values, num_effects);
    }

    // ---- 技能 2：圣光术（治疗 + 护盾）----
    printf("[Skill] Holy Light\n");
    print_separator();
    {
        SkillEffect effects[] = { heal_effect, shield_effect };
        int values[]           = { 30, 20 };
        int num_effects = sizeof(effects) / sizeof(effects[0]);
        skill_execute(/* target_id */ 200, effects, values, num_effects);
    }

    // ---- 技能 3：陨石术（双重伤害 + 自身护盾）----
    printf("[Skill] Meteor Strike\n");
    print_separator();
    {
        SkillEffect effects[] = { damage_effect, damage_effect, shield_effect };
        int values[]           = { 60, 60, 15 };
        int num_effects = sizeof(effects) / sizeof(effects[0]);
        skill_execute(/* target_id */ 300, effects, values, num_effects);
    }

    printf("=== All skills executed ===\n");

    return 0;
}