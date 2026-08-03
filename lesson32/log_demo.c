#include <stdio.h>
#include <time.h>

// 获取当前时间字符串
const char *now_str(void) {
    static char buf[64];
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm);
    return buf;
}

int main(void) {
    FILE *fp = fopen("app.log", "a");   // 追加模式，不覆盖旧日志
    if (fp == NULL) return 1;

    fprintf(fp, "[%s] Application started.\n", now_str());
    fprintf(fp, "[%s] Processing data...\n", now_str());
    fprintf(fp, "[%s] Application finished.\n", now_str());

    fclose(fp);
    printf("Log written to app.log\n");
    return 0;
}