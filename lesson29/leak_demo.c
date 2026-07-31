#include <stdio.h>
#include <stdlib.h>

void leak_40_bytes(void) {
    int *p = (int *)malloc(10 * sizeof(int));  // 分配 40 字节
    p[0] = 42;
    printf("Allocated and used 40 bytes at %p\n", (void*)p);
    // 忘记 free(p) ← 故意制造内存泄漏
}

int main(void) {
    printf("=== Leak Demo ===\n");
    leak_40_bytes();
    printf("Program exiting...\n");
    return 0;
}