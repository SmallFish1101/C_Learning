#include <stdio.h>
extern int version_major;   // 声明外部变量
void print_version(void);   // 函数原型

int main(void) {
    print_version();
    printf("Major version from main: %d\n", version_major);
    return 0;
}