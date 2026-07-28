/*
 * can_frame_packed.c
 * 第25课 练习三（选做）：用紧凑结构体 + 位域模拟 CAN 标准帧
 *
 * 验证 packed 结构体无填充，演示如何通过指针整体读写报文。
 */

#include <stdio.h>   // printf, putchar
#include <stdint.h>  // uint16_t, uint32_t, uint64_t, uint8_t
#include <stddef.h>  // offsetof
#include <string.h>  // memcmp

// ========== 紧凑 CAN 标准帧结构体 ==========
/*
 * CAN_Frame:
 *   用位域描述 ID, RTR, DLC，加 8 字节数据。
 *   __attribute__((packed)) 确保无填充。
 *
 *   GCC 小端位域分配规则：
 *     先定义的字段占据低地址的低位。
 *     因此 ID 占 bit 0~10, RTR 占 bit 11, DLC 占 bit 12~15。
 */
typedef struct __attribute__((packed)) {
    uint32_t id    : 11;   // 标识符（bit 0 ~ 10）
    uint32_t rtr   : 1;    // 远程请求（bit 11）
    uint32_t dlc   : 4;    // 数据长度（bit 12 ~ 15）
    uint8_t  data[8];      // 载荷（字节 2 ~ 9）
} CAN_Frame;

// ========== 辅助函数：打印 16 位二进制 ==========
void print_binary16(uint16_t val, const char *label)
{
    printf("%s: ", label);
    for (int i = 15; i >= 0; i--)
    {
        putchar(((val >> i) & 1U) ? '1' : '0');
        if (i == 12 || i == 11) putchar(' ');   // 分隔 ID / RTR / DLC
    }
    printf("\n");
}

int main(void)
{
    printf("=== CAN Frame with Packed Struct & Bitfields ===\n\n");

    // ===== 1. 验证结构体大小 =====
    printf("sizeof(CAN_Frame) = %zu bytes\n", sizeof(CAN_Frame));
    printf("  (expected: 10 = 2-byte header + 8-byte data)\n\n");

    // ===== 2. 查看各字段偏移 =====
    /*printf("Offsets:\n");
    printf("  offset of id   : %zu\n", offsetof(CAN_Frame, id));
    printf("  offset of rtr  : %zu\n", offsetof(CAN_Frame, rtr));
    printf("  offset of dlc  : %zu\n", offsetof(CAN_Frame, dlc));
    printf("  offset of data : %zu\n", offsetof(CAN_Frame, data));
    printf("  (id, rtr, dlc share offset 0 due to bitfield)\n\n");
    */
   
    // ===== 3. 创建并填充一个 CAN 帧 =====
    CAN_Frame frame;
    // 将所有字节清零，确保没有残留值干扰
    memset(&frame, 0, sizeof(frame));

    frame.id  = 0x5A3;    // ID = 1443 (二进制 101 1010 0011)
    frame.rtr = 1;        // 远程帧
    frame.dlc = 4;        // 数据长度 = 4 字节有效

    // 填充载荷（只使用前 4 字节，后 4 字节保持 0）
    frame.data[0] = 0xDE;
    frame.data[1] = 0xAD;
    frame.data[2] = 0xBE;
    frame.data[3] = 0xEF;

    // ===== 4. 用字段方式读回并打印 =====
    printf("Frame content (by fields):\n");
    printf("  ID  = 0x%03X (%u)\n", frame.id, frame.id);
    printf("  RTR = %u (%s)\n", frame.rtr, frame.rtr ? "Remote" : "Data");
    printf("  DLC = %u (%u bytes)\n", frame.dlc, frame.dlc);
    printf("  Data: ");
    for (int i = 0; i < frame.dlc; i++)
        printf("0x%02X ", frame.data[i]);
    printf("\n\n");

    // ===== 5. 用指针整体读出头部（模拟硬件接收） =====
    // 将结构体首地址解释为指向 uint16_t 的指针
    uint16_t raw_header = *(uint16_t*)&frame;

    print_binary16(raw_header, "Raw header (16-bit)");

    // 从 raw_header 中提取字段，与字段读取结果对比
    uint16_t extracted_id  = (raw_header >> 0) & 0x7FF;   // 低 11 位
    uint16_t extracted_rtr = (raw_header >> 11) & 0x1;    // 第 11 位
    uint16_t extracted_dlc = (raw_header >> 12) & 0xF;    // 高 4 位

    printf("  ID  (extracted): 0x%03X (%u)  %s\n",
           extracted_id, extracted_id,
           extracted_id == frame.id ? "(match)" : "(MISMATCH!)");
    printf("  RTR (extracted): %u  %s\n",
           extracted_rtr, extracted_rtr == frame.rtr ? "(match)" : "(MISMATCH!)");
    printf("  DLC (extracted): %u  %s\n",
           extracted_dlc, extracted_dlc == frame.dlc ? "(match)" : "(MISMATCH!)");

    // ===== 6. 整体读出 8 字节载荷（用 uint64_t 指针） =====
    uint64_t raw_data = *(uint64_t*)frame.data;
    printf("\nRaw data (uint64_t): 0x%016llX\n", (unsigned long long)raw_data);
    printf("Expected:             0x%02X%02X%02X%02X%02X%02X%02X%02X\n",
           frame.data[7], frame.data[6], frame.data[5], frame.data[4],
           frame.data[3], frame.data[2], frame.data[1], frame.data[0]);

    // 用 memcmp 精确校验
    if (memcmp(frame.data, &raw_data, 8) == 0)
        printf("Data matches (verified by memcmp).\n");
    else
        printf("Data MISMATCH!\n");

    printf("\n=== Done ===\n");
    return 0;
}