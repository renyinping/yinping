#include "uart.h"
#include <reg52.h>
#include "config.h"


sfr AUXR = 0x8E;   /* 0000,0000 STC15-MCU 辅助寄存器 */


/* 串口波特率发生器或定时器初值 */
#if UART_SPEED > 0
#define UART_BRT (256-(unsigned char)(((float)UART_CLOCK)/16/(UART_RATE)+0.5))
#else
#define UART_BRT (256-(unsigned char)(((float)UART_CLOCK)/32/(UART_RATE)+0.5))
#endif


/* 串口参数 */
#if defined UART_CFG_CODE && UART_CFG_CODE > 0
code UART_CFG uart_cfg =
{
    UART_RATE,
    UART_CLOCK,
    UART_SPEED,
    UART_BRT
};
#endif /* UART_CFG_CODE */


/* 串口初始化函数 */
#if defined UART_INIT_CODE && UART_INIT_CODE > 0
void uart_init()
{
    ES    = 0;
    TR1   = 0;

    SCON  = 0;
    SCON |= 0x50;
    TMOD &= 0x0f;
    TMOD |= 0x20;

  #if UART_SPEED > 0
    PCON |= 0x80;
  #else
    PCON &= 0x7f;
  #endif

  #if UART_CLOCK == FOSC
    AUXR |= 0x40; /* STC定时器1时钟为FOSC, 即1T */
  #elif UART_CLOCK == FOSC/12
    AUXR &= 0xbf; /* STC定时器1时钟为FOSC/12, 12T */
  #endif

    AUXR &= 0xfe; /* 串口1选择定时器1作为波特率发生器 */

    TH1 = UART_BRT;
    ET1 = 0; /* 关定时器中断 */
    ES  = 0; /* 关串口中断 */
    TR1 = 1; /* 启动定时器1 */
    RI  = 0; 
    TI  = 1; /* putchar 函数必须等待 TI 标志置位确认前一个字节发送完成, 否则无效等待 */
  
}
#endif /* UART_INIT_CODE */
