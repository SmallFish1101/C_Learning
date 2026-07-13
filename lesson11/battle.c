/*
 * battle.c
 * 第11课 作业三（选做·游戏方向）：简易回合制战斗系统
 *
 * 游戏规则：
 *   玩家 vs 怪物，初始血量各 100。
 *   玩家可攻击/防御/逃跑，怪物自动反击。
 *   一方血量 ≤ 0 时战斗结束。
 */

#include <stdio.h>   // printf, fgets, sscanf
#include <stdlib.h>  // rand, srand, exit
#include <time.h>    // time（用于随机数种子）
#include <string.h>  // strlen（用于去掉换行符）

/*
 * read_menu_choice:
 *   安全读取玩家的菜单选择（1-3）。
 *   return: 1=攻击, 2=防御, 3=逃跑
 */
int read_menu_choice(void)
{
    char line[100];

    while (1) {
        printf("Choose action (1:Attack, 2:Defend, 3:Run): ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nEnd of input.\n");
            exit(0);
        }

        int choice;
        int pos = 0;
        int matched = sscanf(line, "%d %n", &choice, &pos);

        // 输入必须是 1 到 3 之间的整数，且没有多余字符
        if (matched == 1 && line[pos] == '\0' && choice >= 1 && choice <= 3) {
            return choice;
        }

        printf("  Invalid input. Please enter 1, 2, or 3.\n");
    }
}

/*
 * random_range:
 *   返回 [min, max] 区间内的随机整数。
 *   min: 最小值（包含）
 *   max: 最大值（包含）
 *   return: 随机整数
 *
 *   示例：random_range(15, 25) 返回 15, 16, ..., 25 中的一个
 */
int random_range(int min, int max)
{
    // rand() % N 返回 0 ~ N-1，加上 min 得到 min ~ min+N-1
    // N = max - min + 1，所以范围是 min ~ max
    return min + rand() % (max - min + 1);
}

int main(void)
{
    // 用当前时间初始化随机数种子，确保每次运行结果不同
    srand((unsigned)time(NULL));

    printf("=== Battle System Demo ===\n");
    printf("A wild monster appears!\n\n");

    int player_hp = 100;    // 玩家血量
    int monster_hp = 100;   // 怪物血量
    int round = 1;          // 回合计数器
    int defending = 0;      // 是否防御中（0=否，1=是，只持续一回合）
    int battle_over = 0;    // 战斗是否结束（0=进行中，1=结束）

    // 主循环：每回合执行一次
    while (!battle_over)
    {
        // ===== 1. 显示当前状态 =====
        printf("\n--- Round %d ---\n", round);
        printf("Player HP: %d | Monster HP: %d\n", player_hp, monster_hp);

        // 重置防御状态（防御只持续一回合）
        if (defending) {
            printf("(You are defending this round!)\n");
        }

        // ===== 2. 玩家回合 =====
        int choice = read_menu_choice();

        switch (choice)
        {
            case 1: // 攻击
            {
                int damage = random_range(15, 25);   // 随机伤害 15~25
                printf(">> You attack the monster and deal %d damage!\n", damage);
                monster_hp -= damage;

                // 攻击行动已执行，防御状态取消
                defending = 0;
                break;
            }

            case 2: // 防御
                printf(">> You raise your shield!\n");
                defending = 1;   // 本回合防御，怪物伤害减半
                break;

            case 3: // 逃跑
            {
                printf(">> You try to run away...\n");

                // 50% 概率逃脱：rand() % 2 生成 0 或 1
                int escape_chance = rand() % 2;   // 0 或 1

                if (escape_chance == 0) {
                    printf(">> You escaped safely!\n");
                    battle_over = 1;   // 战斗结束
                } else {
                    printf(">> Failed to escape! The monster attacks!\n");
                    // 逃跑失败，怪物本轮正常攻击（不跳过怪物回合）
                }
                defending = 0;
                break;
            }
        }

        // ===== 3. 检查怪物是否死亡 =====
        if (monster_hp <= 0) {
            printf("\nThe monster has been defeated!\n");
            printf("You win!\n");
            battle_over = 1;
            continue;   // 跳过怪物回合
        }

        // ===== 4. 怪物回合（仅当战斗未结束且玩家行动不是逃跑成功时） =====
        if (!battle_over) {
            int monster_damage = random_range(10, 20);   // 怪物随机伤害 10~20

            // 如果玩家选择了防御，伤害减半
            if (defending) {
                monster_damage = monster_damage / 2;   // 整数除法，向下取整
                printf(">> The monster attacks, but your shield reduces it to %d damage!\n", monster_damage);
            } else {
                printf(">> The monster attacks and deals %d damage!\n", monster_damage);
            }

            player_hp -= monster_damage;
            defending = 0;   // 防御状态在回合结束时清除
        }

        // ===== 5. 检查玩家是否死亡 =====
        if (player_hp <= 0) {
            printf("\nYou have been defeated by the monster...\n");
            printf("Game Over.\n");
            battle_over = 1;
        }

        // 回合计数器 +1
        round++;
    }

    printf("\nThanks for playing!\n");
    return 0;
}