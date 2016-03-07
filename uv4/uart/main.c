#include "uart.h"
#include <stdio.h>
#include "config.h"

void main()
{
    uart_init();
    printf("uart baud rate : %lu\n", uart_cfg.rate);
    printf("uart timer clock : %lu\n", uart_cfg.clock);
    printf("uart timer initial value : 0x%bx\n", uart_cfg.brt);
    printf("uart speed mode : %bu\n", uart_cfg.smod);
    
    for(;;);
}
