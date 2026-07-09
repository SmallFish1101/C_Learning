#include <stdio.h>

int main(void) {
    int num = 255;
    double pi = 3.1415926535;
    char ch = 'A';

    printf("=== printf Formatting Demo ===\n\n");

    // 整数多种进制
    printf("Decimal:     %d\n", num);     // 255
    printf("Hex (lower): %x\n", num);     // ff
    printf("Hex (upper): %X\n", num);     // FF
    printf("Octal:       %o\n", num);     // 377

    // 浮点精度
    printf("Default:     %f\n", pi);      // 3.141593
    printf("Prec 2:      %.2f\n", pi);    // 3.14
    printf("Width 10:    |%10.2f|\n", pi);// |      3.14|
    printf("Left align:  |%-10.2f|\n", pi);//|3.14      |
    printf("Scientific:  %e\n", pi);      // 3.141593e+00

    // 字符与字符串
    printf("Char:        %c (ASCII %d)\n", ch, ch);  // A (ASCII 65)
    printf("String:      %s\n", "Hello, C!");

    // 特殊格式
    printf("Percent:     100%% of %d\n", 100);       // 100% of 100

    return 0;
}