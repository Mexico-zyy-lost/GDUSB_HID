#ifndef _LED_H
#define _LED_H

#include  "gd32f30x.h"

/* exported types */
typedef enum 
{
    LED1 = 0,
	LED2 = 1,
} led_typedef_enum;

/* eval board low layer led */
#define LEDn                             2U
// b3 c12
#define LED1_PIN                         GPIO_PIN_3
#define LED1_GPIO_PORT                   GPIOB
#define LED1_GPIO_CLK                    RCU_GPIOB
  

#define LED2_PIN                         GPIO_PIN_12
#define LED2_GPIO_PORT                   GPIOC
#define LED2_GPIO_CLK                    RCU_GPIOC

void  gd_led_init (led_typedef_enum lednum);
void  gd_led_on(led_typedef_enum lednum);
void  gd_led_off(led_typedef_enum lednum);
void  gd_led_toggle(led_typedef_enum lednum);
#endif
