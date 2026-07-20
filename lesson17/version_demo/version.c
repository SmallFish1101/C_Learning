#include <stdio.h>
int version_major = 1;    // 定义全局变量
int version_minor = 0;    // 另一个全局变量

void print_version(void) {
    printf("v%d.%d\n", version_major, version_minor);
}