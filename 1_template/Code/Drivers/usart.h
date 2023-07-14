

#ifndef __UART_H
#define __UART_H

#include "gd32f30x.h"
#include <stdio.h>
#include <stdio.h>
#include <string.h>	
#include <stdarg.h>


#define COMn                             1U
#define COM0                             USART0
#define COM0_CLK                         RCU_USART0

#define COM0_TX_PIN                      GPIO_PIN_9
#define COM0_TX_GPIO_PORT                GPIOA
#define COM0_TX_GPIO_CLK                 RCU_GPIOA


#define COM0_RX_PIN                      GPIO_PIN_10
#define COM0_RX_GPIO_PORT                GPIOA
#define COM0_RX_GPIO_CLK                 RCU_GPIOA

void com_put_char(uint8_t	dat);                                     
void uart_send_data(uint8_t* data, int len);
void uart_printf(char *str);
int fputc(int ch, FILE *f);
void gd_com_init(uint32_t com,uint32_t baud);

#endif

