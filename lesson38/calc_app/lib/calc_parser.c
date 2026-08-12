#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#include"calc_parser.h"
#include"calc_stack.h"

// -- 内部常量与辅助函数 --
static bool is_operator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}
static int precedence(char op)
{
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': case '%': return 2;
        default: return 0;   // '(' 的优先级最低
    }
}


bool evaluate_expression(const char *expr, double *result)
{  
    CalcStack values, ops;
    stack_init(&values);
    stack_init(&ops);
    if(expr == NULL || strlen(expr) == 0) 
    {
        return false;
    }

    int i = 0;
    while(expr[i] != '\0')
    {

        if(expr[i] == ' '){ i++; continue;}

        if(isdigit(expr[i]) || expr[i] == '.' ||(expr[i] == '-' && (i == 0 || expr[i-1] == '(' ||is_operator(expr[i-1]))))
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
        // TODO: 实现此分支
        // 不断弹出 ops 直到遇到 '('
        // 对每次弹出来的运算符，pop 两个操作数并计算，把结果 push 回 values
        // 如果 ops 为空还没遇到 '('，说明括号不匹配，返回 false
        // 弹出 '(' 丢弃
        if (expr[i] == ')')
        {

            while(!stack_is_empty(&ops)) 
            {
                // 偷看栈顶，如果是 '(' 就停下
                double op_val;
                stack_peek(&ops, &op_val);
                if ((char)op_val == '(') 
                {
                    stack_pop(&ops, &op_val);   // 弹出 '(' 并丢弃
                    break;
                }
                
                stack_pop(&ops, &op_val);              
                double num1=0, num2=0;
                if(!stack_pop(&values, &num2) || !stack_pop(&values, &num1))
                {
                    return false;
                }
                
                double res=0;
                switch((char)op_val) {
                    case '+': res =num1 +num2; break;
                    case '-': res =num1 -num2; break;
                    case '*': res =num1 *num2; break;
                    case '/':
                        if(num2==0)
                            return false;
                        res =num1 /num2; break;
                    case '%':
                        if(num2==0)return false;
                        res =fmod(num1,num2); break;
                    default: return false;
                }
                stack_push(&values, res);

            }
            i++;
            continue;
        }

        // ===== 情况4：遇到运算符 =====
        // TODO: 实现此分支
        // 只要 ops 栈不为空且栈顶运算符优先级 >= 当前运算符优先级
        //   就弹出栈顶运算符，弹出两个操作数，计算结果并 push 回 values
        // 最后把当前运算符 push 到 ops
        // 前面判断负号的逻辑保持不变
        if(is_operator(expr[i]) && !(expr[i] == '-' && (i == 0 || expr[i-1] == '(' || is_operator(expr[i-1]))))
        {
        
            // 只要 ops 栈顶的运算符优先级 >= 当前运算符，就先把栈顶的算掉
            while (!stack_is_empty(&ops)) 
            {
                double top_op;
                stack_peek(&ops, &top_op);
                if (precedence((char)top_op) < precedence(expr[i]))
                    break;   // 栈顶优先级更低，停止弹出
                    stack_pop(&ops, &top_op);   // 弹出高优先级运算符            
                    double num2 = 0, num1 = 0;
                    if (!stack_pop(&values, &num2) || !stack_pop(&values, &num1))return false;
                    
                    double res = 0;
                    switch ((char)top_op) {
                    case '+': res = num1 + num2; break;
                    case '-': res = num1 - num2; break;   // ★ 统一用 num1 - num2
                    case '*': res = num1 * num2; break;
                    case '/':
                        if (num2 == 0.0) return false;
                        res = num1 / num2;
                        break;
                    default: return false;
                    
                }
            stack_push(&values, res);
            }
        }
        // ★ 所有高优先级运算符都弹出后，再把当前运算符压入 ops
        stack_push(&ops, (double)expr[i]);
        i++;
        continue;
    }
    
    // ===== 遍历结束：弹出 ops 中所有剩余运算符 =====
    // TODO: 实现此循环
    // 不断弹出 ops 的栈顶运算符，弹出两个操作数，计算后 push 回 values
    // 如果 ops 在遇到 '(' 时没被正确弹出，说明有未闭合的括号
    // ===== 最终结果 =====
    // values 栈顶应该只剩一个元素——最终结果
    if(expr[i] == '\0')
    {

        while(!stack_is_empty(&ops)) 
        {
            double op;
            stack_pop(&ops, &op);
            if((char)op == '(') return false; // 未闭合的括号
            
            double num1=0, num2=0;
            if(!stack_pop(&values, &num2) || !stack_pop(&values, &num1))
            
            return false;

            switch((char)op)
            {
                case '+': stack_push(&values, num1 + num2); break;
                case '-': stack_push(&values, num1 - num2); break;
                case '*': stack_push(&values, num1 * num2); break;
                case '/':
                    if(num2 == 0) return false;
                    stack_push(&values, num1 / num2); break;
                case '%':
                    if(num2 == 0) return false;
                    
                    stack_push(&values, fmod(num1, num2)); break;
                default: return false;
            }
        }

    }

    if (stack_pop(&values, result))return true;
    
    return false;
}