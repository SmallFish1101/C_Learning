#include <stdio.h>
#include <string.h>

// 声明手写版本
size_t my_strlen(const char *s);
char *my_strcpy(char *dest, const char *src);
char *my_strcat(char *dest, const char *src);
int my_strcmp(const char *s1, const char *s2);

int main(void) {
    // 测试 strlen
    printf("my_strlen(\"Hello\") = %zu (expected 5)\n", my_strlen("Hello"));

    // 测试 strcpy
    char buf1[20];
    my_strcpy(buf1, "World");
    printf("buf1 after my_strcpy: %s\n", buf1);

    // 测试 strcat
    char buf2[30] = "Hello ";
    my_strcat(buf2, "World!");
    printf("buf2 after my_strcat: %s\n", buf2);

    // 测试 strcmp
    printf("my_strcmp(\"abc\", \"abc\") = %d (expected 0)\n", my_strcmp("abc", "abc"));
    printf("my_strcmp(\"abc\", \"abd\") = %d (expected < 0)\n", my_strcmp("abc", "abd"));
    return 0;
}

size_t my_strlen(const char *s) {
    const char *p = s;
    while (*p) p++;       // 等价于 while (*p != '\0') p++;
    return (size_t)(p - s);
}

char *my_strcpy(char *dest, const char *src) {
    char *ret = dest;               // 保存 dest 的起始地址用于返回
    while ((*dest++ = *src++));     // 先赋值，再判断赋过去的值是否为 '\0'
    return ret;
}

char *my_strcat(char *dest, const char *src) {
    char *ret = dest;
    while (*dest) dest++;           // 找到 dest 的末尾 '\0'
    while ((*dest++ = *src++));     // 从末尾开始复制 src
    return ret;
}

int my_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {   // 只要没到结尾且字符相等，继续前进
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}