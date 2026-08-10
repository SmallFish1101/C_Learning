/*
 * utils.c
 * 通用工具函数库 —— 具体实现。
 *
 * 每个函数都遵循单一职责原则。
 * 内部辅助函数用 static 隐藏，不对外暴露。
 */

#include "utils.h"

// ==================== 安全输入 ====================

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

int read_int(const char *prompt)
{
    char line[100];

    while (1) {
        printf("%s", prompt);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nEnd of input.\n");
            exit(0);
        }

        int value;
        int pos = 0;
        int matched = sscanf(line, "%d %n", &value, &pos);

        if (matched == 1 && line[pos] == '\0') {
            return value;
        }

        printf("  ERROR: Please enter a valid integer.\n");
    }
}

double read_double(const char *prompt)
{
    char line[100];

    while (1) {
        printf("%s", prompt);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nEnd of input.\n");
            exit(0);
        }

        double value;
        int pos = 0;
        int matched = sscanf(line, "%lf %n", &value, &pos);

        if (matched == 1 && line[pos] == '\0') {
            return value;
        }

        printf("  ERROR: Please enter a valid number.\n");
    }
}

// ==================== 数据校验 ====================

bool is_valid_name(const char *name, int max_len)
{
    int len = strlen(name);
    if (len == 0) {
        printf("  ERROR: Name cannot be empty.\n");
        return false;
    }
    if (len >= max_len) {
        printf("  ERROR: Name too long (max %d chars).\n", max_len - 1);
        return false;
    }
    return true;
}

bool is_valid_phone(const char *phone)
{
    int len = strlen(phone);
    if (len == 0) {
        printf("  ERROR: Phone cannot be empty.\n");
        return false;
    }
    // strspn 返回开头连续由合法字符组成的子串长度
    // 若等于总长度，说明所有字符都是合法的
    if (strspn(phone, "0123456789-") != (size_t)len) {
        printf("  ERROR: Phone can only contain digits and '-'.\n");
        return false;
    }
    return true;
}

bool is_valid_age(const char *age_str, int *age_out)
{
    int age;
    int pos = 0;

    if (sscanf(age_str, "%d %n", &age, &pos) != 1) {
        printf("  ERROR: Age must be an integer.\n");
        return false;
    }
    if (age_str[pos] != '\0') {
        printf("  ERROR: Extra characters after age.\n");
        return false;
    }
    if (age < 1 || age > 150) {
        printf("  ERROR: Age must be between 1 and 150.\n");
        return false;
    }

    *age_out = age;
    return true;
}

// ==================== 随机数 ====================

int random_range(int min, int max)
{
    // rand() % N 产生 0 ~ N-1，加上 min 后变成 min ~ min+N-1
    return min + rand() % (max - min + 1);
}