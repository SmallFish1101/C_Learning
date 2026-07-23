/*
 * version.c
 * 第21课 练习二：条件编译实现版本号管理
 *
 * 功能：定义主次版本号，通过是否定义 BETA 宏来控制显示"beta"标记。
 *       编译时可通过 -DBETA 来定义该宏，生成测试版程序。
 */

#include <stdio.h>

// ========== 版本号定义（可在源码中自由修改）==========
#define VERSION_MAJOR 1
#define VERSION_MINOR 0

int main(void)
{
    printf("=== Version Display ===\n");

    // 打印版本号（主.次）
    printf("Version %d.%d", VERSION_MAJOR, VERSION_MINOR);

    // 检查是否定义了 BETA 宏
#ifdef BETA
    printf(" beta");          // 测试版附加标记
#endif

    printf("\n");

    // 额外提示
#ifdef BETA
    printf("This is a BETA version. Use with caution.\n");
#else
    printf("This is a stable release.\n");
#endif

    return 0;
}