#include <stdio.h>

typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_ERROR
} State;

const char *state_name(State s) {
    switch (s) {
        case STATE_IDLE:    return "IDLE";
        case STATE_RUNNING: return "RUNNING";
        case STATE_ERROR:   return "ERROR";
        default:            return "UNKNOWN";
    }
}

int main(void) {
    State current = STATE_IDLE;

    // 模拟状态转换
    printf("Current: %s\n", state_name(current));
    current = STATE_RUNNING;
    printf("Current: %s\n", state_name(current));
    // 检测到错误
    current = STATE_ERROR;
    printf("Current: %s\n", state_name(current));

    return 0;
}