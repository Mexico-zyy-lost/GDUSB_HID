#ifndef __MYIIC_H
#define __MYIIC_H

#include "gd32f30x.h"


//IO��������
#define SDA_IN()  {gpio_init(GPIOB,GPIO_MODE_IPD,GPIO_OSPEED_50MHZ,GPIO_PIN_9);}
#define SDA_OUT() {gpio_init(GPIOB,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_9);}

//IO��������	 
#define IIC_SCL_LOW    	 gpio_bit_reset(GPIOB,GPIO_PIN_9)
#define IIC_SCL_HIGH     gpio_bit_set(GPIOB,GPIO_PIN_9)
#define IIC_SDA_LOW		 gpio_bit_reset(GPIOB,GPIO_PIN_9)
#define IIC_SDA_HIGH	 gpio_bit_set(GPIOB,GPIO_PIN_9)
#define READ_SDA   		 gpio_input_bit_get(GPIOB,GPIO_PIN_9) ? 1 : 0

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	  
#endif
















