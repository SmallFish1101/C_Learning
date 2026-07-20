/*
 * config.h
 * 提供配置模块的公开接口。
 */

#ifndef CONFIG_H
#define CONFIG_H

// 获取最大用户数
int get_max_users(void);

// 设置最大用户数
void set_max_users(int new_val);

int get_timeout(void);      // 新增：声明 get_timeout
void set_timeout(int new_val);  // 新增：声明 set_timeout

#endif