/*
 * line_count.c
 * 第32课 练习一：统计文本文件的行数
 *
 * 功能：用户输入文件名，程序逐行读取该文件，
 *       统计并输出总行数。
 *       处理文件不存在的情况。
 */

#include <stdio.h>    // fopen, fclose, fgets, printf, perror
#include <stdlib.h>   // exit
#include <string.h>   // strlen

#define MAX_LINE_LEN  1024   // 每行最大字符数

/*
 * safe_read_line:
 *   从标准输入安全读取一行，去掉末尾换行符。
 *   参数 buffer: 存放结果的字符数组
 *   参数 size  : 数组最大容量
 *   返回: 实际读取的字符数（不含 '\0'）；EOF 时调用 exit
 */
int safe_read_line(char *buffer, int size)
{
    if (fgets(buffer, size, stdin) == NULL) {
        printf("\nEnd of input.\n");
        exit(0);
    }
    int len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    return len;
}

int main(void)
{
    char filename[256];      // 存放用户输入的文件名
    char line[MAX_LINE_LEN]; // 存放每次读取到的行内容
    FILE *fp = NULL;         // 文件指针（初始化为 NULL，好习惯）
    int line_count = 0;      // 行计数器

    printf("=== File Line Counter ===\n\n");

    // 1. 获取文件名
    printf("Enter the filename to count lines: ");
    safe_read_line(filename, sizeof(filename));

    // 2. 打开文件（只读模式）
    fp = fopen(filename, "r");
    if (fp == NULL) {
        // 打开失败：文件不存在、权限不足、路径错误等
        printf("\n  ERROR: Cannot open file '%s'.\n", filename);
        printf("  Please check that the file exists and you have read permission.\n");
        // perror 会输出操作系统的详细错误原因（如 "No such file or directory"）
        perror("  Reason");
        return 1;   // 非正常退出
    }

    printf("\n  Reading '%s'...\n", filename);

    // 3. 逐行读取，统计行数
    //    fgets 返回 NULL 时，通常表示到达文件末尾（或发生错误）
    while (fgets(line, sizeof(line), fp) != NULL) {
        line_count++;
    }

    // 4. 关闭文件（释放资源）
    fclose(fp);

    // 5. 输出统计结果
    printf("\n  ================================\n");
    printf("  File: %s\n", filename);
    printf("  Total lines: %d\n", line_count);
    printf("  ================================\n");

    return 0;
}