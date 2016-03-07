#include "uart.h"
#include <reg52.h>
#include "config.h"


#define XON  0x11
#define XOFF 0x13


/* 接收数据缓冲区 */
static       volatile unsigned char rxbuf[UART_RX_BUF_SIZE];
static  data volatile unsigned char rxnum = 0;
static  data volatile unsigned char rxend = 0;
#define                             rxstart ((unsigned char)((256 + rxend) - rxnum) & (sizeof(rxbuf) - 1))


/* 发送数据缓冲区 */
static       volatile unsigned char txbuf[UART_TX_BUF_SIZE];
static  data volatile unsigned char txnum = 0xff;
static  data volatile unsigned char txstart = 0;
#define                             txend ((unsigned char)(txstart + txnum) & (sizeof(txbuf) - 1))


static volatile bit xoff = 0;
static volatile bit rxbuf_of = 0; /* 接收数据缓冲区溢出 overflow */


/* 串口中断服务子程序 */
#if defined CODE_UART_ISR && CODE_UART_ISR > 0
void uart_isr() UART_ISR_MEM_MOD \
                UART_ISR_INT_FLAG \
                UART_ISR_REG_GROUP
{
    bit xon = 0;
    unsigned char c;
    
    ES = 0;

    if(RI)
    {
        c = SBUF;
        RI = 0;
        
        switch(c)
        {
            case XOFF:
                xoff = 1;
                break;
            
            case XON:
                xon  = xoff;
                xoff = 0;
                break;
            
            default:
                rxbuf[rxend] = c;
                rxend++; rxend &= (sizeof(rxbuf) - 1);
                rxnum++; 
                if(rxnum > sizeof(rxbuf)) rxbuf_of = 1; /* 缓冲区溢出 */
                break;
        }
    }

    if(TI || xon)
    {
        TI = 0;
        if((0 != txnum) && (0 == xoff))  //发送数据缓冲区不为空
        {
            SBUF = txbuf[txstart];
            txstart++; txstart &= (sizeof(txbuf) - 1);
            txnum--;
        }
        else txnum = 0xff;
    }
    
    ES = 1;
}
#endif /* CODE_UART_ISR */


/* 串口获取一个字符 */
#if defined CODE_UART_RX_BYTE && CODE_UART_RX_BYTE > 0
char uart_rx_byte (unsigned char* c)
{
    ES = 0;
    if(0 == rxnum)  //缓冲区为空
    {
        ES = 1;
        return -1;
    }

    *c = rxbuf[rxstart];
    rxnum--;

    ES = 1;
    return 0;
}
#endif /* CODE_UART_RX_BYTE */


/* 串口发送一个字符 */
#if defined CODE_UART_TX_BYTE && CODE_UART_TX_BYTE > 0
char uart_tx_byte (unsigned char c)
{
    ES = 0;
    
    if(sizeof(txbuf) == txnum)  //缓冲区满
    {
        ES = 1;
        return -1;
    }
    
    if((0xff == txnum) && (0 == xoff))  //串口发送数据已激活
    {
        SBUF = c;
        txnum = 0;
    }
    else
    {
        txbuf[txend] = c;
        txnum++;
    }

    ES = 1;
    return 0;
}
#endif /* CODE_UART_TX_BYTE */

