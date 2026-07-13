/*
 * led_state_machine.c
 * 第11课 作业二：状态机 LED 控制器
 *
 * 模拟一个 LED 在三种状态间切换：OFF -> ON -> BLINK -> OFF ...
 * 用户每按一次回车，状态前进一次。
 * 输入 'q' 退出。
 */

#include <stdio.h>   // printf, fgets
#include <string.h>  // strlen

// 定义 LED 的三种状态
typedef enum {
    LED_OFF,      // 0：熄灭
    LED_ON,       // 1：常亮
    LED_BLINK     // 2：闪烁
} LedState;

/*
 * state_to_string:
 *   将 LED 状态枚举值转换为可读的字符串。
 *   state: 当前状态。
 *   return: 指向字符串字面量的指针（const char*）。
 */
const char* state_to_string(LedState state)
{
    switch (state) {
        case LED_OFF:    return "OFF";
        case LED_ON:     return "ON";
        case LED_BLINK:  return "BLINK";
        default:         return "UNKNOWN";  // 防御性编程：理论不会执行到这里
    }
}

/*
 * next_state:
 *   根据当前 LED 状态，返回下一个状态。
 *   转移规则：OFF -> ON -> BLINK -> OFF ...
 *   current: 当前状态。
 *   return: 下一个状态。
 */
LedState next_state(LedState current)
{
    switch (current) {
        case LED_OFF:
            return LED_ON;      // 熄灭 → 常亮

        case LED_ON:
            return LED_BLINK;   // 常亮 → 闪烁

        case LED_BLINK:
            return LED_OFF;     // 闪烁 → 熄灭

        default:
            return LED_OFF;     // 未知状态，保险起见回到熄灭
    }
}

int main(void)
{
    printf("=== LED State Machine ===\n");
    printf("Press ENTER to toggle LED state.\n");
    printf("Type 'q' or 'quit' to exit.\n\n");

    LedState current = LED_OFF;   // 初始状态：熄灭
    int running = 1;              // 控制主循环（1=继续，0=退出）

    while (running) {
        // 1. 打印当前状态
        printf("[%s] Press ENTER to toggle: ", state_to_string(current));

        // 2. 读取用户输入（使用 fgets 安全读取）
        char line[100];
        if (fgets(line, sizeof(line), stdin) == NULL) {
            // 遇到 EOF（Ctrl+Z / Ctrl+D），退出
            printf("\nEnd of input.\n");
            break;
        }

        // 3. 去掉 fgets 保留的换行符
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';   // 把换行符替换为字符串结束符
            len--;                   // 长度减 1
        }

        // 4. 判断用户输入
        if (len == 0) {
            // 空行（只按了回车）：状态前进一次
            current = next_state(current);
        } else if (strcmp(line, "q") == 0 || strcmp(line, "quit") == 0) {
            // 输入 'q' 或 'quit'：退出循环
            printf("Exiting...\n");
            running = 0;
        } else {
            // 无效输入：提示并忽略
            printf("  Invalid input. Press ENTER to toggle, or 'q' to quit.\n");
        }
    }

    printf("Goodbye!\n");
    return 0;
}