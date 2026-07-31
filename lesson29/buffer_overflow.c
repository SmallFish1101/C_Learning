/*
 * buffer_overflow.c
 * 第29课 练习三（选做）：故意制造缓冲区溢出，用 ASan 检测
 *
 * 编译（无检测）: gcc -g -o buffer_overflow buffer_overflow.c
 * 编译（带 ASan）: gcc -fsanitize=address -g -o buffer_overflow_asan buffer_overflow.c
 *
 * 运行: ./buffer_overflow_asan
 * ASan 会在检测到溢出时立即终止程序并打印报告。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 栈缓冲区溢出
void stack_overflow(void)
{
    printf("\n--- Stack buffer overflow ---\n");
    int arr[5] = {0};          // 只有 5 个元素（索引 0~4）

    printf("Attempting to write beyond array bounds...\n");

    // 故意越界写入：arr[5] ~ arr[9] 都不属于 arr
    for (int i = 0; i <= 10; i++) {
        arr[i] = i * 100;      // i=5 时开始越界！
    }

    printf("(If ASan is active, you won't see this line)\n");
}

// 堆缓冲区溢出
void heap_overflow(void)
{
    printf("\n--- Heap buffer overflow ---\n");
    int *buffer = (int *)malloc(5 * sizeof(int));

    printf("Allocated 5 ints (20 bytes) on heap.\n");

    // 正常填充前 5 个元素
    for (int i = 0; i < 5; i++) {
        buffer[i] = i + 1;
    }

    // 故意越界写入
    printf("Writing beyond allocated region...\n");
    buffer[5] = 999;           // 第 6 个元素，越界！
    buffer[10] = 9999;         // 更远的越界！

    printf("(If ASan is active, you won't see this line)\n");

    free(buffer);
}

int main(void)
{
    printf("=== Buffer Overflow Demo ===\n");
    printf("This program intentionally writes beyond array bounds.\n");
    printf("Run without ASan: the errors may go unnoticed.\n");
    printf("Run with ASan:    the errors will be caught immediately.\n");

    stack_overflow();   // 栈溢出
    heap_overflow();    // 堆溢出

    printf("\n=== Program finished (no ASan) ===\n");
    return 0;
}