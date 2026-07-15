#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *f1 = NULL, *f2 = NULL;
    char *buffer = NULL;

    f1 = fopen("input.txt", "r");
    if (!f1) goto cleanup;

    buffer = (char*)malloc(1024);
    if (!buffer) goto cleanup;

    f2 = fopen("output.txt", "w");
    if (!f2) goto cleanup;

    // 在这儿读写数据...

cleanup:
    if (f1) fclose(f1);
    if (f2) fclose(f2);
    free(buffer);
    return 0;
}