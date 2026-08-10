#include"calc_stack.h"


void stack_init(CalcStack *s) { s->top = -1; }
bool stack_is_empty(const CalcStack *s) { return s->top == -1; }
bool stack_is_full(const CalcStack *s) { return s->top == STACK_SIZE - 1; }

bool stack_push(CalcStack *s, double val) {
    if (stack_is_full(s)) return false;
    s->data[++(s->top)] = val;
    return true;
}

bool stack_pop(CalcStack *s, double *out) {
    if (stack_is_empty(s)) return false;
    *out = s->data[(s->top)--];
    return true;
}

bool stack_peek(const CalcStack *s, double *out) {
    if (stack_is_empty(s)) return false;
    *out = s->data[s->top];
    return true;
}