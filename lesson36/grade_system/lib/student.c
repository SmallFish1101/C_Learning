#include "student.h"

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