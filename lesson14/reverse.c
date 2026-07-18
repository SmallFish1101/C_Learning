/*
 * reverse.c
 * 第14课 练习一：数组反转（原地操作）
 *
 * 功能：安全读取 N 个整数存入数组，
 *       不借助第二个数组，将原数组反转（首尾交换），
 *       输出反转前后的数组内容。
 */

#include <stdio.h>   // printf, fgets, sscanf
#include <stdlib.h>  // exit

#define ARRAY_SIZE 6   // 数组大小，修改此处即可改变数组长度

/*
 * read_int:
 *   安全读取一个整数（标准模板，与前几课一致）。
 *   return: 用户输入的合法整数。
 */
int read_int(void)
{
    char line[100];

    while (1) {
        printf("Enter an integer: ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nEnd of input.\n");
            exit(0);
        }

        int value;
        int pos = 0;
        int matched = sscanf(line, "%d %n", &value, &pos);

        if (matched != 1) {
            printf("  ERROR: Please enter a valid integer.\n");
            continue;
        }
        if (line[pos] != '\0') {
            printf("  ERROR: Extra characters after number.\n");
            continue;
        }

        return value;
    }
}

/*
 * print_array:
 *   打印数组所有元素，用空格分隔。
 *   arr:  数组首地址
 *   size: 数组元素个数
 */
void print_array(int arr[], int size)
{
    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");   // 元素之间加逗号，便于阅读
        }
    }
    printf(" ]\n");
}

/*
 * reverse_array:
 *   原地反转数组（不创建新数组）。
 *   arr:  数组首地址
 *   size: 数组元素个数
 *
 *   原理：双索引法，i 从头向后，j 从尾向前，交换对应元素。
 */
void reverse_array(int arr[], int size)
{
    for (int i = 0, j = size - 1; i < j; i++, j--) {
        // 经典的三步交换（需要临时变量）
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int main(void)
{
    int arr[ARRAY_SIZE];   // 定义数组，大小由宏控制

    printf("=== Array Reversal ===\n");
    printf("Please enter %d integers.\n\n", ARRAY_SIZE);

    // 1. 录入数组元素
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("Element [%d]: ", i);
        arr[i] = read_int();
    }

    // 2. 打印原始数组
    printf("\nOriginal array:\n");
    print_array(arr, ARRAY_SIZE);

    // 3. 反转数组（原地操作，不申请新空间）
    reverse_array(arr, ARRAY_SIZE);

    // 4. 打印反转后的数组
    printf("\nReversed array:\n");
    print_array(arr, ARRAY_SIZE);

    // 5. 验证反转是否正确（再反转一次应该回到原始）
    reverse_array(arr, ARRAY_SIZE);
    printf("\nAfter reversing again (should be original):\n");
    print_array(arr, ARRAY_SIZE);

    return 0;
}