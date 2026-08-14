/*
 * spi_sim.h
 * 模拟 SPI 写入接口（用终端打印代替真实硬件引脚操作）
 */

#ifndef SPI_SIM_H
#define SPI_SIM_H

#include <stdint.h>
#include <stdbool.h>

/*
 * spi_sim_send:
 *   模拟发送一个字节。真实硬件上这里会是 GPIO 引脚操作。
 *   本实现：把字节以二进制形式打印出来，模拟"数据在线上传输"。
 */
void spi_sim_send(uint8_t byte);

/*
 * spi_sim_send_row:
 *   模拟向 MAX7219 发送一行数据。
 *   参数 row : 行号（0~7，内部会 +1 变成寄存器地址 1~8）
 *   参数 data: 该行的 8 位数据（1=亮，0=灭）
 */
void spi_sim_send_row(uint8_t row, uint8_t data);

#endif // SPI_SIM_H