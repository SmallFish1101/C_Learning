#include "temp_manager.h"

static int current_temp = 25;   // 只能在本文件内访问

void set_temperature(int temp) {
    if (temp >= -40 && temp <= 85)
        current_temp = temp;
}

int get_temperature(void) {
    return current_temp;
}