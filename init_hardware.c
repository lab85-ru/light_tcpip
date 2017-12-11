/*
 * prvsetuphardware.c
 *
 *  Created on: 06.09.2010
 *      Author: Администратор
 */

#include <stdint.h>
#include <string.h>
#include "printf_hal.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "main.h"
#include "board.h"

//#include "queue_buf.h"

#include "enc28j60.h"

extern struct queue_buffer consol_rx;
extern uint8_t consol_rx_buf[ QUEUE_CONSOL_RX_SIZE ];
extern uint8_t mac_adr[];

void portDISABLE_INTERRUPTS(void)
{

}

void portENABLE_INTERRUPTS(void)
{

}


void init_hardware(void)
{
        USART_InitTypeDef USART_InitStructure;

        // ethernet
        enc28j60_init( mac_adr );

        // UART Init (CONSOL)
        USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;

	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	stm32_uart_init(COM1);
	stm32_uart_set(COM1, &USART_InitStructure, ENABLE);
        
}
