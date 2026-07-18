/*
 * leaderboard.c
 * 第14课 作业三（选做·游戏方向）：简单排行榜
 *
 * 功能：维护一个 Top 5 排行榜，支持预置数据、降序排序、
 *       输入新分数并判断是否能上榜（高于最低分则替换并重排）。
 */

#include <stdio.h>    // printf, fgets, sscanf
#include <stdlib.h>   // exit
#include <stdbool.h>  // bool, true, false

#define TOP_N 5   // 排行榜容量

/*
 * read_int:
 *   安全读取一个整数（与前几课完全相同的标准模板）。
 *   prompt: 提示信息。
 *   return: 用户输入的合法整数。
 */
int read_int(const char *prompt)
{
    char line[100];

    while (1) {
        printf("%s", prompt);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nEnd of input.\n");
            exit(0);
        }

        int value;
        int pos = 0;
        int matched = sscanf(line, "%d %n", &value, &pos);

        if (matched != 1) {
            printf("  ERROR: Please enter a valid integer.\n");
            continue;
        }
        if (line[pos] != '\0') {
            printf("  ERROR: Extra characters after number.\n");
            continue;
        }

        return value;
    }
}

/*
 * ask_continue:
 *   询问用户是否继续。
 *   return: true 继续，false 退出。
 */
bool ask_continue(void)
{
    char line[100];

    while (1) {
        printf("\nContinue? (y/n): ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            return false;   // EOF，默认退出
        }

        // 去掉换行符
        int len = 0;
        while (line[len] != '\0' && line[len] != '\n') len++;
        if (line[len] == '\n') line[len] = '\0';

        if (len == 1) {
            if (line[0] == 'y' || line[0] == 'Y') return true;
            if (line[0] == 'n' || line[0] == 'N') return false;
        }

        printf("  Please enter 'y' or 'n'.\n");
    }
}

/*
 * sort_descending:
 *   使用冒泡排序对数组进行降序排列（从大到小）。
 *   arr:  待排序的数组
 *   size: 数组元素个数
 *
 *   原理：重复比较相邻元素，如果前面的比后面的小，就交换。
 *         每轮比较后，最小的元素会“沉”到末尾。
 */
void sort_descending(int arr[], int size)
{
    // 外层循环：控制排序趟数（共 size-1 趟）
    for (int pass = 0; pass < size - 1; pass++) {

        // 标记本轮是否有交换，若没有则说明已有序，可提前退出
        bool swapped = false;

        // 内层循环：比较相邻元素，最后 pass 个元素已排好
        for (int j = 0; j < size - 1 - pass; j++) {
            if (arr[j] < arr[j + 1]) {   // 降序：左 < 右时交换
                // 三步交换
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                swapped = true;   // 发生了交换
            }
        }

        // 如果本轮没有发生交换，说明数组已完全有序，提前结束
        if (!swapped) {
            break;
        }
    }
}

/*
 * print_leaderboard:
 *   打印排行榜。
 *   arr:  排行榜数组
 *   size: 排行榜元素个数
 */
void print_leaderboard(int arr[], int size)
{
    printf("\n=== Top %d Leaderboard ===\n", size);
    printf("------------------------\n");
    printf(" Rank | Score\n");
    printf("------+-------\n");

    for (int i = 0; i < size; i++) {
        // %3d 确保排名右对齐，%5d 确保分数右对齐
        printf("  %2d  | %5d\n", i + 1, arr[i]);
    }
    printf("------------------------\n");
}

int main(void)
{
    printf("=== Game Leaderboard System ===\n\n");

    // 1. 初始化排行榜（预置数据）
    int leaderboard[TOP_N] = {100, 85, 90, 70, 95};

    // 2. 先排一次序，让初始排行榜降序显示
    sort_descending(leaderboard, TOP_N);

    bool running = true;

    while (running) {
        // 3. 显示当前排行榜
        print_leaderboard(leaderboard, TOP_N);

        // 4. 用户输入新分数
        int new_score = read_int("Enter your score: ");

        // 5. 判断能否上榜：新分数必须大于最后一名（最低分）
        //    因为排行榜已降序排列，leaderboard[TOP_N-1] 是最低分
        if (new_score > leaderboard[TOP_N - 1]) {
            printf("  Congratulations! You made it to the Top %d!\n", TOP_N);

            // 替换最低分
            leaderboard[TOP_N - 1] = new_score;

            // 重新排序（因为新分数可能排在任何位置）
            sort_descending(leaderboard, TOP_N);

            // 显示更新后的排行榜
            print_leaderboard(leaderboard, TOP_N);
        } else {
            printf("  Sorry, your score did not make it to the Top %d.\n", TOP_N);
        }

        // 6. 询问是否继续
        running = ask_continue();
    }

    printf("\nFinal Leaderboard:\n");
    print_leaderboard(leaderboard, TOP_N);
    printf("\nThanks for playing!\n");

    return 0;
}