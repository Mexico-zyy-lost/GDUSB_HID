#include "myiic.h"

//初始化IIC
void IIC_Init(void)
{					     
	gpio_init(GPIOB,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_9);//GPIO_MODE_OUT_OD
	gpio_init(GPIOA,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_13);
}
//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA_HIGH;	  	  
	IIC_SCL_HIGH;
	delay_1ms(2);
 	IIC_SDA_LOW;//START:when CLK is high,DATA change form high to low 
	delay_1ms(2);
	IIC_SCL_LOW;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL_LOW;
	IIC_SDA_LOW;//STOP:when CLK is high DATA change form low to high
 	delay_1ms(2);
	IIC_SCL_HIGH; 
	IIC_SDA_HIGH;//发送I2C总线结束信号
	delay_1ms(2);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA_HIGH;
	delay_1ms(2);	   
	IIC_SCL_HIGH;
	delay_1ms(2);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_LOW;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL_LOW;
	SDA_OUT();
	IIC_SDA_LOW;
	delay_1ms(2);
	IIC_SCL_HIGH;
	delay_1ms(2);
	IIC_SCL_LOW;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL_LOW;
	SDA_OUT();
	IIC_SDA_HIGH;
	delay_1ms(2);
	IIC_SCL_HIGH;
	delay_1ms(2);
	IIC_SCL_LOW;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SDA_OUT(); 	    
    IIC_SCL_LOW;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
		if((txd&0x80)>>7)
			IIC_SDA_HIGH;
		else
			IIC_SDA_LOW;
		
		txd<<=1; 	  
		delay_1ms(2);
		IIC_SCL_HIGH;
		delay_1ms(2); 
		IIC_SCL_LOW;	
		delay_1ms(2);
    }	 
}

//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL_LOW; 
        delay_1ms(2);
		IIC_SCL_HIGH;
        receive<<=1;
        if(READ_SDA)
			receive++;   
		delay_1ms(2); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}



























