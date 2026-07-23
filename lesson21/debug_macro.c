#include <stdio.h>

// 若需要调试，取消下面注释；否则定义空宏
// #define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
    #define DBG(fmt, ...) printf("DBG [%s:%d]: " fmt "\n", \
                                 __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define DBG(fmt, ...)   // 空
#endif

int main(void) {
    int a = 10;
    DBG("a = %d", a);
    printf("Normal output\n");
    return 0;
}