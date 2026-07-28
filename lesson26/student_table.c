#include <stdio.h>
#include <stdlib.h>   // qsort, bsearch
#include <string.h>   // strcmp

// ---- 结构体定义 ----
typedef struct {
    char name[32];
    int  id;
    float score;
} Student;

// 辅助打印函数
void print_table(const Student arr[], int n) {
    printf("%-4s %-15s %-6s %s\n", "No.", "Name", "ID", "Score");
    for (int i = 0; i < n; i++)
        printf("%-4d %-15s %-6d %.1f\n",
               i+1, arr[i].name, arr[i].id, arr[i].score);
}

// ---- 比较函数 ----
int cmp_by_score_desc(const void *a, const void *b) {
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    if (s1->score > s2->score) return -1;   // 高分在前
    if (s1->score < s2->score) return 1;
    return 0;
}

int cmp_by_name(const void *a, const void *b) {
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    return strcmp(s1->name, s2->name);
}

int main(void) {
    Student class2024[] = {
        {"Alice", 1001, 92.5f},
        {"Bob",   1002, 85.0f},
        {"Carol", 1003, 88.5f},
        {"David", 1004, 78.0f},
        {"Eve",   1005, 95.0f},
    };
    int n = sizeof(class2024) / sizeof(class2024[0]);

    printf("=== Original Table ===\n");
    print_table(class2024, n);

    // 按成绩降序
    qsort(class2024, n, sizeof(Student), cmp_by_score_desc);
    printf("\n=== Sorted by Score (desc) ===\n");
    print_table(class2024, n);

    // 按姓名升序
    qsort(class2024, n, sizeof(Student), cmp_by_name);
    printf("\n=== Sorted by Name ===\n");
    print_table(class2024, n);

    return 0;
}