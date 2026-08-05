/*
 * reverse_list.c
 * 第33课 练习二：反序输出二进制学生记录文件
 *
 * 功能：从最后一条记录开始，逐条向前读取并打印所有学生信息。
 *       核心演示 fseek + SEEK_SET 的随机定位能力。
 */

#include <stdio.h>    // fopen, fclose, fseek, ftell, fread, printf, perror
#include <stdlib.h>   // exit

#define NAME_LEN  32

// ========== 与实例1完全相同的结构体定义 ==========
/*
 * Student:
 *   必须与创建 students.bin 的程序使用完全一致的定义，
 *   包括成员顺序、类型和 NAME_LEN 的值。
 *   否则 sizeof(Student) 不匹配，fseek 定位会错误。
 */
typedef struct {
    int  id;
    char name[NAME_LEN];
    float score;
} Student;

int main(void)
{
    const char *filename = "students.bin";   // 默认文件名（与实例1一致）
    FILE *fp = NULL;
    long file_size;
    int  record_count;

    printf("=== Reverse Student List ===\n\n");

    // 1. 打开二进制文件（只读）
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("  ERROR: Cannot open '%s'.\n", filename);
        printf("  Please run student_db first to create the file.\n");
        perror("  Reason");
        return 1;
    }

    // 2. 获取文件大小并计算记录总数
    fseek(fp, 0L, SEEK_END);           // 移到文件末尾
    file_size = ftell(fp);             // 获取总字节数
    record_count = (int)(file_size / sizeof(Student));

    if (record_count == 0) {
        printf("  The file is empty (no records).\n");
        fclose(fp);
        return 0;
    }

    printf("  File: %s  |  Size: %ld bytes  |  Records: %d\n\n",
           filename, file_size, record_count);

    // 3. 从最后一条记录开始，逐条向前读取并打印
    printf("  %-6s %-20s %s\n", "ID", "Name", "Score");
    printf("  ------ -------------------- -----\n");

    for (int i = record_count - 1; i >= 0; i--)
    {
        // ★ 核心：用 fseek 跳到第 i 条记录的位置
        //   偏移量 = i * sizeof(Student)
        //   SEEK_SET 表示从文件开头开始计算偏移
        if (fseek(fp, (long)i * sizeof(Student), SEEK_SET) != 0) {
            printf("  ERROR: fseek failed for record %d.\n", i);
            break;
        }

        // 读取一条完整的 Student 记录
        Student s;
        size_t read = fread(&s, sizeof(Student), 1, fp);
        if (read != 1) {
            printf("  WARNING: Failed to read record %d (fread returned %zu).\n",
                   i, read);
            continue;   // 跳过损坏的记录，继续尝试前一条
        }

        // 打印该记录内容
        printf("  %-6d %-20s %.1f\n", s.id, s.name, s.score);
    }

    // 4. 关闭文件
    fclose(fp);

    printf("\n  Done. Listed %d record(s) in reverse order.\n", record_count);
    return 0;
}