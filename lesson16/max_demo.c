#include <stdio.h>

// 函数原型
int max(int a, int b);

int main(void) {
    int x = 10, y = 25;
    printf("Max of %d and %d is %d\n", x, y, max(x, y));
    return 0;
}

// 函数定义
int max(int a, int b) {
    return (a > b) ? a : b;
}