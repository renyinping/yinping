#include "uart.h"
#include <reg52.h>
#include <stdio.h>
#include "config.h"


sfr AUXR = 0x8E;   /* 0000,0000 STC15-MCU 辅助寄存器 */


/* 串口波特率发生器或定时器初值 */
#if UART_SPEED > 0
#define UART_BRT (256-(unsigned char)(((float)UART_CLOCK)/16/(UART_RATE)+0.5))
#else
#define UART_BRT (256-(unsigned char)(((float)UART_CLOCK)/32/(UART_RATE)+0.5))
#endif


/* 串口参数 */
#if defined CODE_UART_CFG && CODE_UART_CFG > 0
code UART_CFG uart_cfg =
{
    UART_RATE,
    UART_CLOCK,
    UART_SPEED,
    UART_BRT
};
#endif /* CODE_UART_CFG */


/* 串口测试函数 */
#if defined CODE_UART_TEST && CODE_UART_TEST > 0
void uart_test()
{
    printf("uart baud rate : %lu\n", uart_cfg.rate);
    printf("uart timer clock : %lu\n", uart_cfg.clock);
    printf("uart timer initial value : 0x%bx\n", uart_cfg.brt);
    printf("uart speed mode : %bu\n", uart_cfg.smod);
}
#endif /* CODE_UART_TEST */


/* 串口初始化函数 */
#if defined CODE_UART_INIT && CODE_UART_INIT > 0
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
    TR1 = 1; /* 启动定时器1 */
    
  #if UART_INT_EN > 0
    RI = 0;
    TI = 0;
    ES = 1;
    EA = 1;
  #else
    ES  = 0; /* 关串口中断 */
    RI  = 0; 
    TI  = 1; /* putchar 函数必须等待 TI 标志置位确认前一个字节发送完成, 否则无效等待 */
  #endif /* UART_INT_EN */
}
#endif /* CODE_UART_INIT */


/* putchar */
#if defined CODE_PUTCHAR && CODE_PUTCHAR > 0
char putchar (char c)
{
    if ('\n' == c) while(uart_tx_byte(0x0d));
    while(uart_tx_byte(c));
    return c;
}
#endif /* CODE_PUTCHAR */


/* _getkey */
#if defined CODE_GETKEY && CODE_GETKEY > 0
char _getkey (void)
{
    char c;
    
    while(uart_rx_byte(&c));
    return c;
}
#endif /* CODE_GETKEY */
