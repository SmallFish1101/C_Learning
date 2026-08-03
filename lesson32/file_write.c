#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp = fopen("output.txt", "w");
    if (fp == NULL) {
        printf("Error: cannot open output.txt for writing.\n");
        return 1;
    }

    // 逐行写入
    fprintf(fp, "=== Student Records ===\n");
    fprintf(fp, "Name: %s, Age: %d, Score: %.1f\n", "Alice", 20, 92.5f);
    fprintf(fp, "Name: %s, Age: %d, Score: %.1f\n", "Bob",   21, 85.0f);

    fclose(fp);
    printf("Data written to output.txt\n");
    return 0;
}