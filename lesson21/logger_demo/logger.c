/*
 * logger.c
 * 日志模块的内部实现（本示例中仅提供时间戳辅助函数，可选）。
 *
 * 所有日志输出的条件编译逻辑在 logger.h 中完成。
 */

#include "logger.h"
#include <time.h>     // time, localtime, strftime

/*
 * get_timestamp:
 *   获取当前时间的字符串表示，格式为 "HH:MM:SS"。
 *   buffer: 输出缓冲区，至少 9 字节。
 *   返回: buffer 的指针（方便在 printf 中使用）。
 *
 * 这是一个普通函数，与日志级别无关，任何级别都可能调用它。
 */
const char *get_timestamp(char *buffer, size_t size)
{
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%H:%M:%S", tm_info);
    return buffer;
}