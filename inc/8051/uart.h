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


/* 串口参数配置, 可在配置文件中重新设定参数, 例如
  #undef  UART_RATE
  #define UART_RATE 115200 */
#define UART_CFG_CODE 1          /* 使用(1)或者禁用(0) uaer_cfg 代码 */
#define UART_INIT_CODE 1         /* 使用(1)或者禁用(0) uart_init 函数代码 */
#define UART_RATE 9600           /* 设定 UART 速率 */
#define UART_CLOCK (FOSC/12)     /* 设定 UART 波特率发生器的时钟频率 */
#define UART_SPEED 0             /* 设定 UART 允许(1)或者禁止(0)使用倍速模式 */


/* 函数和变量声明, 不使用的函数和变量可在配置文件中禁用, 例如
  #undef UART_CFG_CODE
  #undef UART_INIT_CODE */
extern code UART_CFG uart_cfg;
extern void uart_init();


#endif /* UART_H */
