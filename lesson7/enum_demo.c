#include <stdio.h>
#include <stdbool.h>

// 枚举定义LED状态
typedef enum {
    LED_OFF,
    LED_ON,
    LED_BLINKING
} LedState;

int main(void)
{
    LedState state = LED_BLINKING;
    bool high_brightness = true;    // 现代C的布尔类型

    printf("LED state: ");
    switch (state) {
        case LED_OFF: printf("OFF\n"); break;
        case LED_ON:  printf("ON\n");  break;
        case LED_BLINKING: printf("BLINKING\n"); break;
        default: printf("UNKNOWN\n");
    }

    printf("High brightness: %s\n", high_brightness ? "true" : "false");

    // 枚举值也是整数
    printf("LED_ON = %d, LED_BLINKING = %d\n", LED_ON, LED_BLINKING);

    return 0;
}