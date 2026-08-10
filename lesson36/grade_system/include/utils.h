/*
 * utils.h
 * 第34课 练习一：通用工具函数库 —— 公开接口
 *
 * 提供安全输入、数据校验、随机数等常用功能。
 * 所有函数均不依赖其他自定义模块，仅依赖 C 标准库。
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>    // printf, fgets, sscanf
#include <stdlib.h>   // exit, rand
#include <string.h>   // strlen, strspn
#include <stdbool.h>  // bool, true, false

// ========== 安全输入 ==========

/*
 * safe_read_line:
 *   从标准输入安全读取一行，去掉末尾换行符。
 *   参数 buffer: 存放结果的字符数组
 *   参数 size  : 数组最大容量
 *   返回: 实际读取的字符数（不含 '\0'）；EOF 时调用 exit
 */
int safe_read_line(char *buffer, int size);

/*
 * read_int:
 *   安全读取一个整数（带提示和重试机制）。
 *   参数 prompt: 提示信息（如 "Enter age: "）
 *   返回: 用户输入的合法整数
 */
int read_int(const char *prompt);

/*
 * read_double:
 *   安全读取一个浮点数（带提示和重试机制）。
 *   参数 prompt: 提示信息
 *   返回: 用户输入的合法浮点数
 */
double read_double(const char *prompt);

// ========== 数据校验 ==========

/*
 * is_valid_name:
 *   校验姓名是否合法：非空，且不超过 max_len 个字符。
 *   参数 name   : 待校验的姓名字符串
 *   参数 max_len: 允许的最大字符数
 *   返回: true 合法，false 非法（并自动打印错误信息）
 */
bool is_valid_name(const char *name, int max_len);

/*
 * is_valid_phone:
 *   校验电话是否合法：非空，且只含数字和连字符 '-'。
 *   参数 phone: 待校验的电话字符串
 *   返回: true 合法，false 非法（并自动打印错误信息）
 */
bool is_valid_phone(const char *phone);

/*
 * is_valid_age:
 *   校验年龄字符串是否合法：整数，范围 1~150，无多余字符。
 *   参数 age_str: 待校验的年龄字符串
 *   参数 age_out: 输出参数，存放解析后的年龄（仅在合法时有效）
 *   返回: true 合法，false 非法（并自动打印错误信息）
 */
bool is_valid_age(const char *age_str, int *age_out);

// ========== 随机数 ==========

/*
 * random_range:
 *   生成 [min, max] 区间内的伪随机整数。
 *   参数 min: 最小值（包含）
 *   参数 max: 最大值（包含）
 *   返回: 区间内的随机整数
 *
 *   注意: 调用前需在 main 中调用 srand((unsigned)time(NULL)) 设置种子。
 */
int random_range(int min, int max);

#endif