#include <stdio.h>
#include <stdlib.h>

// 创建一个 int 数组，填充 1~n，通过二级指针传出
void create_and_fill(int **arr_ptr, int n) {
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) { *arr_ptr = NULL; return; }
    for (int i = 0; i < n; i++) arr[i] = i + 1;
    *arr_ptr = arr;   // 把局部指针 arr 的值（新内存地址）赋给外部的指针
}

int main(void) {
    int *data = NULL;
    int n = 5;
    create_and_fill(&data, n);
    if (data) {
        for (int i = 0; i < n; i++) printf("%d ", data[i]);
        printf("\n");
        free(data);
    }
    return 0;
}