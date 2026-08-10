#include "student.h"
#include "utils.h"
// ---------- 内部辅助 ----------

/*
 * recalc_scores:
 *   重新计算单个学生的总分和平均分。
 *   设为 static 因为它只在修改成绩后被本模块内部调用。
 */
static void recalc_scores(Student *s)
{
    s->total   = s->chinese + s->math + s->english;
    s->average = s->total / 3.0f;
}

/*
 * auto_expand:
 *   自动扩容动态数组。与第28课模式完全一致。
 *   返回 true 表示成功，false 表示内存不足（原数据仍保留）。
 */
static bool auto_expand(StudentManager *mgr)
{
    int new_cap = (mgr->capacity == 0)
                  ? INITIAL_CAPACITY
                  : mgr->capacity * 2;

    Student *tmp = (Student *)realloc(mgr->students,
                                      new_cap * sizeof(Student));
    if (tmp == NULL) return false;

    mgr->students = tmp;
    mgr->capacity = new_cap;
    return true;
}

static int read_grade(const char *prompt)
{
    int grade = 0;
    while (1) {
        grade = read_int(prompt);
        if (grade >= GRADE_MIN && grade <= GRADE_MAX) break;
        printf("  ERROR: Grade must be between %d and %d.\n",
               GRADE_MIN, GRADE_MAX);
    }
    return grade;
}

/*
 * update_ranks:
 *   在总分降序排列后，更新每个学生的排名字段。
 *   假设数组已按 total 降序排列。
 */
static void update_ranks(StudentManager *mgr)
{
    for (int i = 0; i < mgr->count; i++) {
        mgr->students[i].rank = i + 1;
        // 并列处理（与前一名的总分相同则排名相同）
        if (i > 0 &&
            mgr->students[i].total == mgr->students[i-1].total) {
            mgr->students[i].rank = mgr->students[i-1].rank;
        }
    }
}

// ----- 每个排序规则对应一个比较函数 -----

static int cmp_by_id_asc(const void *a, const void *b) {
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    return s1->id - s2->id;
}

static int cmp_by_total_desc(const void *a, const void *b) {
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    if (s1->total > s2->total) return -1;
    if (s1->total < s2->total) return  1;
    return 0;
}

static int cmp_by_chinese_desc(const void *a, const void *b) {
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    return s2->chinese - s1->chinese;
}

// （math_desc 和 english_desc 同理，略）

/*
 * manager_sort:
 *   根据 SortMethod 选择对应的比较函数，调用 qsort，
 *   然后更新 rank 和 sorted 标志。
 */
void manager_sort(StudentManager *mgr, SortMethod method)
{
    if (mgr->count == 0) {
        printf("  No students to sort.\n");
        return;
    }

    int (*cmp)(const void *, const void *) = NULL;
    switch (method) {
        case SORT_BY_ID_ASC:      cmp = cmp_by_id_asc;      break;
        case SORT_BY_TOTAL_DESC:  cmp = cmp_by_total_desc;   break;
        case SORT_BY_CHINESE_DESC:cmp = cmp_by_chinese_desc; break;
        // ... 其他 case
        default: printf("  Unknown sort method.\n"); return;
    }

    qsort(mgr->students, mgr->count, sizeof(Student), cmp);

    if (method == SORT_BY_TOTAL_DESC) {
        update_ranks(mgr);        // 按总分排序后更新排名
    }
    mgr->sorted = (method == SORT_BY_ID_ASC);  // 只有按学号升序时才标记为有序
}

/*
 * manager_init:
 *   初始化管理器，分配初始容量的动态数组。
 *   如果内存不足，打印错误信息并退出程序。
 */
void manager_init(StudentManager *mgr)
{

    mgr->students = (Student *)malloc(INITIAL_CAPACITY * sizeof(Student));
    if(mgr->students == NULL){
        fprintf(stderr, "  Failed to initialize student manager.\n");
        exit(EXIT_FAILURE);
    }
    mgr->count = 0;
    mgr->capacity = INITIAL_CAPACITY;
    mgr->sorted = false;
}

/*
 * manager_destroy:
 *   销毁管理器，释放动态数组内存。
 */
void manager_destroy(StudentManager *mgr)
{
    if (mgr->students) {
        free(mgr->students);
        mgr->students = NULL;
    }
    mgr->count = 0;
    mgr->capacity = 0;
    mgr->sorted = false;
}

/* 列表显示 */
void manager_list_students(const StudentManager *mgr){
    if (mgr->count == 0){
        printf("  No students to display.\n");
        return;
    }

    printf("  %-5s %-20s %-8s %-8s %-8s %-8s %-8s %-5s\n",
           "ID", "Name", "Chinese", "Math", "English", "Total", "Average", "Rank");
    for (int i = 0; i < mgr->count; i++) {
        const Student *s = &mgr->students[i];
       printf("  %-6d %-12s %6d %6d %6d %6d %5.1f %5d\n",
               s->id, s->name,
               s->chinese, s->math, s->english,
               s->total, s->average, s->rank);
    }
    printf("\n  Total students: %d\n", mgr->count);

}

/* CRUD 操作 */

/*
 * manager_add_student:
 *   添加一个学生。逐字段循环校验输入（学号必须正且唯一、姓名非空、
 *   成绩在 0~100 之间）。如果数组已满，自动扩容。
 *   添加完成后，标记数组为"未排序"（因为新元素可能破坏顺序）。
 *
 *   参数 mgr: 成绩管理系统指针
 */
void manager_add_student(StudentManager *mgr)
{
    // 1. 扩容检查
    if (mgr->count >= mgr->capacity) {
        if (!auto_expand(mgr)) {
            printf("  ERROR: Memory full. Cannot add student.\n");
            return;
        }
        printf("  (array expanded to %d)\n", mgr->capacity);
    }

    Student s;
    memset(&s, 0, sizeof(s));   // 清零所有字段（包括 total/average/rank）

    // 2. 学号输入（校验：正整数 + 唯一）
    while (1) {
        s.id = read_int("  Student ID: ");
        if (s.id <= 0) {
            printf("  ERROR: ID must be positive integer.\n");
            continue;
        }
        // 检查是否与已有学生的学号重复
        if (manager_find_by_id(mgr, s.id) != -1) {
            printf("  ERROR: ID %d already exists.\n", s.id);
            continue;
        }
        break;
    }

    // 3. 姓名输入
    while (1) {
        printf("  Name: ");
        safe_read_line(s.name, NAME_LEN);
        if (s.name[0] != '\0') break;
        printf("  ERROR: Name cannot be empty.\n");
    }

    // 4. 成绩输入（逐科校验范围）
    s.chinese = read_grade("  Chinese (0-100): ");
    s.math    = read_grade("  Math (0-100): ");
    s.english = read_grade("  English (0-100): ");

    // 5. 计算总分和平均分
    recalc_scores(&s);

    // 6. 存入数组
    mgr->students[mgr->count] = s;
    mgr->count++;
    mgr->sorted = false;   // 新元素破坏有序性

    printf("  Student '%s' (ID: %d) added.\n", s.name, s.id);
}

/*
 * manager_find_by_id:
 *   按学号查找学生，返回其数组索引。
 *   查找方式：如果数组已标记为 sorted，可用二分查找；
 *             否则用线性查找（安全且简单）。
 *
 *   参数 mgr: 系统指针
 *   参数 id : 要查找的学号
 *   返回: 匹配的学生索引，未找到返回 -1
 */
int manager_find_by_id(const StudentManager *mgr, int id)
{
    for (int i = 0; i < mgr->count; i++) {
        if (mgr->students[i].id == id) {
            return i;
        }
    }
    return -1;
}

/*
 * manager_delete_student:
 *   按学号删除学生。内部调用 manager_find_by_id 做查找，
 *   找到后，用最后一个元素覆盖被删元素（O(1) 删除法）。
 *
 *   参数 mgr: 系统指针
 */
void manager_delete_student(StudentManager *mgr)
{
    if (mgr->count == 0) {
        printf("  No students to delete.\n");
        return;
    }

    int id = read_int("  Enter student ID to delete: ");
    int idx = manager_find_by_id(mgr, id);

    if (idx == -1) {
        printf("  Student with ID %d not found.\n", id);
        return;
    }

    Student *s = &mgr->students[idx];
    printf("  Deleting: %d %s (C:%d M:%d E:%d)\n",
           s->id, s->name, s->chinese, s->math, s->english);

    // O(1) 删除：用最后一个元素覆盖被删元素
    mgr->students[idx] = mgr->students[mgr->count - 1];
    mgr->count--;
    mgr->sorted = false;   // 删除操作破坏有序性

    printf("  Student deleted.\n");
}

/*
 * manager_modify_student:
 *   按学号修改学生信息。先查找，找到后逐个字段提示修改，
 *   输入空行表示保持原值（姓名）或输入 0 表示保持原值（成绩）。
 *   修改完成后重新计算总分和平均分。
 *
 *   参数 mgr: 系统指针
 */
void manager_modify_student(StudentManager *mgr)
{
    if (mgr->count == 0) {
        printf("  No students to modify.\n");
        return;
    }

    int id = read_int("  Enter student ID to modify: ");
    int idx = manager_find_by_id(mgr, id);

    if (idx == -1) {
        printf("  Student with ID %d not found.\n", id);
        return;
    }

    Student *s = &mgr->students[idx];
    printf("  Current: %d %s  C:%d M:%d E:%d\n",
           s->id, s->name, s->chinese, s->math, s->english);

    // 修改姓名（空行保持原值）
    printf("  New name (Enter to keep): ");
    char new_name[NAME_LEN];
    safe_read_line(new_name, NAME_LEN);
    if (new_name[0] != '\0') {
        strcpy(s->name, new_name);
    }

    // 修改成绩（0 或空行保持原值）
    printf("  New Chinese score (0 or Enter to keep): ");
    int new_score = read_int("");
    if (new_score >= GRADE_MIN && new_score <= GRADE_MAX) {
        s->chinese = new_score;
    }

    printf("  New Math score (0 or Enter to keep): ");
    new_score = read_int("");
    if (new_score >= GRADE_MIN && new_score <= GRADE_MAX) {
        s->math = new_score;
    }

    printf("  New English score (0 or Enter to keep): ");
    new_score = read_int("");
    if (new_score >= GRADE_MIN && new_score <= GRADE_MAX) {
        s->english = new_score;
    }

    recalc_scores(s);
    mgr->sorted = false;

    printf("  Student %d '%s' updated.\n", s->id, s->name);
}

/*
 * manager_find_by_name:
 *   按姓名前缀模糊查找。使用 strncmp 匹配前 len 个字符。
 *   打印所有匹配的学生列表。
 *
 *   参数 mgr : 系统指针（只读）
 *   参数 name: 用户输入的姓名或前缀（如 "Zhang" 匹配 "Zhang San"）
 */
void manager_find_by_name(const StudentManager *mgr, const char *name)
{
    if (mgr->count == 0) {
        printf("  (no students)\n");
        return;
    }

    int len = strlen(name);
    if (len == 0) {
        printf("  Name cannot be empty.\n");
        return;
    }

    int match_count = 0;
    printf("  %-6s %-12s %6s %6s %6s %6s %6s\n",
           "ID", "Name", "CN", "MA", "EN", "Total", "Avg");
    printf("  ------ ------------ ------ ------ ------ ------ ------\n");

    for (int i = 0; i < mgr->count; i++) {
        if (strncmp(mgr->students[i].name, name, len) == 0) {
            Student *s = &mgr->students[i];
            printf("  %-6d %-12s %6d %6d %6d %6d %5.1f\n",
                   s->id, s->name, s->chinese, s->math, s->english,
                   s->total, s->average);
            match_count++;
        }
    }

    printf("  %d match(es) for prefix \"%s\".\n", match_count, name);
}

/*
 * manager_show_stats:
 *   显示全班各科统计信息：总分的最高/最低分、各科平均分、各科最高/最低分。
 *
 *   参数 mgr: 系统指针（只读）
 */
void manager_show_stats(const StudentManager *mgr)
{
    if (mgr->count == 0) {
        printf("  (no students)\n");
        return;
    }

    int sum_chinese = 0, sum_math = 0, sum_english = 0;
    int max_total = 0, min_total = 9999;
    int max_chinese = 0, max_math = 0, max_english = 0;
    int min_chinese = 100, min_math = 100, min_english = 100;

    for (int i = 0; i < mgr->count; i++) {
        Student *s = &mgr->students[i];

        sum_chinese += s->chinese;  sum_math += s->math;  sum_english += s->english;

        if (s->total > max_total) max_total = s->total;
        if (s->total < min_total) min_total = s->total;

        if (s->chinese > max_chinese) max_chinese = s->chinese;
        if (s->chinese < min_chinese) min_chinese = s->chinese;
        if (s->math    > max_math)    max_math    = s->math;
        if (s->math    < min_math)    min_math    = s->math;
        if (s->english > max_english) max_english = s->english;
        if (s->english < min_english) min_english = s->english;
    }

    int n = mgr->count;
    printf("  ========== Class Statistics ==========\n");
    printf("  Student count: %d\n", n);
    printf("  Avg Total Score: %.1f\n", (sum_chinese + sum_math + sum_english) / (3.0f * n));
    printf("  Max Total: %d  |  Min Total: %d\n", max_total, min_total);
    printf("  -------------------------------------\n");
    printf("  Chinese  Avg: %5.1f  Max: %3d  Min: %3d\n", (float)sum_chinese / n, max_chinese, min_chinese);
    printf("  Math     Avg: %5.1f  Max: %3d  Min: %3d\n", (float)sum_math    / n, max_math,    min_math);
    printf("  English  Avg: %5.1f  Max: %3d  Min: %3d\n", (float)sum_english / n, max_english, min_english);
    printf("  ======================================\n");
}

/*
 * manager_save_to_file:
 *   将当前所有学生数据以文本格式写入文件。
 *   每行格式: ID|Name|Chinese|Math|English
 *   分隔符 '|' 避免与姓名中的空格混淆。
 *
 *   参数 mgr     : 系统指针（只读）
 *   参数 filename: 要写入的文件名（如 "grades.txt"）
 */
void manager_save_to_file(const StudentManager *mgr, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("  ERROR: Cannot open '%s' for writing.\n", filename);
        perror("  Reason");
        return;
    }

    for (int i = 0; i < mgr->count; i++) {
        Student *s = &mgr->students[i];
        fprintf(fp, "%d|%s|%d|%d|%d\n",
                s->id, s->name, s->chinese, s->math, s->english);
    }

    fclose(fp);
    printf("  Saved %d student(s) to '%s'.\n", mgr->count, filename);
}

/*
 * manager_load_from_file:
 *   从文本文件逐行读取学生数据，添加到系统中。
 *   每行格式: ID|Name|Chinese|Math|English
 *   如果某行格式不正确，跳过并给出警告。
 *   如果系统数组已满，自动扩容。
 *
 *   参数 mgr     : 系统指针（数据追加到现有列表末尾）
 *   参数 filename: 要读取的文件名
 */
void manager_load_from_file(StudentManager *mgr, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("  ERROR: Cannot open '%s' for reading.\n", filename);
        perror("  Reason");
        return;
    }

    char line[FILE_LINE_LEN];
    int loaded = 0, skipped = 0;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // 去除末尾换行符
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') line[len - 1] = '\0';

        // 跳过空行
        if (line[0] == '\0') continue;

        // 解析字段
        Student s;
        memset(&s, 0, sizeof(s));
        int parsed = sscanf(line, "%d|%[^|]|%d|%d|%d",
                            &s.id, s.name, &s.chinese, &s.math, &s.english);

        if (parsed != 5) {
            printf("  WARNING: Skipping malformed line: \"%s\"\n", line);
            skipped++;
            continue;
        }

        // 成绩合法性检查
        if (s.chinese < GRADE_MIN || s.chinese > GRADE_MAX ||
            s.math    < GRADE_MIN || s.math    > GRADE_MAX ||
            s.english < GRADE_MIN || s.english > GRADE_MAX) {
            printf("  WARNING: Invalid grades for ID %d, skipping.\n", s.id);
            skipped++;
            continue;
        }

        // 扩容检查
        if (mgr->count >= mgr->capacity) {
            if (!auto_expand(mgr)) {
                printf("  ERROR: Memory full. Stopped loading.\n");
                break;
            }
        }

        recalc_scores(&s);
        mgr->students[mgr->count] = s;
        mgr->count++;
        loaded++;
    }

    fclose(fp);
    mgr->sorted = false;

    printf("  Loaded %d student(s) from '%s'.\n", loaded, filename);
    if (skipped > 0) {
        printf("  (%d line(s) skipped due to errors.)\n", skipped);
    }
}