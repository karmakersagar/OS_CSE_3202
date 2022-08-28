#ifndef __SYS_H
#define __SYS_H
#include<stdint.h>
extern volatile uint32_t mscount ;
typedef struct{
	volatile uint32_t CTRL; 
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile uint32_t CALIB;

}SysTick_type;

#define SysTick ((SysTick_type*)0xE000E010 ) 
void sysTick_init();
void sysTick_enable(void);
void sysTick_disable(void);
uint32_t getSysTick_Count(void);
void update_SysTick(uint32_t);
uint32_t get_Time(void);

#endif
