#include <stdio.h>
#include "temp_manager.h"

int main(void) {
    printf("Temp: %d\n", get_temperature());
    set_temperature(30);
    printf("Temp: %d\n", get_temperature());
    // 以下编译错误：current_temp 被 static 隐藏
    // printf("%d\n", current_temp);
    return 0;
}