/*
 * main.c
 * 学生成绩管理系统 —— 主程序和菜单
 *
 * 本文件只依赖 student.h，完全不接触 StudentManager 内部细节。
 */

#include "../include/student.h"
#include "../include/utils.h"

// 前向声明（具体实现在文件末尾）
void print_menu(void);
void print_sort_submenu(void);
void handle_sort(StudentManager *mgr);

int main(void)
{
    StudentManager mgr;
    manager_init(&mgr);

    printf("=== Student Grade Management System ===\n");
    printf("Welcome! Manage student records efficiently.\n");

    int running = 1;
    while (running)
    {
        print_menu();

        int choice = read_int("Your choice: ");

        switch (choice)
        {
            case MENU_ADD:    manager_add_student(&mgr);    break;
            case MENU_DELETE: manager_delete_student(&mgr);  break;
            case MENU_MODIFY: manager_modify_student(&mgr);  break;
            case MENU_FIND_ID:
                {
                    int id = read_int("  Enter student ID: ");
                    int idx = manager_find_by_id(&mgr, id);
                    if (idx != -1) {
                        Student *s = &mgr.students[idx];
                        printf("  Found: %d %s  C:%d M:%d E:%d  Total:%d Avg:%.1f\n",
                               s->id, s->name, s->chinese, s->math, s->english,
                               s->total, s->average);
                    } else {
                        printf("  Student with ID %d not found.\n", id);
                    }
                }
                break;
            case MENU_FIND_NAME:
                {
                    char name[NAME_LEN];
                    printf("  Enter name (or prefix): ");
                    safe_read_line(name, NAME_LEN);
                    manager_find_by_name(&mgr, name);
                }
                break;
            case MENU_STATS:  manager_show_stats(&mgr);      break;
            case MENU_SORT:   handle_sort(&mgr);             break;
            case MENU_LIST:   manager_list_students(&mgr);   break;
            case MENU_SAVE:
                {
                    char filename[100];
                    printf("  Filename to save: ");
                    safe_read_line(filename, sizeof(filename));
                    manager_save_to_file(&mgr, filename);
                }
                break;
            case MENU_LOAD:
                {
                    char filename[100];
                    printf("  Filename to load: ");
                    safe_read_line(filename, sizeof(filename));
                    manager_load_from_file(&mgr, filename);
                }
                break;
            case MENU_EXIT:
                printf("Goodbye!\n");
                running = 0;
                break;
            default:
                printf("Invalid choice. Please enter 1-11.\n");
        }
    }

    manager_destroy(&mgr);
    return 0;
}

void print_menu(void)
{
    printf("\n========================================\n");
    printf("  Student Grade Management System\n");
    printf("========================================\n");
    printf("  1.  Add student\n");
    printf("  2.  Delete student\n");
    printf("  3.  Modify student\n");
    printf("  4.  Find by ID\n");
    printf("  5.  Find by name\n");
    printf("  6.  Show statistics\n");
    printf("  7.  Sort records\n");
    printf("  8.  List all students\n");
    printf("  9.  Save to file\n");
    printf(" 10.  Load from file\n");
    printf(" 11.  Exit\n");
    printf("----------------------------------------\n");
}

void print_sort_submenu(void)
{
    printf("\n  Sort by:\n");
    printf("  1. ID (ascending)\n");
    printf("  2. Total score (descending, with ranking)\n");
    printf("  3. Chinese (descending)\n");
    printf("  4. Math (descending)\n");
    printf("  5. English (descending)\n");
    printf("  0. Cancel\n");
}

void handle_sort(StudentManager *mgr)
{
    print_sort_submenu();
    int sort_choice = read_int("  Your choice: ");

    SortMethod method;
    switch (sort_choice) {
        case 1: method = SORT_BY_ID_ASC;        break;
        case 2: method = SORT_BY_TOTAL_DESC;    break;
        case 3: method = SORT_BY_CHINESE_DESC;  break;
        case 4: method = SORT_BY_MATH_DESC;     break;
        case 5: method = SORT_BY_ENGLISH_DESC;  break;
        case 0: return;
        default:
            printf("  Invalid sort choice.\n");
            return;
    }

    manager_sort(mgr, method);
    printf("  Sorting done.\n");
}