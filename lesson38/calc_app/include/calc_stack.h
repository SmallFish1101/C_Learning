#ifndef CALC_STACK_H
#define CALC_STACK_H

#include <stdbool.h>

#define STACK_SIZE 256

typedef struct {
    double data[STACK_SIZE];
    int    top;
} CalcStack;

void  stack_init(CalcStack *s);
bool  stack_is_empty(const CalcStack *s);
bool  stack_push(CalcStack *s, double val);
bool  stack_pop(CalcStack *s, double *out);
bool  stack_peek(const CalcStack *s, double *out);

#endif