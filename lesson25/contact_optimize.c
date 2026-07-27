/*
 * contact_optimize.c
 * 第25课 练习二：尝试优化 Contact 结构体的内存布局
 *
 * 结论：由于成员总大小为 74 字节，整体对齐要求 4 字节，
 *       无论成员如何排列，sizeof 始终为 76 字节。
 */

#include <stdio.h>    // printf
#include <stddef.h>   // offsetof

#define NAME_LEN  50
#define PHONE_LEN 20

// ========== V1：age 放在最前面 ==========
typedef struct {
    int  age;
    char name[NAME_LEN];
    char phone[PHONE_LEN];
} ContactV1;

// ========== V2：age 放在中间 ==========
typedef struct {
    char name[NAME_LEN];
    int  age;
    char phone[PHONE_LEN];
} ContactV2;

// ========== V3：原始顺序 ==========
typedef struct {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    int  age;
} ContactV3;

int main(void)
{
    printf("=== Contact Structure Layout Optimization ===\n\n");

    // ----- V1 -----
    printf("ContactV1 (age, name, phone):\n");
    printf("  sizeof  = %2zu bytes\n", sizeof(ContactV1));
    printf("  offset of age : %2zu\n", offsetof(ContactV1, age));
    printf("  offset of name: %2zu\n", offsetof(ContactV1, name));
    printf("  offset of phone: %2zu\n", offsetof(ContactV1, phone));
    printf("\n");

    // ----- V2 -----
    printf("ContactV2 (name, age, phone):\n");
    printf("  sizeof  = %2zu bytes\n", sizeof(ContactV2));
    printf("  offset of name: %2zu\n", offsetof(ContactV2, name));
    printf("  offset of age : %2zu\n", offsetof(ContactV2, age));
    printf("  offset of phone: %2zu\n", offsetof(ContactV2, phone));
    printf("\n");

    // ----- V3 (原始) -----
    printf("ContactV3 (name, phone, age) - original:\n");
    printf("  sizeof  = %2zu bytes\n", sizeof(ContactV3));
    printf("  offset of name : %2zu\n", offsetof(ContactV3, name));
    printf("  offset of phone: %2zu\n", offsetof(ContactV3, phone));
    printf("  offset of age  : %2zu\n", offsetof(ContactV3, age));
    printf("\n");

    // ===== 结论 =====
    printf("=== Conclusion ===\n");
    printf("All three layouts have the same sizeof: %zu bytes.\n",
           sizeof(ContactV1));
    printf("This is because the total member size (50+20+4) = 74 bytes,\n");
    printf("and the struct must be aligned to the largest member's\n");
    printf("alignment (int = 4 bytes). 74 rounded up to the next\n");
    printf("multiple of 4 is 76. No reordering can break this rule.\n");

    return 0;
}