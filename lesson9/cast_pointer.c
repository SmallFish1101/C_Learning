#include <stdio.h>
#include <stdint.h>

// 模拟硬件寄存器地址
#define TIMER_BASE 0x40000000
// 定义一个指针指向该地址，强制转换为指向 32 位寄存器的 volatile 指针
#define TIMER_CR   (*(volatile uint32_t *) (TIMER_BASE + 0x00))

int main(void)
{
    uint32_t *timer_ptr = (uint32_t *) TIMER_BASE; // 普通指针，用于演示
    // 实际硬件中不能随便写，这里仅演示语法
    printf("Timer base address: %p\n", (void*)timer_ptr);

    // 强制转换的应用：将 void* 转为具体类型指针（在动态内存部分会用到）
    int value = 42;
    void *vp = &value;
    int *ip = (int *) vp;
    printf("Value via cast: %d\n", *ip);

    return 0;
}