#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *input = NULL, *output = NULL;

    input = fopen("source.txt", "r");
    if (input == NULL) goto error;

    output = fopen("dest.txt", "w");
    if (output == NULL) goto error;

    // 正常操作：复制文件内容
    char line[256];
    while (fgets(line, sizeof(line), input) != NULL) {
        fputs(line, output);
    }

    printf("File copied successfully.\n");
    fclose(input);
    fclose(output);
    return 0;

error:
    printf("Error: file operation failed.\n");
    if (input)  fclose(input);
    if (output) fclose(output);
    return 1;
}