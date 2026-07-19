#include <stdio.h>

// 函数原型
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

int main(void) {
    double a = 10.5, b = 2.5;
    printf("Add: %.2f\n", add(a, b));
    printf("Subtract: %.2f\n", subtract(a, b));
    printf("Multiply: %.2f\n", multiply(a, b));
    printf("Divide: %.2f\n", divide(a, b));
    return 0;
}

double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) {
    if (b == 0) {
        printf("Error: division by zero\n");
        return 0;   // 简单处理，实际项目应更好的错误处理
    }
    return a / b;
}