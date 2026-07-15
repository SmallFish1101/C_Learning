/*
 * guess_number.c
 * 第12课 练习二：猜数字游戏
 *
 * 程序生成 1~100 的随机数，用户每次猜测后反馈大小，
 * 直至猜中。支持多次游戏和放弃本局功能。
 */

#include <stdio.h>    // printf, fgets, sscanf
#include <stdlib.h>   // rand, srand, exit
#include <time.h>     // time
#include <string.h>   // strlen

/*
 * read_guess:
 *   安全读取一个整数猜测（1~100），或返回 -1 表示放弃。
 *   return: 用户输入的合法整数（1~100 或 -1）。
 */
int read_guess(void)
{
    char line[100];

    while (1) {
        printf("Enter your guess (1-100, or -1 to give up): ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nEnd of input.\n");
            exit(0);
        }

        int guess;
        int pos = 0;
        int matched = sscanf(line, "%d %n", &guess, &pos);

        if (matched != 1) {
            printf("  ERROR: Please enter an integer.\n");
            continue;
        }
        if (line[pos] != '\0') {
            printf("  ERROR: Extra characters after number.\n");
            continue;
        }

        // 允许 -1 表示放弃，或 1~100 之间的有效猜测
        if (guess == -1 || (guess >= 1 && guess <= 100)) {
            return guess;
        } else {
            printf("  ERROR: Guess must be between 1 and 100 (or -1 to quit).\n");
        }
    }
}

/*
 * ask_replay:
 *   询问用户是否再玩一局。
 *   return: 1 表示再来一局，0 表示退出。
 */
int ask_replay(void)
{
    char line[100];

    while (1) {
        printf("\nWould you like to play again? (y/n): ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            return 0;   // EOF，默认不再玩
        }

        // 去掉换行符
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        if (len == 1 && (line[0] == 'y' || line[0] == 'Y')) {
            return 1;
        }
        if (len == 1 && (line[0] == 'n' || line[0] == 'N')) {
            return 0;
        }

        printf("  Please enter 'y' or 'n'.\n");
    }
}

int main(void)
{
    // 用当前时间初始化随机数种子（仅需一次）
    srand((unsigned)time(NULL));

    printf("=== Guess the Number Game ===\n");
    printf("I have chosen a number between 1 and 100.\n");
    printf("You can give up any time by entering -1.\n\n");

    int play_again = 1;   // 控制外层循环

    while (play_again) {
        // 生成本局秘密数字
        int secret = 1 + rand() % 100;   // 1..100
        int attempts = 0;                // 猜测次数
        int guessed = 0;                 // 是否猜中标志

        printf("--- New round started! ---\n");

        // 内层循环：单局猜数
        while (!guessed) {
            int guess = read_guess();

            if (guess == -1) {
                printf("You gave up! The secret number was %d.\n", secret);
                break;   // 放弃本局，跳出内层循环
            }

            attempts++;

            if (guess < secret) {
                printf("  Too low! Try again.\n");
            } else if (guess > secret) {
                printf("  Too high! Try again.\n");
            } else {
                printf("  Congratulations! You guessed the number %d in %d attempt(s).\n",
                       secret, attempts);
                guessed = 1;   // 跳出内层循环
            }
        }

        // 询问是否再来一局
        play_again = ask_replay();
    }

    printf("Thanks for playing! Goodbye.\n");
    return 0;
}