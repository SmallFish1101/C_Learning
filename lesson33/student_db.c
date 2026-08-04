/*
 * student_db.c
 * 第33课 实例1：二进制学生记录数据库
 *
 * 功能：用二进制文件存储学生记录，支持追加、查询、更新、列出。
 *      核心演示 fread / fwrite / fseek / ftell / rewind 的用法。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN  32

// ========== 数据结构 ==========
typedef struct {
    int  id;
    char name[NAME_LEN];
    float score;
} Student;

// ========== 函数原型 ==========
void db_append(const char *filename, const Student *s);
void db_query(const char *filename, int record_no, Student *out);
void db_update(const char *filename, int record_no, const Student *s);
void db_list_all(const char *filename);

int main(void)
{
    const char *filename = "students.bin";

    printf("=== Binary Student Database ===\n\n");

    // ------ 1. 追加三条记录 ------
    Student s1 = {1001, "Alice", 92.5f};
    Student s2 = {1002, "Bob",   85.0f};
    Student s3 = {1003, "Carol", 88.5f};

    printf("Appending records...\n");
    db_append(filename, &s1);
    db_append(filename, &s2);
    db_append(filename, &s3);

    // ------ 2. 列出所有记录 ------
    printf("\nAll records:\n");
    db_list_all(filename);

    // ------ 3. 查询第 1 条记录（从0开始计数）------
    Student q;
    db_query(filename, 1, &q);
    printf("\nRecord #1: ID=%d, Name=%s, Score=%.1f\n", q.id, q.name, q.score);

    // ------ 4. 修改第 1 条记录 ------
    Student updated = {1002, "Bob", 99.0f};       // Bob 的成绩大幅提升
    db_update(filename, 1, &updated);
    printf("\nAfter update:\n");
    db_list_all(filename);

    return 0;
}

// ========== 函数实现 ==========

/*
 * db_append:
 *   以追加模式打开文件，在末尾写入一条新记录。
 *
 *   使用 "ab" 模式——自动将位置指示器移到文件末尾，
 *   且不清空原有内容（"wb" 会清空）。
 */
void db_append(const char *filename, const Student *s)
{
    FILE *fp = fopen(filename, "ab");   // 二进制追加写
    if (fp == NULL) {
        printf("  ERROR: Cannot open '%s' for appending.\n", filename);
        return;
    }
    fwrite(s, sizeof(Student), 1, fp);
    fclose(fp);
}

/*
 * db_query:
 *   读取第 record_no 条记录（从 0 开始计数）。
 *
 *   核心：fseek(fp, record_no * sizeof(Student), SEEK_SET);
 */
void db_query(const char *filename, int record_no, Student *out)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("  ERROR: Cannot open '%s' for reading.\n", filename);
        return;
    }

    // 定位到目标记录的位置
    fseek(fp, record_no * sizeof(Student), SEEK_SET);

    // 读取一条记录
    size_t read = fread(out, sizeof(Student), 1, fp);
    if (read != 1) {
        printf("  ERROR: Failed to read record #%d.\n", record_no);
    }

    fclose(fp);
}

/*
 * db_update:
 *   覆盖写入第 record_no 条记录（从 0 开始计数）。
 *
 *   注意：使用 "r+b" 模式（文件必须已存在，且可读写）。
 */
void db_update(const char *filename, int record_no, const Student *s)
{
    FILE *fp = fopen(filename, "r+b");
    if (fp == NULL) {
        printf("  ERROR: Cannot open '%s' for updating.\n", filename);
        return;
    }

    fseek(fp, record_no * sizeof(Student), SEEK_SET);
    size_t written = fwrite(s, sizeof(Student), 1, fp);
    if (written != 1) {
        printf("  ERROR: Failed to update record #%d.\n", record_no);
    }

    fclose(fp);
}

/*
 * db_list_all:
 *   从头到尾读取并显示所有记录。
 *
 *   使用 rewind 确保从文件开头开始。
 */
void db_list_all(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("  No records found (file may not exist).\n");
        return;
    }

    Student s;
    size_t read;

    rewind(fp);   // 确保指针在文件开头（与刚打开 "rb" 等效，但多一次调用更安全）

    printf("  %-6s %-20s %s\n", "ID", "Name", "Score");
    printf("  ------ -------------------- -----\n");

    while ((read = fread(&s, sizeof(Student), 1, fp)) == 1) {
        printf("  %-6d %-20s %.1f\n", s.id, s.name, s.score);
    }

    fclose(fp);
}