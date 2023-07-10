#include "usart.h"

static rcu_periph_enum COM_CLK[COMn] = {COM0_CLK};
static uint32_t COM_TX_PIN[COMn] = {COM0_TX_PIN};
static uint32_t COM_RX_PIN[COMn] = {COM0_RX_PIN};


/*!
    \brief    configure COM port
    \param[in]  COM: COM on the board
      \arg        COM0: COM on the board
    \param[out] none
    \retval     none
*/
void gd_com_init(uint32_t com,uint32_t baud)
{
	/* enable GPIO clock */
	uint32_t COM_ID = 0;
	if(COM0 == com)
	{
		COM_ID = 0U;
		
		rcu_periph_clock_enable(COM0_TX_GPIO_CLK);
		rcu_periph_clock_enable(COM0_RX_GPIO_CLK);
		rcu_periph_clock_enable(COM0_CLK);
		
		/* enable USART clock */
		rcu_periph_clock_enable(COM_CLK[COM_ID]);
		
		/* connect port to USARTx_Tx */
		gpio_init(COM0_TX_GPIO_PORT, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ ,COM_TX_PIN[COM_ID]);

		/* connect port to USARTx_Rx */
		gpio_init(COM0_RX_GPIO_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ ,COM_RX_PIN[COM_ID]);

		/* USART configure */
		usart_deinit(com);
		usart_baudrate_set(com,baud);
		usart_receive_config(com, USART_RECEIVE_ENABLE);
		usart_transmit_config(com, USART_TRANSMIT_ENABLE);
		usart_enable(com);

		nvic_irq_enable(USART0_IRQn, 1, 0); 
		usart_interrupt_enable(COM0, USART_INT_RBNE);
	} 
}

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(COM0, (uint8_t)ch);
    while(RESET == usart_flag_get(COM0, USART_FLAG_TBE));
    return ch;
}


//串口单字符发送
void com_put_char(uint8_t	dat)                                    
{
    usart_data_transmit(COM0, dat);
     while(RESET == usart_flag_get(COM0, USART_FLAG_TBE));
}

//串口字符串发送
void uart_printf(char *str)                                    
{
	unsigned int k=0;
  do 
  {
      com_put_char(  *(str + k) );
      k++;
  } while(*(str + k)!='\0');
}

//串口字符串或者结构体发送
void uart_send_data(uint8_t* data, int len)
{  
    uint8_t i;
    for(i = 0; i < len; i++)
    {  
			com_put_char(data[i]);
    } 
}


