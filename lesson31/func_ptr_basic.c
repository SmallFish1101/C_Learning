#include <stdio.h>

typedef int (*MathFunc)(int, int);   // 函数指针类型别名

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int div_int(int a, int b) { return (b != 0) ? a / b : 0; }

int main(void) {
    MathFunc ops[] = { add, sub, mul, div_int };
    const char *names[] = { "Add", "Sub", "Mul", "Div" };

    for (int i = 0; i < 4; i++) {
        printf("%s(10, 3) = %d\n", names[i], ops[i](10, 3));
    }
    return 0;
}