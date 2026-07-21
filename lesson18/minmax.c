#include <stdio.h>

// 同时返回数组的最大值和最小值
void find_minmax(int arr[], int size, int *max, int *min) {
    *max = *min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > *max) *max = arr[i];
        if (arr[i] < *min) *min = arr[i];
    }
}

int main(void) {
    int data[] = {5, 2, 8, 1, 9};
    int n = sizeof(data) / sizeof(data[0]);
    int max_val, min_val;

    find_minmax(data, n, &max_val, &min_val);
    printf("Max: %d, Min: %d\n", max_val, min_val);
    return 0;
}