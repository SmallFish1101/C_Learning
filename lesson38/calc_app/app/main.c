#include <stdio.h>
#include <stdlib.h>    // exit
#include <string.h>    // strlen
#include "calc_parser.h"

#define MAX_LINE 256

int main(void)
{
    char line[MAX_LINE];

    printf("=== Expression Calculator ===\n");
    printf("Supported: + - * / %% ( ) decimals negative\n");
    printf("Examples: (2+3)*4   -5+10   3.14*2\n");
    printf("Type 'q' or 'quit' to exit.\n\n");

    while (1)
    {
        printf("> ");
        if (fgets(line, sizeof(line), stdin) == NULL) break;

        // 去除末尾换行符
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        // 退出命令
        if (strcmp(line, "q") == 0 || strcmp(line, "quit") == 0)
            break;

        // 跳过空行
        if (line[0] == '\0') continue;

        double result;
        if (evaluate_expression(line, &result))
        {
            printf("  = %.2f\n\n", result);
        }
        else
        {
            printf("  Error: invalid expression.\n\n");
        }
    }

    printf("Goodbye!\n");
    return 0;
}