#include "../include/sys/sys.h"
#include<stdint.h>
volatile uint32_t mscount = 0;
void sysTick_init(){
	sysTick_disable();
	SysTick->CTRL |=(1UL << 2);// for ahb prescaler
	SysTick->CTRL |=(1UL << 1); // for systick clock exception request
	SysTick->VAL = 0; // set 0 to val register content
	SysTick->LOAD =1799999; // set reload value for 10 ms 

	mscount =  0; //get msCount;
	sysTick_enable();
	
}

void sysTick_enable(){
	mscount = 0; 
	SysTick->CTRL |=(1UL << 0); // enable systick 
}

void sysTick_disable(){
	SysTick->CTRL &= ~(1UL << 0);// disable systick 	
}

uint32_t getSysTick_Count(){

	return (SysTick->LOAD - SysTick->VAL);


}

void update_SysTick(uint32_t value){
	sysTick_disable();
	SysTick->LOAD =value; // set reload value for 10 ms because reload value = system clock * desired delay
	mscount = 0;

}

uint32_t get_Time(){
	return (mscount + (getSysTick_Count()/180000));
}
