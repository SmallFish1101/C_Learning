/*
 * multi_sort.c
 * 第26课 练习一：用 qsort 实现多条件排序
 *
 * 排序规则：部门（字典序升序）→ 工资（降序）
 */

#include <stdio.h>    // printf
#include <stdlib.h>   // qsort
#include <string.h>   // strcmp, strlen

// ========== 结构体定义 ==========
typedef struct {
    char name[32];         // 姓名
    char department[32];   // 部门
    int  salary;           // 工资
} Employee;

// ========== 比较函数 ==========
/*
 * cmp_by_dept_then_salary:
 *   qsort 的比较函数。
 *   首先按 department 升序，相同时按 salary 降序。
 *   参数 a, b: 指向数组中两个元素的指针（需强制转换）
 *   返回: <0 表示 a 排在 b 前，0 表示相等，>0 表示 a 排在 b 后
 */
int cmp_by_dept_then_salary(const void *a, const void *b)
{
    const Employee *e1 = (const Employee *)a;
    const Employee *e2 = (const Employee *)b;

    // ---- 第 1 级：部门（字符串升序） ----
    int dept_cmp = strcmp(e1->department, e2->department);
    if (dept_cmp != 0) {
        // 部门不同，排序结果由部门比较结果决定
        return dept_cmp;
    }

    // ---- 第 2 级：工资（数值降序） ----
    // 降序：如果 e1 工资高，e1 应该排在 e2 前面 → 返回负数
    if (e1->salary > e2->salary) return -1;
    if (e1->salary < e2->salary) return 1;
    return 0;
}

// ========== 辅助函数：打印表格 ==========
void print_table(const Employee *arr, int n, const char *title)
{
    printf("=== %s ===\n", title);
    printf("%-12s %-15s %s\n", "Name", "Department", "Salary");
    printf("---------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-12s %-15s %d\n",
               arr[i].name,
               arr[i].department,
               arr[i].salary);
    }
    printf("\n");
}

int main(void)
{
    // 测试数据：多个部门，各包含若干员工
    Employee team[] = {
        {"Alice",   "Engineering", 8000},
        {"Bob",     "Marketing",   6000},
        {"Carol",   "Engineering", 9000},
        {"David",   "HR",          5000},
        {"Eve",     "Marketing",   7500},
        {"Frank",   "Engineering", 7500},
        {"Grace",   "HR",          5500},
        {"Henry",   "Marketing",   6000},
    };
    int n = sizeof(team) / sizeof(team[0]);

    print_table(team, n, "Before Sorting");

    // 调用 qsort
    qsort(team, n, sizeof(Employee), cmp_by_dept_then_salary);

    print_table(team, n, "After Sorting (dept asc, salary desc)");

    return 0;
}