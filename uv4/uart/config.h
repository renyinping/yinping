/* 配置文件必须是最后一个包含的头文件 */
#ifndef CONFIG_H
#define CONFIG_H


/* 晶振频率 */
#define FOSC 11059200
//#undef  FOSC
//#define FOSC 12000000


/* 重新配置串口波特率为 2400 */
#undef  UART_RATE
#define UART_RATE 2400


//#undef UART_CFG_CODE
//#undef UART_INIT_CODE


#endif /* CONFIG_H */
