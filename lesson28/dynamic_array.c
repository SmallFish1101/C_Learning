#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int capacity = 2;   // 初始容量
    int count = 0;
    int *arr = (int *)malloc(capacity * sizeof(int));

    if (arr == NULL) {
        printf("Initial allocation failed.\n");
        return 1;
    }

    printf("Enter numbers (0 to stop):\n");
    int num;
    while (1) {
        printf("> ");
        scanf("%d", &num);
        if (num == 0) break;

        // 如果数组已满，扩容两倍
        if (count >= capacity) {
            int new_capacity = capacity * 2;
            int *tmp = (int *)realloc(arr, new_capacity * sizeof(int));
            if (tmp == NULL) {
                printf("Realloc failed. Keeping current data.\n");
                break;
            }
            arr = tmp;
            capacity = new_capacity;
            printf("  (expanded to %d)\n", capacity);
        }

        arr[count++] = num;
    }

    printf("\nYou entered %d numbers: ", count);
    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}