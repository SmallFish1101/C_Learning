#include <stdio.h>

int generate_id(void) {
    static int next_id = 100;   // 初始值 100，只在程序启动时执行一次
    return next_id++;
}

int main(void) {
    for (int i = 0; i < 5; i++) {
        printf("ID: %d\n", generate_id());
    }
    return 0;
}
// 输出：ID: 100, ID: 101, ID: 102, ID: 103, ID: 104