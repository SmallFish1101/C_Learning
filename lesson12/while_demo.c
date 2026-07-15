#include <stdio.h>

int main(void) {
    int sum = 0, count = 0, num;
    printf("Enter numbers (0 to stop):\n");

    // 先读取第一个数
    scanf("%d", &num);
    while (num != 0) {
        sum += num;
        count++;
        scanf("%d", &num);   // 读取下一个
    }

    if (count > 0)
        printf("Average = %.2f\n", (float)sum / count);
    else
        printf("No data.\n");

    return 0;
}