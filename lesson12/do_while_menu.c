#include <stdio.h>

int main(void) {
    int choice;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Say hello\n");
        printf("2. Say goodbye\n");
        printf("3. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: printf("Hello!\n"); break;
            case 2: printf("Goodbye!\n"); break;
            case 3: printf("Exiting...\n"); break;
            default: printf("Invalid.\n");
        }
    } while (choice != 3);

    return 0;
}