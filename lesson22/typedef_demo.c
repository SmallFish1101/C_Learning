#include <stdio.h>

// 1. 简化结构体
typedef struct {
    int x;
    int y;
} Point;

// 2. 简化函数指针类型
typedef int (*MathOp)(int, int);

// 实现两个符合 MathOp 签名的函数
int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

int main(void) {
    Point p = {3, 4};
    printf("Point: (%d, %d)\n", p.x, p.y);

    MathOp op = add;
    printf("add(10,5) = %d\n", op(10, 5));

    op = mul;
    printf("mul(10,5) = %d\n", op(10, 5));

    return 0;
}