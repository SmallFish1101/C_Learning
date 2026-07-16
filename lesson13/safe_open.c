/*
 * safe_open.c
 * 第13课 作业三（选做）：资源安全打开 —— 使用 goto 集中错误处理
 *
 * 功能：模拟文件处理和内存分配流程，演示 goto 错误处理模式。
 *       如果任何一步失败，跳转到 cleanup 统一清理资源。
 */

#include <stdio.h>   // fopen, fclose, printf, perror
#include <stdlib.h>  // malloc, free, exit

int main(void)
{
    printf("=== Safe Resource Open Demo ===\n\n");

    // 初始化所有指针为 NULL
    // 这样做的好处：cleanup 中可以安全地检查指针是否为 NULL
    // 如果某个文件打开失败，它仍为 NULL，cleanup 不会尝试关闭它
    FILE *input_file  = NULL;   // 输入文件指针
    FILE *output_file = NULL;   // 输出文件指针
    char *buffer      = NULL;   // 动态分配的内存缓冲区

    // ===== 步骤 1：打开输入文件 =====
    input_file = fopen("input.txt", "r");   // 以只读方式打开
    if (input_file == NULL) {
        // 文件可能不存在，打印错误信息
        printf("ERROR: Cannot open input.txt\n");
        // 跳转到 cleanup，此时 output_file 和 buffer 都还是 NULL
        // cleanup 中会安全地跳过它们
        goto cleanup;
    }
    printf("SUCCESS: input.txt opened.\n");

    // ===== 步骤 2：分配内存缓冲区 =====
    buffer = (char*)malloc(1024);   // 申请 1024 字节（1KB）的内存
    if (buffer == NULL) {
        // 内存分配失败（在嵌入式或内存不足时可能发生）
        printf("ERROR: Memory allocation failed.\n");
        // 此时 input_file 已经打开，需要关闭它
        // cleanup 中会处理
        goto cleanup;
    }
    printf("SUCCESS: Buffer allocated (1024 bytes).\n");

    // ===== 步骤 3：打开输出文件 =====
    output_file = fopen("output.txt", "w");   // 以只写方式打开
    if (output_file == NULL) {
        printf("ERROR: Cannot open output.txt\n");
        // 此时 input_file 和 buffer 都已分配，需要清理
        // cleanup 中会统一处理
        goto cleanup;
    }
    printf("SUCCESS: output.txt opened.\n");

    // ===== 正常操作（模拟） =====
    printf("\nProcessing data...\n");
    // 这里可以写入实际的文件操作代码，如 fread / fwrite
    // 本作业省略

    printf("All operations completed successfully!\n");

    // ===== 统一清理区 =====
    // 无论成功还是失败，最终都会执行到这里
cleanup:
    printf("\n--- Cleanup ---\n");

    // 关闭文件前必须检查指针是否非空
    // 如果某个文件从未成功打开，它的指针仍为 NULL，跳过
    if (input_file != NULL) {
        fclose(input_file);
        printf("Closed input.txt\n");
    }

    if (output_file != NULL) {
        fclose(output_file);
        printf("Closed output.txt\n");
    }

    // 释放内存，free(NULL) 是安全的，什么也不做
    if (buffer != NULL) {
        free(buffer);
        printf("Freed buffer memory\n");
    }

    printf("\nProgram finished.\n");
    return 0;
}