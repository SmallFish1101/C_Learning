#include <stdio.h>

// 符号常量
#define PASSING_GRADE 60
#define GOOD_PERFORMANCE_THRESHOLD 4
#define BLINK_DELAY_COUNT 100000
#define BLINK_COUNT 10

// LED 状态
#define LED_OFF 0
#define LED_ON  1

int main(void) {
    int scores[] = {78, 92, 55, 61, 88, 45};
    int num_students = sizeof(scores) / sizeof(scores[0]);  // 顺便把 6 也换成计算方式
    int pass_count = 0;

    for (int i = 0; i < num_students; i++) {
        if (scores[i] >= PASSING_GRADE) {
            pass_count++;
        }
    }

    printf("Passed: %d / %d\n", pass_count, num_students);

    if (pass_count > GOOD_PERFORMANCE_THRESHOLD) {
        printf("Class performance is good.\n");
    }

    int led_state = LED_OFF;
    for (int blink = 0; blink < BLINK_COUNT; blink++) {
        led_state = (led_state == LED_OFF) ? LED_ON : LED_OFF;  // 或直接用 ! 但用显式切换更清晰
        for (volatile int d = 0; d < BLINK_DELAY_COUNT; d++);
    }

    printf("Final LED state: %s\n", (led_state == LED_ON) ? "ON" : "OFF");
    return 0;
}