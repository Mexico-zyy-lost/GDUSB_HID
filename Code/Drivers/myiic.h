#ifndef __MYIIC_H
#define __MYIIC_H

#include "gd32f30x.h"


//IO方向设置
#define SDA_IN()  {gpio_init(GPIOB,GPIO_MODE_IPD,GPIO_OSPEED_50MHZ,GPIO_PIN_9);}
#define SDA_OUT() {gpio_init(GPIOB,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_9);}

//IO操作函数	 
#define IIC_SCL_LOW    	 gpio_bit_reset(GPIOB,GPIO_PIN_9)
#define IIC_SCL_HIGH     gpio_bit_set(GPIOB,GPIO_PIN_9)
#define IIC_SDA_LOW		 gpio_bit_reset(GPIOB,GPIO_PIN_9)
#define IIC_SDA_HIGH	 gpio_bit_set(GPIOB,GPIO_PIN_9)
#define READ_SDA   		 gpio_input_bit_get(GPIOB,GPIO_PIN_9) ? 1 : 0

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	  
#endif
















