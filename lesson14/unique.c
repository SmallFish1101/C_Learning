/*
 * unique.c
 * 第14课 练习二：去重统计
 *
 * 功能：输入 N 个整数（允许重复），
 *       统计其中不同值的个数，
 *       并输出去重后的元素列表（保持首次出现的顺序）。
 */

#include <stdio.h>   // printf, fgets, sscanf
#include <stdlib.h>  // exit
#include <stdbool.h> // bool, true, false

#define ARRAY_SIZE 10   // 输入元素个数

/*
 * read_int:
 *   安全读取一个整数（与前几课完全相同的模板）。
 *   return: 用户输入的合法整数。
 */
int read_int(void)
{
    char line[100];

    while (1) {
        printf("Enter an integer: ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nEnd of input.\n");
            exit(0);
        }

        int value;
        int pos = 0;
        int matched = sscanf(line, "%d %n", &value, &pos);

        if (matched != 1) {
            printf("  ERROR: Please enter a valid integer.\n");
            continue;
        }
        if (line[pos] != '\0') {
            printf("  ERROR: Extra characters after number.\n");
            continue;
        }

        return value;
    }
}

/*
 * is_first_occurrence:
 *   检查 arr[i] 是否在索引 0..i-1 之间已经出现过。
 *   arr:  数组首地址
 *   i:    当前要检查的索引
 *   return: true 表示是首次出现，false 表示之前已出现过
 */
bool is_first_occurrence(int arr[], int i)
{
    // 遍历 arr[0] 到 arr[i-1]，看是否有与 arr[i] 相等的值
    for (int j = 0; j < i; j++) {
        if (arr[j] == arr[i]) {
            return false;   // 找到了重复值，不是首次出现
        }
    }
    return true;            // 没找到重复值，是首次出现
}

int main(void)
{
    int arr[ARRAY_SIZE];           // 存放输入的所有元素
    int unique_vals[ARRAY_SIZE];   // 存放去重后的值（首次出现的顺序）
    int unique_count = 0;          // 不同值的个数

    printf("=== Unique Value Counter ===\n");
    printf("Please enter %d integers (duplicates allowed).\n\n", ARRAY_SIZE);

    // 1. 录入数组
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("Element [%d]: ", i);
        arr[i] = read_int();
    }

    // 2. 去重统计
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (is_first_occurrence(arr, i)) {
            // 是首次出现：存入 unique_vals，计数器加 1
            unique_vals[unique_count] = arr[i];
            unique_count++;
        }
        // 如果不是首次出现，直接跳过（什么都不做）
    }

    // 3. 输出结果
    printf("\nOriginal array:\n[ ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d", arr[i]);
        if (i < ARRAY_SIZE - 1) printf(", ");
    }
    printf(" ]\n");

    printf("\nNumber of unique values: %d\n", unique_count);

    printf("Unique values (first occurrence order):\n[ ");
    for (int i = 0; i < unique_count; i++) {
        printf("%d", unique_vals[i]);
        if (i < unique_count - 1) printf(", ");
    }
    printf(" ]\n");

    return 0;
}