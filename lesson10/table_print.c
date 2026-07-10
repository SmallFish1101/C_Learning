#include <stdio.h>

int main(void) {
    printf("ASCII Table (32-95) - 4 columns per row\n");
    printf("------------------------------------------\n");

    for (int start = 32; start < 96; start += 4) {
        // 每行打印4个字符
        for (int i = 0; i < 4; i++) {
            int ch_code = start + i;
            if (ch_code > 95) break;

            // 打印格式：字符左对齐占2位，十进制右对齐占3位，十六进制右对齐占4位，总计约9字符，保持8字符稍微调整
            // 这里设计格式为: "C:DDD 0xHH" 大约9字符，为了更紧凑，用"%-2c %3d 0x%02X" 并设最小宽度
            printf("%-2c %3d 0x%02X   ", ch_code, ch_code, ch_code);
        }
        printf("\n");
    }

    printf("------------------------------------------\n");
    return 0;
}