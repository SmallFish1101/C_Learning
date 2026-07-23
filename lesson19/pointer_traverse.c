#include <stdio.h>

int main(void) {
    double temps[] = {36.5, 36.7, 36.8, 37.0, 37.2};
    int n = sizeof(temps) / sizeof(temps[0]);

    printf("=== Using pointer increment ===\n");
    for (double *p = temps; p < temps + n; p++) {
        printf("%.1f ", *p);
    }
    printf("\n");
    return 0;
}