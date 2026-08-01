#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Usage: %s <num1> <op> <num2>\n", argv[0]);
        return 1;
    }
    double a = atof(argv[1]);
    char op  = argv[2][0];   // 运算符字符串的首字符
    double b = atof(argv[3]);
    double result;

    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/':
            if (b == 0.0) { printf("Error: division by zero.\n"); return 2; }
            result = a / b;
            break;
        default:
            printf("Error: unknown operator '%c'.\n", op);
            return 3;
    }
    printf("%.2f %c %.2f = %.2f\n", a, op, b, result);
    return 0;
}