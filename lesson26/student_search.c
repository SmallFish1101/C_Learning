/*
 * student_search.c
 * 第26课 练习二：用 bsearch 按学号查找学生
 *
 * 要求：程序先按学号排序，然后提示用户输入学号，
 *       用 bsearch 二分查找，打印查找结果。
 */

#include <stdio.h>    // printf, fgets, sscanf
#include <stdlib.h>   // qsort, bsearch, exit
#include <string.h>   // strlen

// ========== 结构体定义 ==========
typedef struct {
    char name[32];
    int  id;
    float score;
} Student;

// ========== 辅助函数：打印表格 ==========
void print_table(const Student *arr, int n, const char *title)
{
    printf("=== %s ===\n", title);
    printf("%-4s %-15s %-6s %s\n", "No.", "Name", "ID", "Score");
    printf("---------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-4d %-15s %-6d %.1f\n",
               i + 1, arr[i].name, arr[i].id, arr[i].score);
    }
    printf("\n");
}

// ========== qsort 比较函数：按 id 升序 ==========
/*
 * cmp_by_id_for_qsort:
 *   qsort 的比较函数。
 *   参数 a, b: 指向数组中两个元素的指针（const void*），需转换为 const Student*。
 *   返回: 负数表示 a 排在 b 前，0 表示相等，正数表示 a 排在 b 后。
 */
int cmp_by_id_for_qsort(const void *a, const void *b)
{
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    return s1->id - s2->id;
}

// ========== bsearch 比较函数：按 id 查找 ==========
/*
 * cmp_by_id_for_bsearch:
 *   bsearch 的比较函数。
 *   注意参数顺序：第一个参数是查找键（key），第二个是数组元素（element）。
 *
 *   参数 key: 指向要查找的目标学号（int*）的指针。
 *   参数 element: 指向数组中当前元素的指针（const Student*）。
 *   返回: 与 qsort 相同的规则——<0 表示 key 在 element 前面，
 *         0 表示找到，>0 表示 key 在 element 后面。
 */
int cmp_by_id_for_bsearch(const void *key, const void *element)
{
    // key 是调用 bsearch 时传入的 &target_id，即 int* 类型
    int target_id = *(const int *)key;

    // element 是数组中某个 Student 元素的地址
    const Student *s = (const Student *)element;

    return target_id - s->id;
}

// ========== 安全输入辅助函数 ==========
/*
 * safe_read_int:
 *   安全读取一个整数（复用第10课模板）。
 *   参数 prompt: 提示信息。
 *   返回: 用户输入的合法整数。
 */
int safe_read_int(const char *prompt)
{
    char line[100];

    while (1) {
        printf("%s", prompt);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nEnd of input.\n");
            exit(0);
        }

        int value;
        int pos = 0;
        int matched = sscanf(line, "%d %n", &value, &pos);

        if (matched != 1) {
            printf("  ERROR: Please enter an integer.\n");
            continue;
        }
        if (line[pos] != '\0') {
            printf("  ERROR: Extra characters after number.\n");
            continue;
        }

        return value;
    }
}

// ========== 主函数 ==========
int main(void)
{
    // 1. 定义学生数组（学号未排序）
    Student class2024[] = {
        {"Alice", 1003, 92.5f},
        {"Bob",   1001, 85.0f},
        {"Carol", 1005, 88.5f},
        {"David", 1002, 78.0f},
        {"Eve",   1004, 95.0f},
    };
    int n = sizeof(class2024) / sizeof(class2024[0]);

    // 2. 打印原始表格
    print_table(class2024, n, "Original Table (unsorted)");

    // 3. 按学号排序（bsearch 的前提）
    qsort(class2024, n, sizeof(Student), cmp_by_id_for_qsort);
    print_table(class2024, n, "Sorted by ID");

    // 4. 用户输入要查找的学号
    printf("=== Student Search ===\n");
    int target_id = safe_read_int("Enter student ID to search: ");

    // 5. 使用 bsearch 二分查找
    Student *found = (Student *)bsearch(
        &target_id,                  // 查找键的地址
        class2024,                   // 数组首地址
        n,                           // 元素个数
        sizeof(Student),             // 每个元素大小
        cmp_by_id_for_bsearch        // 比较函数
    );

    // 6. 输出查找结果
    if (found != NULL) {
        printf("\n  Student found:\n");
        printf("  Name  : %s\n", found->name);
        printf("  ID    : %d\n", found->id);
        printf("  Score : %.1f\n", found->score);
    } else {
        printf("\n  Student with ID %d not found.\n", target_id);
    }

    return 0;
}