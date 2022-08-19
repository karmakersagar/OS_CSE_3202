#include "../include/sys_init.h"
#include "../include/kmain.h"
#include "../include/kstdio.h"
#include <stdint.h>

void kmain(void)
{
__sys_init();
uint32_t a=11000;
uint32_t b=0;

float x ;
 kprintf((uint8_t*)"%s",(uint8_t*)"Booting OS CSE: ");
 kprintf((uint8_t*)"%s",(uint8_t*)"Version: 1.0\n");
	kprintf((uint8_t*)"%s",(uint8_t*)"Wellcome .... \n");
 //_USART_WRITE(USART2,(uint8_t*)"abc");
while(1){

 
	//for string  scanf printf 
	// uint8_t ch[50] ;
	// kscanf((uint8_t*)"%s",(uint8_t*) ch);
	// kprintf((uint8_t*)"%s",(uint8_t*)ch);

	// decimal scanf && printf done
	// uint32_t dec;
	// kscanf((uint8_t*)"%d",(uint8_t*)&dec);
	//  kprintf((uint8_t*)"%d",(uint8_t*)&dec);


	// char scanf && printf 
	// uint8_t ch;
	// kscanf((uint8_t*)"%c",(uint8_t*) &ch);
 //    kprintf((uint8_t*)"%c",(uint8_t*) ch);

	//hex scanf && printf
	// uint32_t hex;
	// kscanf((uint8_t*)"%x",(uint8_t*)&hex);
	// kprintf((uint8_t*)"%x",(uint8_t*)&hex);
	// for floating point 
		   kscanf((uint8_t*)"%f",(uint8_t*)&x);
		   kprintf((uint8_t*)"%f",(uint8_t*)&x);
	a++;
	b++;
	//you can change the following line by replacing a delay function
	for(uint32_t i=0;i<10000000;i++){}	
}
}

