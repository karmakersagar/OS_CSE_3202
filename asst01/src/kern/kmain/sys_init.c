#include "../include/sys_init.h"
#include "../arch/stm32f446re/include/dev/clock.h"
#include "../arch/stm32f446re/include/dev/usart.h"
#include "../arch/stm32f446re/include/dev/gpio.h"
void __sys_init(void)
{
	DRV_CLOCK_INIT(); //configure system clock 180 MHz
	DRV_GPIO_INIT(GPIOA);
	DRV_USART_INIT(USART2); //configure as standard input and output 
}
