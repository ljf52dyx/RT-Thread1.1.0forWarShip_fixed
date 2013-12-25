#ifndef __DELAY_H__
#define __DELAY_H__

#include <board.h>
#include <rtthread.h>
#include <stm32f10x.h>


void delay_init(void);
void delay_ms(rt_uint16_t ms);
void delay_us(rt_uint32_t us);


#endif

