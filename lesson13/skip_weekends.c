#include <stdio.h>

int main(void) {
    for (int day = 1; day <= 7; day++) {
        if (day == 6 || day == 7) {
            printf("Day %d: Weekend, skip\n", day);
            continue;   // 跳过工作日操作
        }
        printf("Day %d: Work\n", day);
    }
    return 0;
}