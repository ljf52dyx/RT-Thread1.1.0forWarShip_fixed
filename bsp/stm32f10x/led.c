/*
 * File      : led.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */
#include <rtthread.h>
#include <stm32f10x.h>

// led define
#ifdef STM32_SIMULATOR
#define led1_rcc                    RCC_APB2Periph_GPIOA
#define led1_gpio                   GPIOA
#define led1_pin                    (GPIO_Pin_5)

#define led2_rcc                    RCC_APB2Periph_GPIOA
#define led2_gpio                   GPIOA
#define led2_pin                    (GPIO_Pin_6)

#else
#ifdef HAVE_SHENZHOU

#define led1_rcc                    RCC_APB2Periph_GPIOF
#define led1_gpio                   GPIOF
#define led1_pin                    (GPIO_Pin_6)

#define led2_rcc                    RCC_APB2Periph_GPIOF
#define led2_gpio                   GPIOF
#define led2_pin                    (GPIO_Pin_7)

#define led3_rcc                    RCC_APB2Periph_GPIOF
#define led3_gpio                   GPIOF
#define led3_pin                    (GPIO_Pin_8)

#define led4_rcc                    RCC_APB2Periph_GPIOF
#define led4_gpio                   GPIOF
#define led4_pin                    (GPIO_Pin_9)


#else
#define led1_rcc                    RCC_APB2Periph_GPIOB
#define led1_gpio                   GPIOB
#define led1_pin                    (GPIO_Pin_5)

#define led2_rcc                    RCC_APB2Periph_GPIOE
#define led2_gpio                   GPIOE
#define led2_pin                    (GPIO_Pin_5)
#endif
#endif // led define #ifdef STM32_SIMULATOR

void rt_hw_led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(led1_rcc|led2_rcc,ENABLE);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin   = led1_pin;
    GPIO_Init(led1_gpio, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = led2_pin;
    GPIO_Init(led2_gpio, &GPIO_InitStructure);
#ifdef HAVE_SHENZHOU
	GPIO_InitStructure.GPIO_Pin   = led3_pin;
    GPIO_Init(led3_gpio, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = led4_pin;
    GPIO_Init(led4_gpio, &GPIO_InitStructure);

#endif	
	
}

void rt_hw_led_on(rt_uint32_t n)
{
    switch (n)
    {

#ifdef HAVE_SHENZHOU
    case 0:
        GPIO_ResetBits(led1_gpio, led1_pin);
        break;
    case 1:
        GPIO_ResetBits(led2_gpio, led2_pin);
        break;
    case 2:
        GPIO_ResetBits(led3_gpio, led3_pin);
        break;
    case 3:
        GPIO_ResetBits(led4_gpio, led4_pin);
        break;	
#else
	case 0:
        GPIO_SetBits(led1_gpio, led1_pin);
        break;
    case 1:
        GPIO_SetBits(led2_gpio, led2_pin);
        break;
#endif				
    default:
        break;
    }
}

void rt_hw_led_off(rt_uint32_t n)
{
    switch (n)
    {
#ifdef HAVE_SHENZHOU
	case 0:
        GPIO_SetBits(led1_gpio, led1_pin);
        break;
    case 1:
        GPIO_SetBits(led2_gpio, led2_pin);
        break;
    case 2:
        GPIO_SetBits(led3_gpio, led3_pin);
        break;
    case 3:
        GPIO_SetBits(led4_gpio, led4_pin);
        break;
#else

	case 0:
        GPIO_ResetBits(led1_gpio, led1_pin);
        break;
    case 1:
        GPIO_ResetBits(led2_gpio, led2_pin);
        break;

#endif
    default:
        break;
    }
}
#ifdef HAVE_SHENZHOU
void rt_hw_led_count(rt_uint8_t count )
{
	rt_uint8_t i;
	for(i=0;i<4;i++)
	{
		if((count&(0x01<<i))>>i)
		{
			rt_hw_led_on(i);
		}
		else
		{
			rt_hw_led_off(i);
		}		
	}
}
#endif
#ifdef RT_USING_FINSH
#include <finsh.h>
static rt_uint8_t led_inited = 0;
void led(rt_uint32_t led, rt_uint32_t value)
{
    /* init led configuration if it's not inited. */
    if (!led_inited)
    {
        rt_hw_led_init();
        led_inited = 1;
    }

    if ( led == 0 )
    {
        /* set led status */
        switch (value)
        {
        case 0:
            rt_hw_led_off(0);
            break;
        case 1:
            rt_hw_led_on(0);
            break;
			
			
        default:
            break;
        }
    }

    if ( led == 1 )
    {
        /* set led status */
        switch (value)
        {
        case 0:
            rt_hw_led_off(1);
            break;
        case 1:
            rt_hw_led_on(1);
            break;
        default:
            break;
        }
    }
#ifdef HAVE_SHENZHOU
	if ( led == 2 )
    {
        /* set led status */
        switch (value)
        {
        case 0:
            rt_hw_led_off(2);
            break;
        case 1:
            rt_hw_led_on(2);
            break;
        default:
            break;
        }
    }
	if ( led == 3 )
    {
        /* set led status */
        switch (value)
        {
        case 0:
            rt_hw_led_off(3);
            break;
        case 1:
            rt_hw_led_on(3);
            break;
        default:
            break;
        }
    }
#endif	
}
#ifdef HAVE_SHENZHOU
FINSH_FUNCTION_EXPORT(led, set led[0 - 3] on[1] or off[0].)
#else
FINSH_FUNCTION_EXPORT(led, set led[0 - 1] on[1] or off[0].)
#endif
#endif

