/*
 * safe_array.c
 * 安全整数动态数组模块 —— 具体实现
 *
 * 扩容策略：capacity 从 0 → SAFE_ARRAY_INIT_CAPACITY (4)，
 *           之后每次满时翻倍（× SAFE_ARRAY_GROWTH_FACTOR）。
 */

#include "safe_array.h"

// ========== 初始化 ==========
/*
 * array_init:
 *   将结构体的三个字段全部置为 0/NULL。
 *   此时 data 为 NULL，表示尚未分配任何内存。
 *   这种"延迟分配"策略避免了无元素时占用堆内存。
 */
void array_init(SafeIntArray *arr)
{
    arr->data     = NULL;   // 初始无内存分配
    arr->count    = 0;
    arr->capacity = 0;
}

// ========== 追加元素（含扩容）==========
/*
 * array_append:
 *   在数组末尾添加一个元素。
 *   如果数组已满（count >= capacity），自动扩容。
 *   参数 arr: 数组指针
 *   参数 value: 要追加的值
 *   返回: 1 表示成功，0 表示内存分配失败
 *
 *   扩容安全规则：
 *     - 若 capacity == 0，分配初始容量
 *     - 否则，容量翻倍
 *     - 始终使用临时指针 tmp 接收 realloc 结果
 *     - 若 realloc 失败，原数组保持不变，返回 0
 */
int array_append(SafeIntArray *arr, int value)
{
    // 1. 检查是否需要扩容
    if (arr->count >= arr->capacity) {
        // 计算新容量：若当前为 0 则用初始值，否则翻倍
        int new_capacity = (arr->capacity == 0)
                           ? SAFE_ARRAY_INIT_CAPACITY
                           : arr->capacity * SAFE_ARRAY_GROWTH_FACTOR;

        // 安全模式：用临时指针接收 realloc 的返回值
        int *tmp = (int *)realloc(arr->data, new_capacity * sizeof(int));
        if (tmp == NULL) {
            // realloc 失败：原内存块 arr->data 仍然有效，数据未丢失
            printf("  ERROR: realloc failed. Cannot append value %d.\n", value);
            return 0;   // 返回失败，调用者可继续使用旧数组
        }

        // 扩容成功：更新指针和容量
        arr->data     = tmp;
        arr->capacity = new_capacity;
    }

    // 2. 将新元素存入数组末尾，计数器加 1
    arr->data[arr->count] = value;
    arr->count++;

    return 1;   // 成功
}

// ========== 销毁数组 ==========
/*
 * array_destroy:
 *   释放 data 指向的堆内存，并将所有字段归零。
 *   特别之处：free 后将 data 置为 NULL，防止悬空指针。
 *   此函数可以安全地重复调用（因为 free(NULL) 是安全的）。
 */
void array_destroy(SafeIntArray *arr)
{
    free(arr->data);         // 即使 data 为 NULL 也安全
    arr->data     = NULL;    // ★ 关键：free 后立即置 NULL
    arr->count    = 0;
    arr->capacity = 0;
}

// ========== 安全读取 ==========
/*
 * array_get:
 *   读取第 index 个元素（索引从 0 开始）。
 *   若 index 越界，打印错误信息并退出程序。
 *   这是防御性编程：比返回一个"错误值"更安全，
 *   因为它迫使调用者必须传入合法索引。
 */
int array_get(const SafeIntArray *arr, int index)
{
    if (index < 0 || index >= arr->count) {
        printf("  ERROR: array_get index %d out of range [0, %d).\n",
               index, arr->count);
        exit(1);
    }
    return arr->data[index];
}

// ========== 获取大小 ==========
int array_size(const SafeIntArray *arr)
{
    return arr->count;
}

// ========== 打印所有元素 ==========
void array_print(const SafeIntArray *arr)
{
    if (arr->count == 0) {
        printf("  (empty)\n");
        return;
    }
    printf("  [");
    for (int i = 0; i < arr->count; i++) {
        printf("%d", arr->data[i]);
        if (i < arr->count - 1) printf(", ");
    }
    printf("]  (count=%d, capacity=%d)\n", arr->count, arr->capacity);
}