/*
 * logger.h
 * 第21课 练习三：日志模块的公开接口
 *
 * 使用条件编译，根据编译时宏 LOG_LEVEL 的值决定哪些级别的日志被保留。
 *
 * 日志级别定义：
 *   LOG_LEVEL_ERROR (1) —— 只输出错误
 *   LOG_LEVEL_WARN  (2) —— 输出错误和警告
 *   LOG_LEVEL_INFO  (3) —— 输出所有日志（错误、警告、信息）
 *
 * 若未定义 LOG_LEVEL，默认定义为 3（全部输出）。
 *
 * 用法：
 *   LOG_ERROR("Failed to open file: %s", filename);
 *   LOG_WARN("Temperature %d exceeds limit", temp);
 *   LOG_INFO("System started.");
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>   // printf

// ========== 日志级别宏（数值定义）==========
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_WARN  2
#define LOG_LEVEL_INFO  3

// ========== 若未定义 LOG_LEVEL，则默认为 INFO（全部输出）==========
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_INFO
#endif

// ========== 根据 LOG_LEVEL 条件编译来定义各日志宏 ==========

// ---------- LOG_ERROR : 级别 >= 1 ----------
#if LOG_LEVEL >= LOG_LEVEL_ERROR
    #define LOG_ERROR(fmt, ...) \
        do { \
            printf("[ERROR] %s:%d: " fmt "\n", \
                   __FILE__, __LINE__, ##__VA_ARGS__); \
        } while(0)
#else
    #define LOG_ERROR(fmt, ...)   // 空宏，代码被完全移除
#endif

// ---------- LOG_WARN : 级别 >= 2 ----------
#if LOG_LEVEL >= LOG_LEVEL_WARN
    #define LOG_WARN(fmt, ...) \
        do { \
            printf("[WARN]  %s:%d: " fmt "\n", \
                   __FILE__, __LINE__, ##__VA_ARGS__); \
        } while(0)
#else
    #define LOG_WARN(fmt, ...)
#endif

// ---------- LOG_INFO : 级别 >= 3 ----------
#if LOG_LEVEL >= LOG_LEVEL_INFO
    #define LOG_INFO(fmt, ...) \
        do { \
            printf("[INFO]  %s:%d: " fmt "\n", \
                   __FILE__, __LINE__, ##__VA_ARGS__); \
        } while(0)
#else
    #define LOG_INFO(fmt, ...)
#endif

#endif  // LOGGER_H