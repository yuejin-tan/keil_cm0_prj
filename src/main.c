#include "string.h"

#include "CMSDK_CM0.h"

#include "delay.h"
#include "ahb_uart.h"

#include "scd_inc.h"

void uart_ahb_init()
{
    __ISB();
    __DSB();
    __DMB();
    AHB_UART->cmd.all = 0;
    __ISB();
    __DSB();
    __DMB();
    AHB_UART->buad_div_2 = (50ul * 1000ul * 1000ul / (115200ul * 2ul)) - 1;
    // AHB_UART->buad_div_2 = (50ul * 1000ul * 1000ul / (460800ul * 2ul)) - 1;
    __ISB();
    __DSB();
    __DMB();
    AHB_UART->cmd.all = 1;
    __ISB();
    __DSB();
    __DMB();
}

volatile uint32_t ms_cnt = 0;

uint16_t test1 = 0;
uint16_t test2 = 0;
uint16_t test3 = 0;
uint16_t test4 = 0;

uint16_t test1r = 0;
uint16_t test2r = 0;
uint16_t test3r = 0;
uint16_t test4r = 0;

uint8_t txdata = 0;
uint8_t rxdata = 0;
uint8_t rxbuff[256] = { 0 };
uint8_t rxbuffptr = 0;

int main(void)
{
    SysTick_Config(SystemCoreClock / 1000ul - 1ul);
    uart_ahb_init();
    test3 = AHB_UART->buad_div_2;

    // 测试delay函数
    delay_ms(1000);
    test1 = ms_cnt;
    DELAY_TICK(1000 * 1000 * 50);
    test2 = ms_cnt;

    scd_init_1();

    while (1)
    {
        while (AHB_UART->cmd.bit.TX_FIFO_FULL == 0)
        {
            AHB_UART->data = scd_send1Byte(&scd_1);
        }

        while (AHB_UART->cmd.bit.RX_FIFO_EMPTY == 0)
        {
            SCD_Rev1Byte(&scd_1, AHB_UART->data);
        }
    }

    // LED1_ON;
    // delay_ms(50);
    // LED1_OFF;
    // DELAY_TICK(200 * 1000 * 50);
}



