#include <stdio.h>

int main(void) {
    int num;
    printf("Enter numbers (0 to stop):\n");

    while (1) {
        scanf("%d", &num);
        if (num == 0) {
            printf("No negative found.\n");
            break;   // 遇到终止标记，退出循环
        }
        if (num < 0) {
            printf("Found negative: %d\n", num);
            break;   // 找到第一个负数，立即退出
        }
    }
    return 0;
}