#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp = fopen("output.txt", "r");
    if (fp == NULL) {
        printf("Error: cannot open output.txt for reading.\n");
        return 1;
    }

    char line[256];
    int line_num = 0;

    // 逐行读取，直到文件末尾
    while (fgets(line, sizeof(line), fp) != NULL) {
        line_num++;
        printf("Line %d: %s", line_num, line);  // line 中已含换行符
    }

    fclose(fp);
    return 0;
}