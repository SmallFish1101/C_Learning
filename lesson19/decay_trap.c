#include <stdio.h>

// 函数内 arr 退化为指针
void print_size(int arr[]) {
    printf("Inside function: sizeof(arr) = %zu\n", sizeof(arr));
}

int main(void) {
    int arr[10];
    printf("In main: sizeof(arr) = %zu\n", sizeof(arr));
    print_size(arr);
    return 0;
}
// 输出：
// In main: sizeof(arr) = 40
// Inside function: sizeof(arr) = 8 (64位系统)