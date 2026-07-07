#include <stdio.h>
// 宏常量（注意：宏名通常全大写，单词间用下划线）
#define SENSOR_MAX 150
#define SENSOR_MIN (-40)

int main(void)
{
    int temp_values[] = {20, -15, 80, 160, -50, 0};

    for (int i = 0; i < 6; i++)
    {
        int t = temp_values[i];
        printf("Temp = %d: ", t);
        if (t > SENSOR_MAX || t < SENSOR_MIN)
            printf("OUT OF RANGE!\n");
        else
            printf("OK\n");
    }
    return 0;
}