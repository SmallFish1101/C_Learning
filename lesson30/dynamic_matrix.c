#include <stdio.h>
#include <stdlib.h>

int **create_matrix(int rows, int cols) {
    int **mat = (int **)malloc(rows * sizeof(int *));
    if (mat == NULL) exit(1);
    for (int i = 0; i < rows; i++) {
        mat[i] = (int *)malloc(cols * sizeof(int));
        if (mat[i] == NULL) exit(1);
    }
    return mat;
}

void fill_matrix(int **mat, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            mat[i][j] = i * cols + j;   // 按行列编号填充
}

void print_matrix(int **mat, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%4d", mat[i][j]);
        printf("\n");
    }
}

void free_matrix(int **mat, int rows) {
    for (int i = 0; i < rows; i++) {
        free(mat[i]);
        mat[i] = NULL;
    }
    free(mat);
}

int main(void) {
    int rows = 3, cols = 4;
    int **matrix = create_matrix(rows, cols);
    fill_matrix(matrix, rows, cols);
    printf("=== Dynamic Matrix (3x4) ===\n");
    print_matrix(matrix, rows, cols);
    free_matrix(matrix, rows);
    return 0;
}