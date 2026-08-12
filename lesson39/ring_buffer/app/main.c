/*
 * main.c
 * 环形缓冲区测试程序 —— 模拟 UART 中断接收 + 主循环处理
 *
 * 场景：
 *   - 生产者（模拟 ISR）：每 100ms 产生 3 个字节，写入环形缓冲区
 *   - 消费者（模拟主循环）：每 1 秒读取一次缓冲区中的所有数据
 *   - 观察缓冲区在"满"和"空"之间的变化
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   // sleep() (Linux) 或替换为 Sleep() (Windows)
#include "../include/ring_buffer.h"

int main(void)
{
    printf("=== Ring Buffer Demo: UART RX Simulation ===\n\n");

    // 初始化一个容量为 16 字节的接收缓冲区（故意设小，便于观察满/空状态）
    RingBuffer rx_buf;
    if (!ring_buffer_init(&rx_buf, 16)) {
        printf("Failed to initialize ring buffer.\n");
        return 1;
    }

    int tick = 0;   // 模拟时钟计数器

    while (1)
    {
        tick++;

        // ---- 生产者：每轮写入 3 个字节（模拟 UART 中断） ----
        // 生成可预测的数据：本例中直接使用 tick 的低 8 位
        for (int i = 0; i < 3; i++) {
            uint8_t byte = (uint8_t)((tick * 3 + i) & 0xFF);
            if (!ring_buffer_write(&rx_buf, byte)) {
                printf("  [OVERFLOW] Buffer full! Dropping byte 0x%02X\n",
                       byte);
            }
        }

        // ---- 消费者：每 3 轮读取一次（模拟主循环处理较慢） ----
        if (tick % 3 == 0) {
            uint8_t buf_out[32] = {0};
            int n = ring_buffer_read_bulk(&rx_buf, buf_out, sizeof(buf_out));

            if (n > 0) {
                printf("[tick %2d] Read %2d byte(s): ", tick, n);
                for (int i = 0; i < n; i++) {
                    printf("0x%02X ", buf_out[i]);
                }
                printf("\n");
            } else {
                printf("[tick %2d] Buffer empty.\n", tick);
            }
        }

        // ---- 状态输出 ----
        printf("         (used: %2d/%2d)\n",
               ring_buffer_count(&rx_buf),
               rx_buf.capacity);

        // ---- 退出条件 ----
        if (tick >= 12) {
            printf("\n  Simulation complete.\n");
            break;
        }

        // 在真实硬件上，这里是两个独立的中断/循环并行运行；
        // 在模拟程序中，我们用单线程串行模拟，但算法逻辑完全一致。
#ifdef _WIN32
        Sleep(500);
#else
        usleep(500000);   // 0.5 秒
#endif
    }

    ring_buffer_destroy(&rx_buf);
    return 0;
}