#include <stdio.h>
#include <stddef.h>   // offsetof

// 顺序不当——内存浪费
typedef struct {
    char  flag;        // 1 字节
    int   id;          // 4 字节
    char  type;        // 1 字节
} BadLayout;

// 顺序优化——节省内存
typedef struct {
    int   id;
    char  flag;
    char  type;
} GoodLayout;

// 强制紧凑
typedef struct __attribute__((packed)) {
    char  a;
    int   b;
    char  c;
} Packed;

int main(void) {
    printf("=== Structure Alignment Demo ===\n\n");

    printf("sizeof(BadLayout)  = %zu\n", sizeof(BadLayout));
    printf("sizeof(GoodLayout) = %zu\n", sizeof(GoodLayout));
    printf("sizeof(Packed)     = %zu\n\n", sizeof(Packed));

    printf("BadLayout offsets:\n");
    printf("  flag: %zu\n", offsetof(BadLayout, flag));
    printf("  id  : %zu\n", offsetof(BadLayout, id));
    printf("  type: %zu\n", offsetof(BadLayout, type));

    return 0;
}