#include <stdio.h>

int main(void)
{
    printf("ASCII Table (32-126): Printable Characters\n");
    printf("---------------------------------------------------------\n");

    int count = 0;          // 计数器，每行打印4个字符
    for (int ch = 32; ch <= 126; ch++)
    {
        // 打印字符、十进制、十六进制
        // %-2c: 左对齐占2格（字符）
        // %3d: 右对齐占3格（十进制）
        // 0x%02X: 十六进制，2位，大写字母，不足补零
        printf("%c %3d 0x%02X   ", ch, ch, ch);

        count++;
        if (count % 4 == 0)
        {
            printf("\n");   // 每4个字符换行
        }
    }

    // 如果最后一行不满4个，也换行
    if (count % 4 != 0)
    {
        printf("\n");
    }

    printf("---------------------------------------------------------\n");
    printf("Done. Total: %d characters printed.\n", count);

    return 0;
}