#include <stdio.h>
#include <string.h>

int main(void) {
    char dest[10] = "AAAAAAAAA";  // 9个A + '\0'
    // 源字符串 "Hi" 长度 2，n=5，strncpy 会复制 'H','i','\0','\0','\0'
    strncpy(dest, "Hi", 5);
    printf("dest after strncpy(dest, \"Hi\", 5): \"%s\"\n", dest);

    // 重要：如果源长度 >= n，strncpy 不会自动补 '\0'！
    char dest2[5] = "AAAA";
    strncpy(dest2, "HelloWorld", sizeof(dest2)); // 只复制 5 个字符，没有 '\0'！
    // 手动添加 '\0' 保证安全
    dest2[sizeof(dest2)-1] = '\0';
    printf("dest2 after strncpy: \"%s\"\n", dest2);
    return 0;
}