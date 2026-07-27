#include <stdio.h>
#include <stddef.h>

#define NAME_LEN  50
#define PHONE_LEN 20

typedef struct {
    char name[NAME_LEN];     // 50 字节，偏移 0
    char phone[PHONE_LEN];   // 20 字节，偏移 50
    int  age;               // 4 字节，偏移 70（50+20）
} Contact;

int main(void) {
    printf("sizeof(Contact)  = %zu\n", sizeof(Contact));
    printf("offset of name:   %zu\n", offsetof(Contact, name));
    printf("offset of phone:  %zu\n", offsetof(Contact, phone));
    printf("offset of age:    %zu\n", offsetof(Contact, age));

    // 分析：50 + 20 = 70，age 偏移刚好是 70，
    // 70 不是 4 的倍数吗？70 / 4 = 17.5，不是整数！
    // 说明 age 前应填充 2 字节到偏移 72
    return 0;
}