/*
 * matrix_multiply.c
 * 第30课 练习二：用二级指针实现动态矩阵乘法
 *
 * 计算 A(2×3) × B(3×4) = C(2×4)
 * 所有内存分配均检查返回值。
 */

#include <stdio.h>    // printf
#include <stdlib.h>   // malloc, free, exit

// ========== 1. 创建矩阵 ==========
/*
 * create_matrix:
 *   在堆上动态创建 rows×cols 的二维矩阵（int 类型）。
 *   使用二级指针：先分配 rows 个行指针，再为每行分配 cols 个 int。
 *
 *   参数 rows: 行数
 *   参数 cols: 列数
 *   返回: 指向矩阵的二级指针；若分配失败则退出程序。
 */
int **create_matrix(int rows, int cols)
{
    // 第一步：分配 rows 个行指针（每个行指针是 int* 类型）
    int **mat = (int **)malloc(rows * sizeof(int *));
    if (mat == NULL) {
        printf("Error: malloc failed for row pointers.\n");
        exit(1);
    }

    // 第二步：为每一行分配 cols 个 int
    for (int i = 0; i < rows; i++) {
        mat[i] = (int *)malloc(cols * sizeof(int));
        if (mat[i] == NULL) {
            // 如果某行分配失败，需要释放之前已分配的行和指针数组
            printf("Error: malloc failed for row %d.\n", i);
            for (int j = 0; j < i; j++) {
                free(mat[j]);
            }
            free(mat);
            exit(1);
        }
    }

    return mat;
}

// ========== 2. 填充矩阵 ==========
/*
 * fill_matrix:
 *   按公式填充矩阵元素。
 *   pattern = 1: A[i][j] = i * cols + j + 1 （逐行递增，从 1 开始）
 *   pattern = 2: B[i][j] = (i + 1) * 10 + (j + 1) （便于人工验证乘法结果）
 *
 *   参数 mat    : 矩阵二级指针
 *   参数 rows   : 行数
 *   参数 cols   : 列数
 *   参数 pattern: 填充模式（1 或 2）
 */
void fill_matrix(int **mat, int rows, int cols, int pattern)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (pattern == 1) {
                // A 矩阵：1, 2, 3, 4, 5, 6
                mat[i][j] = i * cols + j + 1;
            } else {
                // B 矩阵：11, 12, 13, 14, 21, ... （i从0开始）
                mat[i][j] = (i + 1) * 10 + (j + 1);
            }
        }
    }
}

// ========== 3. 矩阵乘法 ==========
/*
 * multiply_matrices:
 *   计算 C = A × B。
 *   A 是 m×n 矩阵，B 是 n×p 矩阵，C 是 m×p 矩阵。
 *
 *   参数 A: 左矩阵（m×n）
 *   参数 B: 右矩阵（n×p）
 *   参数 m: A 的行数
 *   参数 n: A 的列数（也是 B 的行数）
 *   参数 p: B 的列数
 *   返回: 新创建的 C 矩阵（m×p）
 *
 *   算法：三重循环
 *     for i = 0..m-1      （C 的行）
 *       for j = 0..p-1    （C 的列）
 *         sum = 0
 *         for k = 0..n-1  （A 的列 / B 的行）
 *           sum += A[i][k] * B[k][j]
 *         C[i][j] = sum
 */
int **multiply_matrices(int **A, int **B, int m, int n, int p)
{
    // 创建结果矩阵 C (m × p)
    int **C = create_matrix(m, p);

    // 三重循环计算矩阵乘法
    for (int i = 0; i < m; i++) {          // 遍历 C 的每一行
        for (int j = 0; j < p; j++) {      // 遍历 C 的每一列
            int sum = 0;
            for (int k = 0; k < n; k++) {  // 累加 A 的行 × B 的列
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }

    return C;
}

// ========== 4. 打印矩阵 ==========
/*
 * print_matrix:
 *   格式化打印矩阵，带标题和行列标注。
 */
void print_matrix(int **mat, int rows, int cols, const char *title)
{
    printf("%s (%d×%d):\n", title, rows, cols);
    for (int i = 0; i < rows; i++) {
        printf("  ");
        for (int j = 0; j < cols; j++) {
            printf("%5d", mat[i][j]);   // %5d 保证列对齐
        }
        printf("\n");
    }
    printf("\n");
}

// ========== 5. 释放矩阵 ==========
/*
 * free_matrix:
 *   释放动态分配的矩阵内存。
 *   释放顺序：先释放每一行，再释放行指针数组。
 *   释放后不置 NULL（因为是调用者传入的指针拷贝，置 NULL 无意义）。
 *
 *   参数 mat : 矩阵二级指针
 *   参数 rows: 行数
 */
void free_matrix(int **mat, int rows)
{
    // 第一步：逐行释放
    for (int i = 0; i < rows; i++) {
        free(mat[i]);
    }
    // 第二步：释放行指针数组本身
    free(mat);
}

// ========== 主函数 ==========
int main(void)
{
    printf("=== Dynamic Matrix Multiplication ===\n\n");

    // 定义维度
    int m = 2;   // A 的行数
    int n = 3;   // A 的列数 = B 的行数
    int p = 4;   // B 的列数

    // 1. 创建矩阵 A (2×3) 和 B (3×4)
    int **A = create_matrix(m, n);
    int **B = create_matrix(n, p);

    // 2. 填充矩阵（可预测的数字，便于手工验证）
    fill_matrix(A, m, n, 1);   // A[i][j] = i * n + j + 1
    fill_matrix(B, n, p, 2);   // B[i][j] = (i+1)*10 + (j+1)

    // 3. 打印 A 和 B
    print_matrix(A, m, n, "Matrix A");
    print_matrix(B, n, p, "Matrix B");

    // 4. 计算 C = A × B
    int **C = multiply_matrices(A, B, m, n, p);

    // 5. 打印结果矩阵 C
    print_matrix(C, m, p, "Matrix C = A × B");

    // 6. 手工验证提示
    printf("=== Verification ===\n");
    printf("C[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0] + A[0][2]*B[2][0]\n");
    printf("        = 1×11 + 2×21 + 3×31 = 11 + 42 + 93 = 146\n");
    printf("See output above to confirm.\n\n");

    // 7. 释放所有矩阵（顺序不重要：A、B、C 是独立的）
    free_matrix(A, m);
    free_matrix(B, n);
    free_matrix(C, m);

    printf("All matrices freed.\n");
    return 0;
}