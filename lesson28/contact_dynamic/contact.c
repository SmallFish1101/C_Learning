/*
 * contact.c
 * 第28课 作业一：动态通讯录 —— 核心功能实现（含自动扩容）
 */

#include "contact.h"

// ========== 初始化（动态分配初始内存）==========
void contact_init(ContactList *list)
{
    list->entries = (Contact *)malloc(INITIAL_CAPACITY * sizeof(Contact));
    if (list->entries == NULL) {
        printf("Fatal: Failed to allocate initial memory.\n");
        exit(1);   // 初始分配失败，程序无法继续
    }
    list->count = 0;
    list->capacity = INITIAL_CAPACITY;
}

// ========== 销毁通讯录（释放堆内存）==========
void contact_destroy(ContactList *list)
{
    free(list->entries);
    list->entries = NULL;    // 防止悬空指针
    list->count = 0;
    list->capacity = 0;
}

// ========== 添加联系人（含扩容逻辑）==========
void contact_add(ContactList *list)
{
    // 1. 检查是否需要扩容
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity * 2;   // 翻倍扩容

        // 安全模式：使用临时指针接收 realloc 的返回值
        Contact *tmp = (Contact *)realloc(list->entries,
                                         new_capacity * sizeof(Contact));
        if (tmp == NULL) {
            // realloc 失败，原内存块仍然有效
            printf("  Memory allocation failed. Cannot add more contacts.\n");
            return;
        }

        // 扩容成功，更新指针和容量
        list->entries = tmp;
        list->capacity = new_capacity;

        printf("  (contact list expanded to %d)\n", list->capacity);
    }

    // 2. 逐字段循环校验输入
    Contact new_contact;

    // 姓名校验
    while (1) {
        printf("  Name  : ");
        safe_read_line(new_contact.name, NAME_LEN);
        if (is_valid_name(new_contact.name)) {
            break;
        }
    }

    // 电话校验
    while (1) {
        printf("  Phone : ");
        safe_read_line(new_contact.phone, PHONE_LEN);
        if (is_valid_phone(new_contact.phone)) {
            break;
        }
    }

    // 年龄校验
    while (1) {
        printf("  Age   : ");
        char age_buf[10];
        safe_read_line(age_buf, sizeof(age_buf));
        if (is_valid_age(age_buf, &new_contact.age)) {
            break;
        }
    }

    // 3. 存入动态数组
    list->entries[list->count] = new_contact;
    list->count++;

    printf("  Contact '%s' added successfully.\n", new_contact.name);
}

// ========== 以下函数与第24课原版基本一致，不再重复展开 ==========
// contact_find / contact_delete / contact_modify / contact_list
// safe_read_line / is_valid_name / is_valid_phone / is_valid_age
// （可直接复用第24课练习一的实现，此处省略完整代码）
// ========== 安全输入辅助 ==========
/*
 * safe_read_line:
 *   用 fgets 读取一行，去掉末尾的换行符。
 *   返回：实际读取到的字符数（不含 '\0'），EOF 时返回 0。
 */
int safe_read_line(char *buffer, int size)
{
    if (fgets(buffer, size, stdin) == NULL) {
        // 遇到 EOF，让程序安全退出
        printf("\nEnd of input.\n");
        exit(0);
    }
    int len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';   // 去掉换行符
        len--;
    }
    return len;
}

int contact_find(const ContactList *list, const char *name)
{
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->entries[i].name, name) == 0) {
            return i;   // 找到了，返回索引
        }
    }
    return -1;         // 未找到
}

// ========== 删除联系人 ==========
void contact_delete(ContactList *list)
{
    if (list->count == 0) {
        printf("  The contact list is empty.\n");
        return;
    }

    char name[NAME_LEN];
    printf("  Enter name to delete: ");
    safe_read_line(name, NAME_LEN);

    int idx = contact_find(list, name);
    if (idx == -1) {
        printf("  Contact '%s' not found.\n", name);
        return;
    }

    // 用最后一个元素覆盖待删元素，然后 count--，高效且 O(1)
    list->entries[idx] = list->entries[list->count - 1];
    list->count--;

    printf("  Contact '%s' deleted.\n", name);
}

// ========== 修改联系人 ==========
void contact_modify(ContactList *list)
{
    if (list->count == 0) {
        printf("  The contact list is empty.\n");
        return;
    }

    char name[NAME_LEN];
    printf("  Enter name to modify: ");
    safe_read_line(name, NAME_LEN);

    int idx = contact_find(list, name);
    if (idx == -1) {
        printf("  Contact '%s' not found.\n", name);
        return;
    }

    Contact *c = &list->entries[idx];   // 用指针操作，简洁

    printf("  Current phone: %s\n", c->phone);
    printf("  New phone (press Enter to keep): ");
    char new_phone[PHONE_LEN];
    safe_read_line(new_phone, PHONE_LEN);
    if (new_phone[0] != '\0') {
        strcpy(c->phone, new_phone);   // 仅当用户输入了内容才更新
    }

    printf("  Current age: %d\n", c->age);
    printf("  New age (press Enter or 0 to keep): ");
    char age_buf[10];
    safe_read_line(age_buf, sizeof(age_buf));
    int new_age;
    if (sscanf(age_buf, "%d", &new_age) == 1 && new_age > 0) {
        c->age = new_age;
    }

    printf("  Contact '%s' updated.\n", name);
}

// ========== 列出所有联系人 ==========
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

/*
 * is_valid_name:
 *   校验姓名是否合法：非空，且长度不超过 NAME_LEN - 1。
 *   返回 1 合法，0 非法。
 */
int is_valid_name(const char *name)
{
    int len = strlen(name);
    if (len == 0) {
        printf("  ERROR: Name cannot be empty.\n");
        return 0;
    }
    if (len >= NAME_LEN) {    // >= NAME_LEN 则包含 '\0' 放不下
        printf("  ERROR: Name too long (max %d chars).\n", NAME_LEN - 1);
        return 0;
    }
    return 1;
}
/*
 * is_valid_phone:
 *   校验电话是否合法：非空，且只允许数字和连字符 '-'。
 *   返回 1 合法，0 非法。
 */
int is_valid_phone(const char *phone)
{
    int len = strlen(phone);
    if (len == 0) {
        printf("  ERROR: Phone cannot be empty.\n");
        return 0;
    }
    if (strspn(phone, "0123456789-") != (size_t)len) {
        printf("  ERROR: Phone can only contain digits and '-'.\n");
        return 0;
    }
    return 1;
}
/*
 * is_valid_age:
 *   校验年龄字符串是否合法：解析为整数，且在 1~150 之间，无多余字符。
 *   参数 age_str: 用户输入的年龄字符串
 *   参数 age_out: 输出参数，存放解析后的年龄
 *   返回 1 合法，0 非法。
 */
int is_valid_age(const char *age_str, int *age_out)
{
    int age;
    int pos = 0;
    if (sscanf(age_str, "%d %n", &age, &pos) != 1) {
        printf("  ERROR: Age must be an integer.\n");
        return 0;
    }
    if (age_str[pos] != '\0') {
        printf("  ERROR: Extra characters after age.\n");
        return 0;
    }
    if (age < 1 || age > 150) {
        printf("  ERROR: Age must be between 1 and 150.\n");
        return 0;
    }
    *age_out = age;
    return 1;
}
