#include "uart.h"
#include <stdio.h>
#include "config.h"


void main()
{
    uart_init();
    uart_test();
    
    for(;;)
    {
        _getkey();
        uart_test();
    }
}
