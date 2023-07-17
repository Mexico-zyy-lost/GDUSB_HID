/*!
    \file    main.c
    \brief  
*/
#include "main.h"
#include "standard_hid_core.h"
#include "usbd_hw.h"
#include "myiic.h"

usb_dev usb_hid;

static uint8_t touch_singal;

extern hid_fop_handler fop_handler;
extern uint8_t buff_Key[9];

uint8_t iic_data[5];

uint16_t key_temp[6];
uint16_t isFn_Press;

//extern xKEY_MATRIX_TypeDef xKEY_MATRIX;

void main_tick_1s(void)
{
	gd_led_toggle(LED1);
}

/*!
    \brief    main function
    \param[in]  none
    \param[out] none
    \retval     none
*/

void timer2_config(void)
{
    /* -----------------------------------------------------------------------
    ----------------------------------------------------------------------- */
    timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER2);

    timer_deinit(TIMER2);

    /* TIMER1 configuration */
    timer_initpara.prescaler         = 119;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 15999;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER2,&timer_initpara);

    /* CH0,CH1 and CH2 configuration in PWM mode */
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

    timer_channel_output_config(TIMER2,TIMER_CH_0,&timer_ocintpara);

    /* CH0 configuration in PWM mode0,duty cycle 25% */
    timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_0,3999);
    timer_channel_output_mode_config(TIMER2,TIMER_CH_0,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER2,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER2);
    /* auto-reload preload enable */
    timer_enable(TIMER2);
}

uint8_t* read_action()
{
    IIC_Start();  
	IIC_Send_Byte(0x10 | 1);
	IIC_Wait_Ack();
    iic_data[0]=IIC_Read_Byte(0);
	iic_data[1]=IIC_Read_Byte(0);	
	iic_data[2]=IIC_Read_Byte(0);	
	iic_data[3]=IIC_Read_Byte(0);	
	iic_data[4]=IIC_Read_Byte(1);		
    IIC_Stop();//产生一个停止条件	    
	return iic_data;
}

void writeOneByte(uint16_t WriteAddr,uint8_t DataToWrite,uint8_t DataToWrite2)
{				   	  	    																 
    IIC_Start();
	IIC_Send_Byte(WriteAddr);
	IIC_Wait_Ack();	   
    IIC_Send_Byte(DataToWrite);
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite2);						   
	IIC_Wait_Ack();  			
    IIC_Stop();//产生一个停止条件 
	delay_1ms(10);	 
}

int main(void)
{	
	rcu_ahb_clock_config(RCU_AHB_CKSYS_DIV1);
    systick_config();
	rcu_periph_clock_enable(RCU_AF); //AF时钟使能
	delay_1ms(1000);//等待1000ms
	/* system clocks configuration */
	gpio_pin_remap_config(GPIO_SWJ_NONJTRST_REMAP, ENABLE);//下载口NJTRST引脚当做普通I/O口
	rcu_periph_clock_enable(RCU_GPIOB);//PB时钟使能
	rcu_periph_clock_enable(RCU_GPIOC);//PB时钟使能
//	gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3);//PB4配置成输出
//	gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);//PB4配置成输出
	
//    gd_led_init(LED1);
//	gd_led_init(LED2);
	
	gd_key_init();
//	gpio_init(GPIOB, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_15);
	
//	timer2_config(); // PB2

	rcu_config();
	
	hid_itfop_register (&usb_hid, &fop_handler);

    /* USB device configuration */
    usbd_init(&usb_hid, &hid_desc, &hid_class);

    /* NVIC configuration */
    nvic_config();

    usbd_connect(&usb_hid);
	
////	IIC_Init();
////	
////	writeOneByte(0x10,0xc0,1);
	
	while(USBD_CONFIGURED != usb_hid.cur_status){
    }
	
	while(1)
	{
		gd_led_off(LED2); 
		
		/* check whether the button is pressed */
		KEY_MATRIX_Scan(key_temp,&isFn_Press);
		if(key_temp[0] != 0)
		{
			for(int i = 0;i < isFn_Press;i++)
			{
				buff_Key[3 + i] = key_temp[i];
			}
			fop_handler.hid_itf_data_process(&usb_hid);

			/* delay 10ms for software removing jitter */
			delay_1ms(10);
		}
//		
//		if(touch_singal)
//		{
//			touch_singal = 0;
//			
//			*iic_data = read_action();
//			
//			if(iic_data[1] | 0x7)
//			{
//				// 左中右 触发
//			}
//		
//		}
//		delay_1ms(500);
		gd_led_on(LED2);
		delay_1ms(200);
	}
}

void EXTI5_9_IRQHandler (void)
{
	if (RESET != exti_interrupt_flag_get(EXTI_8)) 
	{
		exti_interrupt_flag_clear(EXTI_8);
		
		delay_1ms(1);
		
		if(gpio_input_bit_get(GPIOB,GPIO_PIN_8) == RESET)
		{
			touch_singal = 1;
		}
	}	
}


void USART0_IRQHandler(void)	
{
    if((RESET != usart_interrupt_flag_get(COM0, USART_INT_FLAG_RBNE)) && 
       (RESET != usart_flag_get(COM0, USART_FLAG_RBNE)))
	{
        com_put_char(usart_data_receive(COM0));
	}		
}



volatile uint32_t msCount = 0;
void SysTick_Handler(void)
{
	delay_decrement();
	if (msCount % 1000 == 0) {
		main_tick_1s();
		msCount = 0;
	}
	msCount++;
}
