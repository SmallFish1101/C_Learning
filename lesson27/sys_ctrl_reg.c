/*
 * sys_ctrl_reg.c
 * 第27课 练习二：用位域定义 32 位系统控制寄存器
 *
 * 字段布局（GCC 小端模式，先定义的字段占低地址低位）：
 *   clock_div : 4 位  (bit 0~3)
 *   reset     : 1 位  (bit 4)
 *   boot_mode : 2 位  (bit 5~6)
 *   reserved  : 25 位 (bit 7~31)
 */

#include <stdio.h>   // printf, putchar
#include <stdint.h>  // uint32_t
#include <stddef.h>  // offsetof（验证用）
#include <string.h>  // memset（清零用）

// ========== 位域结构体（紧凑布局）==========
/*
 * SysCtrlBits:
 *   精确映射 32 位寄存器中每个字段的位宽。
 *   __attribute__((packed)) 确保编译器不插入额外填充。
 */
typedef struct __attribute__((packed)) {
    uint32_t clock_div : 4;    // bit 0~3：时钟分频器
    uint32_t reset     : 1;    // bit 4  ：复位控制
    uint32_t boot_mode : 2;    // bit 5~6：启动模式
    uint32_t           : 25;   // bit 7~31：保留未用（无名位域，不可访问）
} SysCtrlBits;

// ========== 联合体：整体与字段双视角 ==========
typedef union {
    SysCtrlBits bits;   // 按位域逐字段读写
    uint32_t    raw;    // 按 32 位整体读写
} SysCtrlReg;

// ========== 辅助函数：打印 32 位二进制 ==========
/*
 * print_binary32:
 *   以二进制形式打印 32 位值，并标注字段分界线。
 *   每次打印 4 位，字段之间加竖线分隔。
 */
void print_binary32(uint32_t val)
{
    for (int i = 31; i >= 0; i--)
    {
        putchar(((val >> i) & 1U) ? '1' : '0');

        // 在字段分界处添加竖线
        if (i == 7 || i == 6 || i == 4 || i == 0) {
            putchar(' ');
        }
    }
    printf("\n");

    // 字段标注
    printf("  |  reserved (25b)         |BM|R|CDIV|\n");
    printf("  bit 31..7                65 4 3..0\n");
}

// ========== 启动模式枚举 ==========
typedef enum {
    BOOT_FLASH = 0,   // 从 Flash 启动
    BOOT_RAM   = 1,   // 从 RAM 启动
    BOOT_ISP   = 2,   // ISP 烧录模式
    BOOT_RSVD  = 3    // 保留
} BootMode;

// ========== 主函数 ==========
int main(void)
{
    printf("=== 32-bit System Control Register ===\n\n");

    // ---------- 测试 1：整体写入，字段读取 ----------
    printf("--- Test 1: Write raw value, read back fields ---\n");

    SysCtrlReg reg1;
    memset(&reg1, 0, sizeof(reg1));   // 清零所有位

    // 手动构造一个已知的 32 位值：
    //   clock_div = 5 (0b0101) → bit 0~3 = 0101
    //   reset     = 1          → bit 4   = 1
    //   boot_mode = 2 (ISP)    → bit 5~6 = 10
    //   reserved  = 0xABCDEF   → bit 7~31（任意非零值）
    uint32_t test_val =
        (0xABCDEFU << 7) |    // reserved  = 0xABCDEF，移到 bit 7 开始
        (2U         << 5) |    // boot_mode = 2 (ISP)，移到 bit 5
        (1U         << 4) |    // reset     = 1，        移到 bit 4
        (5U         << 0);     // clock_div = 5，        移到 bit 0

    reg1.raw = test_val;

    printf("Raw value: 0x%08X\n", reg1.raw);
    printf("Binary   : ");
    print_binary32(reg1.raw);

    // 从位域读回各字段
    printf("\nFields (read from bitfields):\n");
    printf("  clock_div = %u (expected 5)\n",  reg1.bits.clock_div);
    printf("  reset     = %u (expected 1)\n",  reg1.bits.reset);
    printf("  boot_mode = %u (expected 2, ISP)\n", reg1.bits.boot_mode);
    printf("\n");

    // ---------- 测试 2：字段写入，整体读取 ----------
    printf("--- Test 2: Write via bitfields, read raw ---\n");

    SysCtrlReg reg2;
    reg2.raw = 0x00000000;    // 清零

    reg2.bits.clock_div = 10;       // 设置分频器为 10
    reg2.bits.boot_mode = BOOT_RAM; // 设置启动模式为 RAM (1)
    reg2.bits.reset     = 0;        // 确保复位位为 0

    printf("Raw value after field writes: 0x%08X\n", reg2.raw);
    printf("Binary                     : ");
    print_binary32(reg2.raw);

    // 预期：clock_div=10 (1010), reset=0, boot_mode=1 (01)
    // raw = (10 << 0) | (0 << 4) | (1 << 5) = 10 + 0 + 32 = 42 = 0x2A
    printf("Expected raw: 0x%08X (decimal %d)\n", 0x2AU, 42);
    printf("Match: %s\n\n", (reg2.raw == 0x2AU) ? "YES" : "NO");

    // ---------- 测试 3：保留位应被忽略 ----------
    printf("--- Test 3: Reserved bits behavior ---\n");

    SysCtrlReg reg3;
    memset(&reg3, 0, sizeof(reg3));

    // 直接通过 raw 写入一个值，其中保留位非零
    reg3.raw = 0xFFFF80FFU;   // 保留位大量为 1
    printf("Before field write: raw = 0x%08X\n", reg3.raw);

    // 通过字段修改 clock_div（只影响 bit 0~3）
    reg3.bits.clock_div = 3;

    // 读取 raw 时，保留位的内容仍然存在！
    // 这是预期行为：你没有修改它们，它们就保持原样
    printf("After  field write: raw = 0x%08X\n", reg3.raw);
    printf("  clock_div = %u\n", reg3.bits.clock_div);
    printf("  (reserved bits are preserved when writing other fields)\n\n");

    // ---------- 验证结构体大小 ----------
    printf("=== Verification ===\n");
    printf("sizeof(SysCtrlReg) = %zu (expected 4)\n", sizeof(SysCtrlReg));

    return 0;
}