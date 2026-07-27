/*
 * layout_analysis.c
 * 第25课 练习一：结构体内存布局分析
 *
 * 功能：对比三种结构体定义的实际内存占用和成员偏移，
 *       验证内存对齐规则与 __attribute__((packed)) 的效果。
 */

#include <stdio.h>    // printf
#include <stddef.h>   // offsetof

// ========== 三种结构体定义 ==========

/* 未优化顺序：两个 char 中间夹 double，会产生大量填充 */
typedef struct {
    char   a;       // 1 字节
    double b;       // 8 字节
    char   c;       // 1 字节
} LayoutA;

/* 优化顺序：大成员放前面，小成员挤在一起 */
typedef struct {
    double b;       // 8 字节
    char   a;       // 1 字节
    char   c;       // 1 字节
} LayoutB;

/* 强制紧凑：取消所有对齐填充 */
typedef struct __attribute__((packed)) {
    char   a;       // 1 字节
    double b;       // 8 字节
    char   c;       // 1 字节
} LayoutC;

int main(void)
{
    printf("=== Structure Layout Analysis ===\n\n");

    // ===== LayoutA：未优化顺序 =====
    printf("LayoutA (char, double, char):\n");
    printf("  sizeof  = %2zu bytes\n", sizeof(LayoutA));
    printf("  offset of a: %2zu\n", offsetof(LayoutA, a));
    printf("  offset of b: %2zu\n", offsetof(LayoutA, b));
    printf("  offset of c: %2zu\n", offsetof(LayoutA, c));
    printf("  (wasted on padding: %zu bytes)\n\n",
           sizeof(LayoutA) - (sizeof(char) + sizeof(double) + sizeof(char)));

    // ===== LayoutB：优化顺序 =====
    printf("LayoutB (double, char, char):\n");
    printf("  sizeof  = %2zu bytes\n", sizeof(LayoutB));
    printf("  offset of b: %2zu\n", offsetof(LayoutB, b));
    printf("  offset of a: %2zu\n", offsetof(LayoutB, a));
    printf("  offset of c: %2zu\n", offsetof(LayoutB, c));
    printf("  (wasted on padding: %zu bytes)\n\n",
           sizeof(LayoutB) - (sizeof(double) + sizeof(char) + sizeof(char)));

    // ===== LayoutC：强制紧凑 =====
    printf("LayoutC (packed):\n");
    printf("  sizeof  = %2zu bytes\n", sizeof(LayoutC));
    printf("  offset of a: %2zu\n", offsetof(LayoutC, a));
    printf("  offset of b: %2zu\n", offsetof(LayoutC, b));
    printf("  offset of c: %2zu\n", offsetof(LayoutC, c));
    printf("  (no padding waste)\n\n");

    // ===== 综合对比 =====
    printf("=== Summary ===\n");
    printf("  LayoutA (bad order) : %2zu bytes\n", sizeof(LayoutA));
    printf("  LayoutB (optimized) : %2zu bytes\n", sizeof(LayoutB));
    printf("  LayoutC (packed)    : %2zu bytes\n", sizeof(LayoutC));

    printf("\nLayoutB saves %zu bytes compared to LayoutA by reordering members.\n",
           sizeof(LayoutA) - sizeof(LayoutB));

    return 0;
}