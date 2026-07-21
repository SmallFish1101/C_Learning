#include <stdio.h>

int main(void) {
    int num = 42;
    int *ptr = &num;

    printf("Address of num: %p\n", (void*)&num);
    printf("ptr stores:     %p\n", (void*)ptr);
    printf("value of num:   %d\n", num);
    printf("*ptr:           %d\n", *ptr);

    *ptr = 100;   // 通过指针修改
    printf("num after *ptr=100: %d\n", num);

    return 0;
}