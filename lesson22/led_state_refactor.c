/*
 * led_state_refactor.c
 * 第22课 练习一：用 typedef enum 重构 LED 状态机
 *
 * 功能：模拟 LED 在 OFF / ON / BLINK 三种状态间切换。
 *       使用枚举类型替代魔法数字，提高代码可读性。
 */

#include <stdio.h>   // printf, fgets
#include <string.h>  // strlen, strcmp

// ========== 1. 用 typedef enum 定义状态 ==========
// 替代原来的 #define LED_OFF 0 / #define LED_ON 1 / #define LED_BLINK 2
typedef enum {
    LED_OFF,      // 0：熄灭
    LED_ON,       // 1：常亮
    LED_BLINK     // 2：闪烁
} LedState;

// ========== 2. 辅助函数：状态 → 字符串 ==========
/*
 * state_to_string:
 *   将 LedState 枚举值转换为可读的字符串。
 *   参数 state: 当前状态
 *   返回: 指向字符串字面量的只读指针
 */
const char* state_to_string(LedState state)
{
    // switch 配合枚举，编译器会在缺少分支时给出警告（取决于编译选项）
    switch (state) {
        case LED_OFF:    return "OFF";
        case LED_ON:     return "ON";
        case LED_BLINK:  return "BLINK";
        default:         return "UNKNOWN";   // 防御性编程
    }
}

// ========== 3. 状态转移函数 ==========
/*
 * next_state:
 *   根据当前状态返回下一个状态。
 *   转移规则：OFF → ON → BLINK → OFF → ...
 *   参数 current: 当前状态
 *   返回: 下一个状态
 */
LedState next_state(LedState current)
{
    switch (current) {
        case LED_OFF:    return LED_ON;
        case LED_ON:     return LED_BLINK;
        case LED_BLINK:  return LED_OFF;
        default:         return LED_OFF;   // 保险：未知状态回到 OFF
    }
}

// ========== 4. 主函数 ==========
int main(void)
{
    printf("=== LED State Machine (Refactored with enum) ===\n");
    printf("Press ENTER to toggle LED state.\n");
    printf("Type 'q' or 'quit' to exit.\n\n");

    LedState current = LED_OFF;   // 初始状态：熄灭
    int running = 1;               // 控制主循环

    while (running) {
        // 显示当前状态
        printf("[%s] Press ENTER to toggle: ", state_to_string(current));

        // 读取用户输入
        char line[100];
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nEnd of input.\n");
            break;
        }

        // 去掉末尾的换行符
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        // 判断用户输入
        if (len == 0) {
            // 只按了回车：状态前进一次
            current = next_state(current);
        } else if (strcmp(line, "q") == 0 || strcmp(line, "quit") == 0) {
            // 输入退出命令
            printf("Exiting...\n");
            running = 0;
        } else {
            // 无效输入
            printf("  Invalid input. Press ENTER to toggle, or 'q' to quit.\n");
        }
    }

    printf("Goodbye!\n");
    return 0;
}