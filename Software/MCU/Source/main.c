/*
 * main.c
 *
 *  Created on: 28. feb. 2017
 *      Author: urban
 */


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void){

OSC.CTRL=OSC_XOSCEN_bm;
CCP=0xD8;
CLK.CTRL=0x03;

PORTD.DIR=1<<0;
	for(;;){
		PORTD.OUT=1<<0;
		_delay_ms(500);
		PORTD.OUT=0<<0;
		_delay_ms(500);
	}
	return 0;
}
