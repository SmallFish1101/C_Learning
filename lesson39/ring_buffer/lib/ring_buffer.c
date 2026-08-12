/*
 * ring_buffer.c
 * 环形缓冲区模块 —— 具体实现。
 *
 * 核心操作：每次写/读一个字节，并使用取模运算使指针绕回。
 * 批量操作使用 memcpy 加速。
 * 所有函数均 O(1)，无循环，无阻塞。
 */

#include "ring_buffer.h"
#include <stdlib.h>    // malloc, free
#include <string.h>    // memcpy

// ========== 初始化与销毁 ==========

bool ring_buffer_init(RingBuffer *buf, int capacity)
{
    if (buf == NULL || capacity <= 0) return false;

    buf->buffer = (uint8_t *)malloc(capacity * sizeof(uint8_t));
    if (buf->buffer == NULL) return false;

    buf->capacity = capacity;
    buf->head     = 0;
    buf->tail     = 0;
    buf->count    = 0;

    return true;
}

void ring_buffer_destroy(RingBuffer *buf)
{
    if (buf == NULL) return;

    free(buf->buffer);
    buf->buffer   = NULL;   // 防止悬空指针
    buf->capacity = 0;
    buf->head     = 0;
    buf->tail     = 0;
    buf->count    = 0;
}

// ========== 单字节读写 ==========

bool ring_buffer_write(RingBuffer *buf, uint8_t byte)
{
    if (buf == NULL || buf->buffer == NULL) return false;
    if (ring_buffer_is_full(buf)) return false;   // 拒绝覆盖旧数据

    buf->buffer[buf->head] = byte;
    buf->head = (buf->head + 1) % buf->capacity;   // ★ 取模实现"绕回"
    buf->count++;

    return true;
}

bool ring_buffer_read(RingBuffer *buf, uint8_t *byte)
{
    if (buf == NULL || buf->buffer == NULL || byte == NULL) return false;
    if (ring_buffer_is_empty(buf)) return false;

    *byte = buf->buffer[buf->tail];
    buf->tail = (buf->tail + 1) % buf->capacity;   // ★ 取模实现"绕回"
    buf->count--;

    return true;
}

bool ring_buffer_peek(const RingBuffer *buf, uint8_t *byte)
{
    if (buf == NULL || buf->buffer == NULL || byte == NULL) return false;
    if (ring_buffer_is_empty(buf)) return false;

    *byte = buf->buffer[buf->tail];
    return true;   // count 和 tail 不变
}

// ========== 批量读写 ==========

int ring_buffer_write_bulk(RingBuffer *buf, const uint8_t *data, int len)
{
    if (buf == NULL || data == NULL || len <= 0) return 0;

    int free = ring_buffer_free(buf);
    if (free == 0) return 0;

    int to_write = (len < free) ? len : free;   // 能写多少写多少

    // 需要处理"绕回"的情况——数据可能分成两段写入
    int first_part = buf->capacity - buf->head;
    if (to_write <= first_part) {
        // 不需要绕回：一次 memcpy
        memcpy(&buf->buffer[buf->head], data, to_write);
    } else {
        // 需要绕回：先写到数组末尾，再绕回数组开头
        memcpy(&buf->buffer[buf->head], data, first_part);
        memcpy(&buf->buffer[0], data + first_part, to_write - first_part);
    }

    buf->head = (buf->head + to_write) % buf->capacity;
    buf->count += to_write;

    return to_write;
}

int ring_buffer_read_bulk(RingBuffer *buf, uint8_t *data, int len)
{
    if (buf == NULL || data == NULL || len <= 0) return 0;

    int avail = buf->count;
    if (avail == 0) return 0;

    int to_read = (len < avail) ? len : avail;

    int first_part = buf->capacity - buf->tail;
    if (to_read <= first_part) {
        memcpy(data, &buf->buffer[buf->tail], to_read);
    } else {
        memcpy(data, &buf->buffer[buf->tail], first_part);
        memcpy(data + first_part, &buf->buffer[0], to_read - first_part);
    }

    buf->tail = (buf->tail + to_read) % buf->capacity;
    buf->count -= to_read;

    return to_read;
}

// ========== 状态查询 ==========

int ring_buffer_count(const RingBuffer *buf)
{
    return (buf != NULL) ? buf->count : 0;
}

int ring_buffer_free(const RingBuffer *buf)
{
    return (buf != NULL) ? (buf->capacity - buf->count) : 0;
}

bool ring_buffer_is_empty(const RingBuffer *buf)
{
    return (buf != NULL) && (buf->count == 0);
}

bool ring_buffer_is_full(const RingBuffer *buf)
{
    return (buf != NULL) && (buf->count == buf->capacity);
}

void ring_buffer_reset(RingBuffer *buf)
{
    if (buf == NULL) return;
    buf->head  = 0;
    buf->tail  = 0;
    buf->count = 0;
    // 不释放 buffer，也不清零其内容——旧数据在下一次写入时被覆盖
}