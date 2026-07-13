/*
 * grade.c
 * 第11课 作业一：成绩等级评定
 *
 * 功能：安全读取一个 0~100 的整数成绩，输出对应的等级（A-F）。
 */

#include <stdio.h>   // printf, fgets, sscanf
#include <stdlib.h>  // exit

/*
 * read_score:
 *   安全读取一个 0~100 之间的整数成绩。
 *   return: 合法的成绩值。
 */
int read_score(void)
{
    char line[100];   // 存放用户输入的一整行

    while (1) {
        printf("Enter score (0-100): ");

        // fgets 读取一行，如果返回 NULL 表示 EOF（Ctrl+Z / Ctrl+D）
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nEnd of input.\n");
            exit(0);   // 正常退出
        }

        int score;
        int pos = 0;   // 记录 sscanf 解析停止的位置

        // 尝试从 line 中解析整数
        // %d 读取整数，%n 记下此时消耗了多少个字符
        int matched = sscanf(line, "%d %n", &score, &pos);

        // 检查 1：必须成功匹配到一个整数
        if (matched != 1) {
            printf("  ERROR: Please enter a valid integer.\n");
            continue;   // 回到 while 开头，重新输入
        }

        // 检查 2：行内不能有残余字符（如 "85abc"）
        if (line[pos] != '\0') {
            printf("  ERROR: Extra characters after number.\n");
            continue;
        }

        // 检查 3：范围 0~100
        if (score < 0 || score > 100) {
            printf("  ERROR: Score must be between 0 and 100.\n");
            continue;
        }

        // 全部通过，返回成绩
        return score;
    }
}

/*
 * get_grade:
 *   根据成绩返回等级字符。
 *   score: 0~100 的整数。
 *   return: 等级字符 'A', 'B', 'C', 'D', 'F'。
 */
char get_grade(int score)
{
    if (score >= 90) {
        return 'A';
    } else if (score >= 80) {
        return 'B';
    } else if (score >= 70) {
        return 'C';
    } else if (score >= 60) {
        return 'D';
    } else {
        return 'F';
    }
}

int main(void)
{
    printf("=== Grade Calculator ===\n\n");

    // 读取成绩
    int score = read_score();

    // 获取等级
    char grade = get_grade(score);

    // 输出结果
    printf("\n  Score: %d -> Grade: %c\n", score, grade);

    return 0;
}