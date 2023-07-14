/***************************************************************************//**
  文件: main.c
  作者: Zhengyu https://gzwelink.taobao.com
  版本: V1.0.0
  时间: 202101201
	平台:MINI-GD32F303RCT6开发板
	微信号:gzwelink

*******************************************************************************/

#include "gd32f30x.h"
#include "systick.h"
#include <stdio.h>

int main(void)
{
  rcu_ahb_clock_config(RCU_AHB_CKSYS_DIV1);//设置主频120M(#define __SYSTEM_CLOCK_120M_PLL_HXTAL           (uint32_t)(120000000),8M外部晶振  (#define HXTAL_VALUE    ((uint32_t)8000000))
	systick_config();//1ms systick
	rcu_periph_clock_enable(RCU_AF); //AF时钟使能 
	delay_1ms(1000);//等待1000ms
	gpio_pin_remap_config(GPIO_SWJ_NONJTRST_REMAP, ENABLE);//下载口NJTRST引脚当做普通I/O口
	rcu_periph_clock_enable(RCU_GPIOB);//PB时钟使能
	gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4);//PB4配置成输出
	
    while(1)
    {
        delay_1ms(1000);//等待1000ms
        gpio_bit_set(GPIOB, GPIO_PIN_4);//输出高
        delay_1ms(1000);
        gpio_bit_reset(GPIOB, GPIO_PIN_4);//输出低
    }
    return 0;
}
