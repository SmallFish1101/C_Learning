/*
 * record_count.c
 * 第33课 练习一：统计二进制文件中的记录数
 *
 * 功能：打开一个二进制学生记录文件，用 fseek + ftell 获取文件大小，
 *       除以 sizeof(Student) 得到记录总数。
 *       处理文件不存在、空文件、大小不对齐等情况。
 */

#include <stdio.h>    // fopen, fclose, fseek, ftell, printf, perror
#include <stdlib.h>   // exit

#define NAME_LEN  32

// ========== 与实例1完全相同的结构体定义 ==========
/*
 * Student:
 *   学生记录结构体。本练习不读取实际内容，只依赖 sizeof(Student)
 *   来计算文件中有多少条记录。因此定义必须与创建该文件的程序一致。
 */
typedef struct {
    int  id;
    char name[NAME_LEN];
    float score;
} Student;

int main(void)
{
    char filename[256];      // 存放用户输入的文件名
    FILE *fp = NULL;         // 文件指针
    long file_size;          // 文件总字节数
    int  record_count;       // 记录总数

    printf("=== Binary Record Counter ===\n\n");

    // 1. 获取文件名
    printf("Enter filename (e.g., students.bin): ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        printf("\nEnd of input.\n");
        return 0;
    }
    // 去掉末尾的换行符
    int len;
    for (len = 0; filename[len] != '\0'; len++);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }

    // 2. 打开二进制文件（只读模式）
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("  ERROR: Cannot open '%s'.\n", filename);
        perror("  Reason");
        return 1;
    }

    // 3. 用 fseek 移到文件末尾，用 ftell 获取字节数
    fseek(fp, 0L, SEEK_END);        // 将文件指针移到末尾
    file_size = ftell(fp);          // 获取当前偏移量（= 文件总字节数）
    // 此时文件指针在末尾，如果之后需要从头读取，需要用 rewind 或 fseek(SEEK_SET)

    // 4. 计算记录总数
    if (file_size % sizeof(Student) != 0) {
        // 文件大小不是记录大小的整数倍，数据可能损坏或存储了其他内容
        printf("  WARNING: File size (%ld bytes) is not a multiple of "
               "record size (%zu bytes).\n",
               file_size, sizeof(Student));
        printf("  The file may be corrupted or not contain Student records.\n");
    }

    record_count = (int)(file_size / sizeof(Student));

    // 5. 输出统计结果
    printf("\n  ================================\n");
    printf("  File:          %s\n", filename);
    printf("  Record size:   %zu bytes\n", sizeof(Student));
    printf("  Total size:    %ld bytes\n", file_size);
    printf("  Record count:  %d\n", record_count);
    printf("  ================================\n");

    // 6. 关闭文件
    fclose(fp);

    return 0;
}