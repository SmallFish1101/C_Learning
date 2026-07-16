/*
 * prime_finder.c
 * 第13课 练习一：素数寻找器
 *
 * 功能：打印 2~100 之间的所有素数。
 *       内层循环使用 break 提前退出，提高效率。
 */

#include <stdio.h>

int main(void)
{
    printf("Prime numbers between 2 and 100:\n");

    // 外层循环：遍历 2~100 的每一个整数
    for (int num = 2; num <= 100; num++)
    {
        int is_prime = 1;   // 假设 num 是素数

        // 内层循环：检查 num 是否能被某个数整除
        // divisor 从 2 开始，到 sqrt(num) 为止（用 divisor*divisor <= num 表示）
        for (int divisor = 2; divisor * divisor <= num; divisor++)
        {
            // 如果 num 能被 divisor 整除，说明不是素数
            if (num % divisor == 0)
            {
                is_prime = 0;   // 标记为非素数
                break;          // 已经找到因子，无需继续检查更大的 divisor
            }
        }

        // 内层循环结束后，如果 is_prime 仍为 1，说明 num 没有任何因子
        if (is_prime)
        {
            printf("%d ", num);
        }
    }

    printf("\n");
    return 0;
}