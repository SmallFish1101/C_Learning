#include <stdio.h>

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("=== Index vs Pointer Offset ===\n");
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = %d, *(arr + %d) = %d\n",
               i, arr[i], i, *(arr + i));
        // 两者永远相等
    }
    return 0;
}