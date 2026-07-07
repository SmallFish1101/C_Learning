#include <stdio.h>

int main(void)
{
    const double PI = 3.1415926;
    int radius = 10;

    // PI = 3.14;           // ❌ 取消注释会编译失败

    double area = PI * radius * radius;
    printf("Area of circle with r=%d is %.2f\n", radius, area);

    return 0;
}