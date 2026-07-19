#include <stdio.h>
#include <stdbool.h>   // bool, true, false

// 函数原型
bool is_prime(int n);

int main(void) {
    int num;
    printf("Enter a positive integer: ");
    scanf("%d", &num);   // 为了简洁使用 scanf，实际项目请用安全输入

    if (is_prime(num)) {
        printf("%d is a prime number.\n", num);
    } else {
        printf("%d is not a prime number.\n", num);
    }
    return 0;
}

// 函数定义：判断是否为素数
bool is_prime(int n) {
    if (n <= 1) return false;   // 1 和负数都不是素数
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;       // 找到因子，不是素数
        }
    }
    return true;                // 没有因子，是素数
}