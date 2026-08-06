/*
 * contact.c
 * 通讯录模块 —— 所有函数的实现。
 *
 * 内部的 auto_expand 函数用 static 隐藏，外部不可见。
 * 所有公开函数均在此实现，签名与 contact.h 完全一致。
 */

#include "contact.h"

// ========== 内部辅助函数（static）==========

/*
 * auto_expand:
 *   自动扩容通讯录数组（当 count >= capacity 时调用）。
 *   使用 realloc 安全模式：临时指针 → 检查 NULL → 更新原指针。
 *   设为 static 因为它只在 contact_add / contact_load_from_file 内部使用。
 *
 *   参数 list: 通讯录指针
 *   返回: true 扩容成功，false 内存不足（原数据仍保留）
 */
static bool auto_expand(ContactList *list)
{
    int new_cap = (list->capacity == 0)
                  ? INITIAL_CAPACITY
                  : list->capacity * 2;

    Contact *tmp = (Contact *)realloc(list->entries,
                                      new_cap * sizeof(Contact));
    if (tmp == NULL) {
        return false;   // 扩容失败，原数组仍有效
    }

    list->entries  = tmp;
    list->capacity = new_cap;
    return true;
}

// ========== 公开函数的实现 ==========

void contact_init(ContactList *list)
{
    list->entries = (Contact *)malloc(INITIAL_CAPACITY * sizeof(Contact));
    if (list->entries == NULL) {
        printf("Fatal: Initial memory allocation failed.\n");
        exit(1);
    }
    list->count    = 0;
    list->capacity = INITIAL_CAPACITY;
}

void contact_destroy(ContactList *list)
{
    free(list->entries);
    list->entries  = NULL;   // 防御性置空
    list->count    = 0;
    list->capacity = 0;
}

// ========== 增 ==========

void contact_add(ContactList *list)
{
    // 1. 扩容检查
    if (list->count >= list->capacity) {
        if (!auto_expand(list)) {
            printf("  ERROR: Memory full. Cannot add.\n");
            return;
        }
        printf("  (contact list expanded to %d)\n", list->capacity);
    }

    // 2. 逐字段循环校验输入
    Contact c;

    while (1) {
        printf("  Name : ");
        safe_read_line(c.name, NAME_LEN);
        if (is_valid_name(c.name)) break;
    }

    while (1) {
        printf("  Phone: ");
        safe_read_line(c.phone, PHONE_LEN);
        if (is_valid_phone(c.phone)) break;
    }

    while (1) {
        printf("  Age  : ");
        char age_buf[10];
        safe_read_line(age_buf, sizeof(age_buf));
        if (is_valid_age(age_buf, &c.age)) break;
    }

    // 3. 存入数组
    list->entries[list->count] = c;
    list->count++;

    printf("  Contact '%s' added.\n", c.name);
}

// ========== 删 ==========

void contact_delete(ContactList *list)
{
    if (list->count == 0) {
        printf("  List is empty.\n");
        return;
    }

    char name[NAME_LEN];
    printf("  Name to delete: ");
    safe_read_line(name, NAME_LEN);

    int idx = contact_find(list, name);
    if (idx == -1) {
        printf("  '%s' not found.\n", name);
        return;
    }

    // 用最后一个元素覆盖被删元素（O(1) 删除）
    list->entries[idx] = list->entries[list->count - 1];
    list->count--;

    printf("  '%s' deleted.\n", name);
}

// ========== 查 ==========

int contact_find(const ContactList *list, const char *name)
{
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->entries[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// ========== 改 ==========

void contact_modify(ContactList *list)
{
    if (list->count == 0) {
        printf("  List is empty.\n");
        return;
    }

    char name[NAME_LEN];
    printf("  Name to modify: ");
    safe_read_line(name, NAME_LEN);

    int idx = contact_find(list, name);
    if (idx == -1) {
        printf("  '%s' not found.\n", name);
        return;
    }

    Contact *c = &list->entries[idx];

    printf("  Current phone: %s\n", c->phone);
    printf("  New phone (Enter to keep): ");
    char new_phone[PHONE_LEN];
    safe_read_line(new_phone, PHONE_LEN);
    if (new_phone[0] != '\0') {
        strcpy(c->phone, new_phone);
    }

    printf("  Current age: %d\n", c->age);
    printf("  New age (Enter or 0 to keep): ");
    int new_age = read_int("");
    if (new_age > 0) {
        c->age = new_age;
    }

    printf("  '%s' updated.\n", name);
}

// ========== 列表 ==========

void contact_list(const ContactList *list)
{
    if (list->count == 0) {
        printf("  (empty)\n");
        return;
    }

    printf("  %-3s %-20s %-15s %s\n", "No.", "Name", "Phone", "Age");
    printf("  --- -------------------- --------------- ---\n");
    for (int i = 0; i < list->count; i++) {
        printf("  %-3d %-20s %-15s %d\n",
               i + 1,
               list->entries[i].name,
               list->entries[i].phone,
               list->entries[i].age);
    }
}

// ========== 文件保存 ==========

void contact_save_to_file(const ContactList *list, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("  ERROR: Cannot open '%s' for writing.\n", filename);
        perror("  Reason");
        return;
    }

    for (int i = 0; i < list->count; i++) {
        fprintf(fp, "%s|%s|%d\n",
                list->entries[i].name,
                list->entries[i].phone,
                list->entries[i].age);
    }

    fclose(fp);
    printf("  Saved %d contact(s) to '%s'.\n", list->count, filename);
}

// ========== 文件加载 ==========

void contact_load_from_file(ContactList *list, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("  ERROR: Cannot open '%s' for reading.\n", filename);
        perror("  Reason");
        return;
    }

    char line[FILE_LINE_LEN];
    int loaded = 0;
    int skipped = 0;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // 去换行符
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') line[len - 1] = '\0';

        // 跳过空行
        if (line[0] == '\0') continue;

        // 解析字段
        Contact c;
        int parsed = sscanf(line, "%[^|]|%[^|]|%d", c.name, c.phone, &c.age);

        if (parsed != 3) {
            printf("  WARNING: Skipping malformed line: \"%s\"\n", line);
            skipped++;
            continue;
        }

        // 扩容检查
        if (list->count >= list->capacity) {
            if (!auto_expand(list)) {
                printf("  ERROR: Memory full. Stopped loading.\n");
                break;
            }
        }

        // 存入数组
        list->entries[list->count] = c;
        list->count++;
        loaded++;
    }

    fclose(fp);

    printf("  Loaded %d contact(s) from '%s'.\n", loaded, filename);
    if (skipped > 0) {
        printf("  (%d line(s) skipped due to format errors.)\n", skipped);
    }
}

// ========== 安全输入 ==========

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

        printf("  ERROR: Please enter an integer.\n");
    }
}

// ========== 数据校验 ==========

bool is_valid_name(const char *name)
{
    int len = strlen(name);
    if (len == 0) {
        printf("  ERROR: Name cannot be empty.\n");
        return false;
    }
    if (len >= NAME_LEN) {
        printf("  ERROR: Name too long (max %d chars).\n", NAME_LEN - 1);
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