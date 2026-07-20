/*
 * config.c
 * 内部使用 static 变量存储配置，对外提供 get/set 函数。
 */

#include "config.h"

// static 全局变量：仅本文件可访问
static int max_users = 100;
static int timeout = 30;      // 另一个私有变量

// 实现公开接口
int get_max_users(void) {
    return max_users;
}

void set_max_users(int new_val) {
    // 合法性检查：最大用户数必须在 1~1000 之间
    if (new_val >= 1 && new_val <= 1000) {
        max_users = new_val;
    }
    // 如果超出范围，静默忽略（实际项目可返回错误码）
}

// 可以继续为 timeout 提供类似接口
int get_timeout(void) {
    return timeout;
}

void set_timeout(int new_val) {
    if (new_val >= 0) {
        timeout = new_val;
    }
}