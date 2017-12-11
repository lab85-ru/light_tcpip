/*
 * prvsetuphardware.h
 *
 *  Created on: 06.09.2010
 *      Author: Администратор
 */

#ifndef INIT_HARDWARE_H_
#define INIT_HARDWARE_H_
#include <stdint.h>

void init_hardware(void);
void output_gpio_byte(char b);
/*
void modem_reset_hard(void);
void modem_rts_out_low(void);
void modem_rts_out_high(void);
uint32_t modem_cts_in(void);
*/
#endif /* PRVSETUPHARDWARE_H_ */
