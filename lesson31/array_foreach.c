/*
 * array_foreach.c
 * 第31课 练习二：带回调的数组遍历函数
 *
 * 功能：实现通用的数组遍历框架 array_foreach，
 *       通过传入不同的回调函数，实现打印或求和等操作。
 *       展示回调函数"分离遍历逻辑与处理逻辑"的核心价值。
 */

#include <stdio.h>   // printf

// ========== 1. 定义回调函数类型 ==========
/*
 * ElementFunc:
 *   指向 "接受索引和值，无返回值" 的函数的指针类型。
 *   任何符合 (int index, int value) 签名的函数都可以赋给此类型。
 */
typedef void (*ElementFunc)(int index, int value);

// ========== 2. 全局变量（用于 sum_element 累加）==========
/*
 * g_sum:
 *   全局累加变量。sum_element 回调会将每个元素的值累加到这里。
 *   局限性分析（见 main 函数末尾注释）。
 */
static int g_sum = 0;

// ========== 3. 遍历框架：array_foreach ==========
/*
 * array_foreach:
 *   遍历数组的每个元素，对每个元素调用回调函数 fn。
 *
 *   参数 arr: 数组首地址
 *   参数 n  : 数组元素个数
 *   参数 fn : 回调函数指针（ElementFunc 类型）
 *             每次调用 fn 时，传入当前元素的索引和值。
 *
 *   此函数是"框架"——它不关心 fn 具体做什么（打印/求和/写文件），
 *   只负责"遍历 + 传参"。这是回调模式的最大优势。
 */
void array_foreach(int *arr, int n, ElementFunc fn)
{
    // 如果回调为空，直接返回（防御性编程）
    if (fn == NULL) {
        return;
    }

    for (int i = 0; i < n; i++) {
        // ★ 核心：通过函数指针调用回调，传入索引和值
        fn(i, arr[i]);
    }
}

// ========== 4. 具体回调函数 ==========

/*
 * print_element:
 *   回调函数：打印当前元素的索引和值。
 *   用法: array_foreach(arr, n, print_element);
 */
void print_element(int index, int value)
{
    printf("  arr[%d] = %d\n", index, value);
}

/*
 * sum_element:
 *   回调函数：将当前元素的值累加到全局变量 g_sum。
 *   用法:
 *     g_sum = 0;
 *     array_foreach(arr, n, sum_element);
 *     printf("Sum = %d\n", g_sum);
 *
 *   注意：此回调依赖全局变量 g_sum 传递结果。
 *         更通用的做法是用 void *user_data 参数（见文末分析）。
 */
void sum_element(int index, int value)
{
    // 这里故意忽略 index 参数（只用 value），这也是回调的常见情况
    // 编译器可能给出 "unused parameter" 警告，属正常现象
    (void)index;       // 显式标记"不使用此参数"，消除编译警告

    g_sum += value;    // 累加当前元素的值
}

// ========== 5. 主函数 ==========
int main(void)
{
    printf("=== Array Foreach with Callbacks ===\n\n");

    // 测试数据
    int data[] = {10, 25, 37, 42, 58};
    int n = sizeof(data) / sizeof(data[0]);

    // ---- 测试 1：用 print_element 回调打印数组 ----
    printf("Test 1: Print all elements via callback\n");
    array_foreach(data, n, print_element);

    // ---- 测试 2：用 sum_element 回调计算总和 ----
    printf("\nTest 2: Calculate sum via callback\n");

    g_sum = 0;   // ★ 重置全局累加器（非常重要！）
    array_foreach(data, n, sum_element);
    printf("  Sum of all elements = %d\n", g_sum);

    // ---- 测试 3：用同一个数组展示两种回调的独立性 ----
    printf("\nTest 3: Two callbacks, same framework\n");

    int squares[] = {1, 4, 9, 16, 25};
    n = sizeof(squares) / sizeof(squares[0]);

    printf("  Squares array:\n");
    array_foreach(squares, n, print_element);

    g_sum = 0;
    array_foreach(squares, n, sum_element);
    printf("  Sum of squares = %d\n", g_sum);

    /*
     * ========== 关于全局变量的局限性 ==========
     *
     * 本练习中，sum_element 通过全局变量 g_sum 传递累加结果。
     * 这种方法有一个明显的缺陷：
     *   - 如果你同时需要计算两个不同数组的和，全局变量就"不够用"了。
     *   - 全局变量可以被任何函数修改，容易引发难以追踪的 Bug。
     *
     * 更通用的做法是通过一个 void *user_data 参数向回调传递上下文：
     *
     *   typedef void (*ElementFuncEx)(int index, int value, void *user_data);
     *
     *   这样你可以把任何数据（如一个结构体指针）传给回调，
     *   回调内部通过强制类型转换拿到它需要的上下文（累加器、文件指针等）。
     *
     *   qsort 和 bsearch 的比较函数通过 void * 基类指针来间接操作不同类型的
     *   数据，本质上也是类似的思路。
     *
     *   第28课的动态数组模块中，如果你想把数组的"所有元素加倍"或"写入文件"，
     *   也可以用这种带 user_data 的回调模式来实现。
     */

    return 0;
}