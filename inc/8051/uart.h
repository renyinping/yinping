#ifndef UART_H
#define UART_H


/* 串口参数结构定义 */
typedef struct _uart_cfg
{
    unsigned long rate;  /* 波特率 */
    unsigned long clock; /* 定时器时钟频率 */
    unsigned char smod;  /* 波特率倍速模式值 */
    unsigned char brt;   /* 波特率发生器或定时器初值 */
} UART_CFG;


/* 串口定义, 可在配置文件中重新设定参数, 例如
  #undef  UART_RATE
  #define UART_RATE 115200 */
#define CODE_UART_CFG 1          /* 使用(1)或者禁用(0) uaer_cfg 代码 */
#define CODE_UART_TEST 1         /* 使用(1)或者禁用(0) uaer_test 函数代码 */
#define CODE_UART_INIT 1         /* 使用(1)或者禁用(0) uart_init 函数代码 */
#define UART_RATE 9600           /* 设定 UART 速率 */
#define UART_CLOCK (FOSC/12)     /* 设定 UART 波特率发生器的时钟频率 */
#define UART_SPEED 0             /* 设定 UART 允许(1)或者禁止(0)使用倍速模式 */
#define UART_INT_EN 1            /* 设定 UART 允许(1)或者禁止(0)串口中断 */

#define CODE_UART_ISR 1                /* 使用(1)或者禁用(0) uart_isr 中断代码 */
#define UART_ISR_MEM_MOD small         /* 内存模式 */
#define UART_ISR_INT_FLAG interrupt 4  /* 中断标志号 */
#define UART_ISR_REG_GROUP using 2     /* 使用寄存器组 */
#define UART_RX_BUF_SIZE 8             /* 串口接收数据缓冲区 */
#define UART_TX_BUF_SIZE 16            /* 串口发送数据缓冲区 */
#define UART_RX_BUF_OF 0x01            /* 串口接收数据缓冲区溢出 */
#define CODE_UART_RX_BYTE 1            /* 使用(1)或者禁用(0) uart_rx_byte 函数代码 */
#define CODE_UART_TX_BYTE 1            /* 使用(1)或者禁用(0) uart_tx_byte 函数代码 */

#define CODE_PUTCHAR 1           /* 使用(1)或者禁用(0) putchar 函数代码 */
#define CODE_GETKEY 1            /* 使用(1)或者禁用(0) _getkey 函数代码 */


/* 函数和变量声明, 不使用的函数和变量可在配置文件中禁用, 例如
  #undef CODE_UART_CFG
  #undef CODE_UART_INIT */
extern code UART_CFG uart_cfg;
extern void uart_test();
extern void uart_init();
extern char uart_rx_byte (unsigned char* c);
extern char uart_tx_byte (unsigned char c);


#endif /* UART_H */
