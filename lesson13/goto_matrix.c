#include <stdio.h>

int main(void) {
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int target = 5;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == target) {
                printf("Found %d at row %d, col %d\n", target, i, j);
                goto done;   // 直接跳出双循环
            }
        }
    }
    printf("Not found.\n");

done:
    return 0;
}