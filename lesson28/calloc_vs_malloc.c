#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n = 5;

    // malloc：不初始化，内容是垃圾值
    int *a = (int *)malloc(n * sizeof(int));
    printf("malloc (uninitialized): ");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    // calloc：自动清零
    int *b = (int *)calloc(n, sizeof(int));
    printf("calloc (zero-initialized): ");
    for (int i = 0; i < n; i++) printf("%d ", b[i]);
    printf("\n");

    free(a);
    free(b);
    return 0;
}