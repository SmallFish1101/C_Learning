/*
 * endian_check.c
 * 第27课 练习一：用联合体检测系统的字节序（大小端）
 *
 * 原理：将一个已知的 32 位整数写入联合体，
 *       再逐字节读出，观察最低地址处存储的是最高字节还是最低字节。
 */

#include <stdio.h>   // printf
#include <stdint.h>  // uint32_t, uint8_t

// 联合体：32 位整体和 4 字节数组共享同一块内存
typedef union {
    uint32_t word;       // 按 32 位无符号整数解释
    uint8_t  bytes[4];   // 按 4 个独立字节解释
} EndianChecker;

int main(void)
{
    EndianChecker checker;

    // 写入一个已知的测试值，其每字节内容互不相同：0x12, 0x34, 0x56, 0x78
    checker.word = 0x12345678;

    printf("=== Endianness Check ===\n\n");
    printf("Test value: 0x12345678\n\n");

    // 逐字节打印内存中的存储顺序
    printf("Memory layout (low address -> high address):\n");
    for (int i = 0; i < 4; i++) {
        printf("  bytes[%d] = 0x%02X\n", i, checker.bytes[i]);
    }

    printf("\n");

    // 判断大小端：
    //   小端（Little-Endian）：低地址存放最低有效字节（0x78）
    //   大端（Big-Endian）   ：低地址存放最高有效字节（0x12）
    if (checker.bytes[0] == 0x78) {
        printf("Result: This system is LITTLE-ENDIAN.\n");
        printf("(x86, x64, and most ARM processors are little-endian.)\n");
    } else if (checker.bytes[0] == 0x12) {
        printf("Result: This system is BIG-ENDIAN.\n");
        printf("(Some network processors and older Macs use big-endian.)\n");
    } else {
        printf("Result: UNKNOWN endianness.\n");
    }

    // ========== 分析注释 ==========
    /*
     * 为什么网络协议（如 TCP/IP）需要显式规定字节序？
     *
     * 不同的 CPU 架构可能使用不同的字节序：
     *   - x86 / ARM（大多数）  : 小端（低地址存低字节）
     *   - 部分 PowerPC / 旧 Mac : 大端（低地址存高字节）
     *
     * 当两台不同端序的计算机通过网络交换一个多字节整数
     * （如端口号 0x1234）时，如果不规定统一格式：
     *   - 小端机发送的字节流：0x34, 0x12
     *   - 大端机接收到后按本地端序解读：0x3412（错误！）
     *
     * 为了解决这个问题，TCP/IP 协议强制规定：
     *   - 网络字节序 = 大端（Big-Endian）
     *   - 发送前，小端机必须用 htons() / htonl() 将整数转为网络序
     *   - 接收后，小端机必须用 ntohs() / ntohl() 转回本地序
     *
     * 因此，理解大小端是编写跨平台通信代码的基础。
     */

    return 0;
}