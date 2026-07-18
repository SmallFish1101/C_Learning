/*
 * scores.c
 * 第14课 实例1：一维数组处理学生成绩
 *
 * 功能：录入5个学生的成绩，计算总分、平均分、最高分、最低分。
 */

#include <stdio.h>

#define STUDENT_COUNT 5    // 用宏定义数组大小，方便修改

int main(void) {
    int scores[STUDENT_COUNT];

    // 1. 录入成绩（使用安全输入的简化版，直接用 scanf 演示，实际项目请用 fgets+sscanf）
    for (int i = 0; i < STUDENT_COUNT; i++) {
        printf("Enter score for student %d: ", i + 1);
        scanf("%d", &scores[i]);
    }

    // 2. 计算总分、平均分、最高分、最低分
    int sum = 0;
    int max = scores[0];   // 初始化为第一个元素
    int min = scores[0];

    for (int i = 0; i < STUDENT_COUNT; i++) {
        sum += scores[i];

        if (scores[i] > max) {
            max = scores[i];
        }
        if (scores[i] < min) {
            min = scores[i];
        }
    }

    float average = (float)sum / STUDENT_COUNT;   // 浮点除法

    // 3. 输出结果
    printf("\n=== Results ===\n");
    printf("Scores: ");
    for (int i = 0; i < STUDENT_COUNT; i++) {
        printf("%d ", scores[i]);
    }
    printf("\nTotal:   %d\n", sum);
    printf("Average: %.2f\n", average);
    printf("Max:     %d\n", max);
    printf("Min:     %d\n", min);

    return 0;
}