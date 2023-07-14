
#include "led.h"


static uint32_t GPIO_PORT[LEDn] = {LED1_GPIO_PORT,LED2_GPIO_PORT};
static uint32_t GPIO_PIN[LEDn] = {LED1_PIN,LED2_PIN};
static rcu_periph_enum GPIO_CLK[LEDn] = {LED1_GPIO_CLK,LED2_GPIO_CLK};

void  gd_led_init (led_typedef_enum lednum)
{
    /* enable the led clock */
    rcu_periph_clock_enable(GPIO_CLK[lednum]);
    /* configure led GPIO port */ 
	 gpio_init(GPIO_PORT[lednum], GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,GPIO_PIN[lednum]);
	
   GPIO_BOP(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}
/*!
    \brief      turn on selected led
    \param[in]  lednum: specify the Led to be turned on
      \arg        LED1
    \param[out] none
    \retval     none
*/
void gd_led_on(led_typedef_enum lednum)
{
    GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}
/*!
    \brief      turn off selected led
    \param[in]  lednum: specify the Led to be turned off
      \arg        LED1
    \param[out] none
    \retval     none
*/
void gd_led_off(led_typedef_enum lednum)
{
	   GPIO_BOP(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}
/*!
    \brief      toggle selected led
    \param[in]  lednum: specify the Led to be toggled
      \arg        LED1
    \param[out] none
    \retval     none
*/
void  gd_led_toggle(led_typedef_enum lednum)
{
    gpio_bit_write(GPIO_PORT[lednum], GPIO_PIN[lednum], 
                    (bit_status)(1-gpio_input_bit_get(GPIO_PORT[lednum], GPIO_PIN[lednum])));
}
