/*
 * trig_macro.c
 * 第21课 练习一：三角函数宏 —— 弧度与角度的转换
 *
 * 演示使用宏定义 PI 和转换宏，注意括号保护。
 */

#include <stdio.h>
#include <math.h>   // sin, cos（用于验证弧度值是否正确）

// 自定义 PI 宏（也可用 math.h 中的 M_PI，但并非所有编译器都定义）
#define PI 3.14159265358979323846

// 弧度转角度：角度 = 弧度 * 180 / PI
// 注意：整个宏及参数都加了括号，防止结合顺序错误
#define RAD2DEG(rad)  ((rad) * 180.0 / PI)

// 角度转弧度：弧度 = 角度 * PI / 180
#define DEG2RAD(deg)  ((deg) * PI / 180.0)

int main(void)
{
    printf("=== Angle Conversion Macros ===\n\n");

    // 用几个常见的角度值进行测试
    double degrees[] = {0.0, 30.0, 45.0, 60.0, 90.0, 180.0, 360.0};
    int num_tests = sizeof(degrees) / sizeof(degrees[0]);

    printf("   Degrees    Radians     sin(rad)    cos(rad)    Reconvert\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < num_tests; i++)
    {
        double deg = degrees[i];
        // 调用宏：角度 -> 弧度
        double rad = DEG2RAD(deg);

        // 用标准库三角函数（需要弧度）进行验证
        double s = sin(rad);
        double c = cos(rad);

        // 再转换回角度，验证宏的正确性
        double reconv = RAD2DEG(rad);

        // 打印结果
        printf("%10.2f°  %10.6f  %10.6f  %10.6f  %10.2f°\n",
               deg, rad, s, c, reconv);
    }

    return 0;
}