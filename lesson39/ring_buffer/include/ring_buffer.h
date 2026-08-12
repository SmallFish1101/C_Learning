/*
 * ring_buffer.h
 * 第39课 环形缓冲区模块 —— 公开接口
 *
 * 设计目标：
 *   - 单生产者-单消费者模式
 *   - 固定容量，写满时拒绝写入（不覆盖旧数据）
 *   - 所有操作 O(1)
 *   - 支持同时读写（无锁）
 *
 * 典型用法（嵌入式 UART 接收中断）：
 *   void ISR_UART_RX(void) {
 *       uint8_t byte = UART->DR;          // 从硬件读取一个字节
 *       ring_buffer_write(&rx_buf, byte);  // 压入缓冲区
 *   }
 *   void main_loop(void) {
 *       uint8_t byte;
 *       if (ring_buffer_read(&rx_buf, &byte)) {
 *           parse_protocol(byte);         // 在主循环中慢速处理
 *       }
 *   }
 */

#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>    // uint8_t
#include <stdbool.h>   // bool, true, false
#include <stddef.h>    // size_t

// ========== 数据结构 ==========

typedef struct {
    uint8_t *buffer;     // 堆上分配的缓冲区
    int      capacity;   // 总容量（字节数）
    int      head;       // 写指针（下一个写入位置的索引）
    int      tail;       // 读指针（下一个读取位置的索引）
    int      count;      // 当前已存储的字节数
} RingBuffer;

// ========== 操作接口 ==========

/*
 * ring_buffer_init:
 *   初始化环形缓冲区（在堆上分配 capacity 字节的内存）。
 *   参数 buf: 未初始化的环形缓冲区结构体指针
 *   参数 capacity: 最大容量（字节数），必须 > 0
 *   返回: true 成功，false 内存不足
 *
 *   注意: 使用完毕后必须调用 ring_buffer_destroy 释放内存。
 */
bool ring_buffer_init(RingBuffer *buf, int capacity);

/*
 * ring_buffer_destroy:
 *   释放环形缓冲区占用的堆内存，并将结构体字段归零。
 *   可安全地重复调用（因 free 后 buffer 被置 NULL）。
 */
void ring_buffer_destroy(RingBuffer *buf);

/*
 * ring_buffer_write:
 *   向缓冲区写入一个字节（生产者操作）。
 *   参数 buf:  缓冲区指针
 *   参数 byte: 要写入的字节
 *   返回: true 写入成功，false 缓冲区已满
 *
 *   在 UART 中断中调用，写入速度快，永不阻塞。
 */
bool ring_buffer_write(RingBuffer *buf, uint8_t byte);

/*
 * ring_buffer_read:
 *   从缓冲区读取一个字节（消费者操作）。
 *   参数 buf:  缓冲区指针
 *   参数 byte: 输出参数，存放读到的字节（仅在返回 true 时有效）
 *   返回: true 读取成功，false 缓冲区为空
 *
 *   在主循环中调用，读取速度慢于写入，但缓冲区吸收速度差。
 */
bool ring_buffer_read(RingBuffer *buf, uint8_t *byte);

/*
 * ring_buffer_peek:
 *   查看队首字节但不移除（与 read 相比，count 和 tail 不变）。
 */
bool ring_buffer_peek(const RingBuffer *buf, uint8_t *byte);

/*
 * ring_buffer_write_bulk:
 *   批量写入多个字节（一次 memcpy，比逐字节循环高效）。
 *   参数 buf:  缓冲区指针
 *   参数 data: 源数据指针
 *   参数 len:  要写入的字节数
 *   返回: 实际写入的字节数（0 表示缓冲区已满或剩余空间不足）
 *
 *   注意: 此操作会处理"可以写多少就写多少"的场景。
 */
int  ring_buffer_write_bulk(RingBuffer *buf, const uint8_t *data, int len);

/*
 * ring_buffer_read_bulk:
 *   批量读取多个字节。
 *   参数 buf:  缓冲区指针
 *   参数 data: 目标数据指针
 *   参数 len:  要读取的最大字节数
 *   返回: 实际读取的字节数（0 表示缓冲区为空）
 */
int  ring_buffer_read_bulk(RingBuffer *buf, uint8_t *data, int len);

/*
 * ring_buffer_count / ring_buffer_free:
 *   返回当前已存储字节数 / 剩余可用字节数。
 *   O(1) 直接返回 count 字段。
 */
int ring_buffer_count(const RingBuffer *buf);
int ring_buffer_free(const RingBuffer *buf);

/*
 * ring_buffer_is_empty / ring_buffer_is_full:
 *   判空 / 判满的便捷函数。
 */
bool ring_buffer_is_empty(const RingBuffer *buf);
bool ring_buffer_is_full(const RingBuffer *buf);

/*
 * ring_buffer_reset:
 *   清空缓冲区（将 head, tail, count 归零，不释放内存）。
 *   等价于"丢弃所有旧数据，重新开始接收"。
 */
void ring_buffer_reset(RingBuffer *buf);

#endif