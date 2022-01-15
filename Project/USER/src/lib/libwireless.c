#include "fsl_common.h"
#include "fsl_gpio.h"
#include "zf_systick.h"
#include "zf_gpio.h"
#include "zf_iomuxc.h"
#include "zf_uart.h"
#include "SEEKFREE_WIRELESS.h"

void wirelessInit(void)
{
    seekfree_wireless_init();    
}

uint32 sendBuff(uint8 *buff, uint32 len)
{
    while(len>30)
    {
        if(gpio_get(RTS_PIN))  
        {
            return len;
        }
        uart_putbuff(WIRELESS_UART,buff,30);

        buff += 30; 
        len -= 30;
    }
    
    if(gpio_get(RTS_PIN))  
    {
    }
    uart_putbuff(WIRELESS_UART,buff,len);
    
    return 0;
}

