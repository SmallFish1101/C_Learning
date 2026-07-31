#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *p = (int *)malloc(sizeof(int));
    *p = 100;
    printf("Before free: *p = %d\n", *p);

    free(p);
    printf("Memory freed.\n");

    // 悬空指针访问：Use-After-Free
    printf("After free: *p = %d\n", *p);   // ← 未定义行为！
    *p = 200;                               // ← 向已释放的内存写入，更危险！

    return 0;
}