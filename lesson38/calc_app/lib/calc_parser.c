#include<stdio.h>
#include<string.h>
#include<math.h>
#include"calc_parser.h"
#include"calc_stack.h"

bool evaluate_expression(const char *expr, double *result)
{
    CalcStack values, ops;
    stack_init(&values);
    stack_init(&ops);
    if(expr == NULL || strlen(expr) == 0) {
        return false;
    }
    int i = 0;
    while(expr[i] != '\0'){

        if(expr[i] == ' '){ i++; continue;}

        if(isdigit(expr[i]) || expr[i] == '.' ||
            (expr[i] == '-' && (i == 0 || expr[i-1] == '(' ||
                                is_operator(expr[i-1]))))
        {
            char *end = NULL;
            double val = strtod(&expr[i], &end);
            if(end == &expr[i]) return false; // Invalid number
            stack_push(&values, val);
            i = end - expr;   // 跳过整个数字
            continue;
        }

        if (expr[i] == '(')
        {
            stack_push(&ops, (double)'(');
            i++;
            continue;
        }

         // ===== 情况3：遇到 ')' =====
        if (expr[i] == ')')
        {
            // TODO: 实现此分支
            // 不断弹出 ops 直到遇到 '('
            // 对每次弹出来的运算符，pop 两个操作数并计算，把结果 push 回 values
            // 如果 ops 为空还没遇到 '('，说明括号不匹配，返回 false
            // 弹出 '(' 丢弃
            i++;
            continue;
        }

        // ===== 情况4：遇到运算符 =====
        if (is_operator(expr[i]) && !(expr[i] == '-' &&
            (i == 0 || expr[i-1] == '(' || is_operator(expr[i-1]))))
        {
            // TODO: 实现此分支
            // 只要 ops 栈不为空且栈顶运算符优先级 >= 当前运算符优先级
            //   就弹出栈顶运算符，弹出两个操作数，计算结果并 push 回 values
            // 最后把当前运算符 push 到 ops
            i++;
            continue;
        }

        // 未知字符
        return false;
    }
    // ===== 遍历结束：弹出 ops 中所有剩余运算符 =====
    // TODO: 实现此循环
    // 不断弹出 ops 的栈顶运算符，弹出两个操作数，计算后 push 回 values
    // 如果 ops 在遇到 '(' 时没被正确弹出，说明有未闭合的括号
    // ===== 最终结果 =====
    // values 栈顶应该只剩一个元素——最终结果
    if (stack_pop(&values, result))
        return true;
    return false;
}