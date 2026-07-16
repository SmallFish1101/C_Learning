/*
 * draw_triangle.c
 * 第12课 练习三：用嵌套 for 循环打印等腰三角形
 *
 * 功能：安全读取 1~20 的行数，打印由星号组成的等腰三角形。
 *       例如输入 4，输出：
 *          *
 *         ***
 *        *****
 *       *******
 */

#include <stdio.h>   // printf, fgets, sscanf
#include <stdlib.h>  // exit

/*
 * read_rows:
 *   安全读取一个正整数（1~20），表示三角形的行数。
 *   return: 合法的行数。
 */
int read_rows(void)
{
    char line[100];   // 输入缓冲区

    while (1) {
        printf("Enter number of rows (1-20): ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nEnd of input.\n");
            exit(0);
        }

        int rows;
        int pos = 0;
        int matched = sscanf(line, "%d %n", &rows, &pos);

        if (matched != 1) {
            printf("  ERROR: Please enter an integer.\n");
            continue;
        }
        if (line[pos] != '\0') {
            printf("  ERROR: Extra characters after number.\n");
            continue;
        }
        if (rows < 1 || rows > 20) {
            printf("  ERROR: Rows must be between 1 and 20.\n");
            continue;
        }

        return rows;
    }
}

/*
 * draw_triangle:
 *   打印由星号组成的等腰三角形。
 *   rows: 三角形的行数。
 *
 *   规律（第 i 行，i 从 1 开始）：
 *     - 空格数 = rows - i
 *     - 星号数 = 2 * i - 1
 */
void draw_triangle(int rows)
{
    for (int i = 1; i <= rows; i++) {

        // 打印前导空格：rows - i 个
        for (int space = 1; space <= rows - i; space++) {
            putchar(' ');   // 或 printf(" ");
        }

        // 打印星号：2*i - 1 个
        for (int star = 1; star <= 2 * i - 1; star++) {
            putchar('*');   // 或 printf("*");
        }

        // 换行
        putchar('\n');
    }
}

int main(void)
{
    printf("=== Triangle Printer ===\n\n");

    int rows = read_rows();   // 获取合法行数

    printf("\n");
    draw_triangle(rows);      // 打印三角形

    return 0;
}