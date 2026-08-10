#ifndef CALC_PARSER_H
#define CALC_PARSER_H

#include <stdbool.h>

// 将一个中缀表达式字符串求值为 double 结果
// 成功返回 true，结果写入 *result
// 失败返回 false（语法错误、除零、括号不匹配等）
bool evaluate_expression(const char *expr, double *result);

#endif