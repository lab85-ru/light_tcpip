#include "stm32f10x_conf.h"
#include "stm32f10x.h"
//---------------------------------------------------------------------------
#include <string.h>
#include <stdarg.h>
//---------------------------------------------------------------------------
#include "board.h"
#include "main.h"
#include "init_hardware.h"
#
#include "enc28j60.h"
#include "sg_lib.h"
#include "printf_hal.h"
#include "git_commit.h"
#include "sys_timer.h"
#include "time_hal.h"

const char txt_device_ver_soft[]={"SV:0.1.17"};	// версия прошивки софт
const char txt_device_ver_hard[]={"HV:1.0.12"};	// версия прошивки железа
const char txt_device_name[]={"Lingt TCP/IP"};  // текстовое описание устройства

const uint8_t mac_adr[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05}; // SET MY MAC
const uint32_t ip_addr = 0;
const uint32_t ip_mask = 0;
const uint32_t ip_gateway = 0;

void tx_byte(uint8_t ch);

#define TCPIP_BUF_RX_SIZE   (1600)
uint8_t tcpip_buf_rx[ TCPIP_BUF_RX_SIZE ];



//---------------------------------------------------------------------------
void light_tcpip(void) 
{
    uint16_t dlen = 0;

	for (;;) {
		dlen = enc28j60_recv_packet((uint8_t *) tcpip_buf_rx, TCPIP_BUF_RX_SIZE);
		if (dlen > 0) {
            printf_d("RX = %d bytes.\n", dlen);
            hex_out((char const*)tcpip_buf_rx, dlen);
            printf_d("\n");
//enc28j60_send_packet((uint8_t *) uip_buf, uip_len);
		}
	}// END FOR(;;)
}

////////////////////////////////////////////////////////////////////////////////
// MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN MAIN
////////////////////////////////////////////////////////////////////////////////
int main()
{
    xfunc_out = tx_byte;           // настройка указателя на функцию вывода (для xprintf.c)

  	// this sets up the oscilator
	SystemInit();
    init_hardware();
    sys_timer_setup();

    printf_d("\r\n\r\nDevice start.\n");

    if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET){
	    /* IWDGRST flag set */
		printf_d("\r\nHard Reset From WatchDog....\r\n");
		/* Clear reset flags */
		RCC_ClearFlag();
	}

    printf_d("================================================================================\r\n");
    printf_d(" Soft Version = %s\r\n", txt_device_ver_soft);
    printf_d(" Hard Version = %s\r\n", txt_device_ver_hard);
    printf_d(" Device Name  = %s\r\n", txt_device_name);
    printf_d(" GIT commit   = %s\r\n", git_commit_str);
    printf_d("================================================================================\r\n");
    
    light_tcpip();

	return 0;
}
//---------------------------------------------------------------------------
void tx_byte(uint8_t ch)
{
    while (USART_GetFlagStatus(H_COM1, USART_FLAG_TC) == RESET);
    USART_SendData(H_COM1, (uint8_t) ch);
}
