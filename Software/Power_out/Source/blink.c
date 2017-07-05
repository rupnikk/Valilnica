/*
 * blink.c
 *
 *  Created on: 19. dec. 2016
 *      Author: Urban Rupnik
 *      City: Zadlog 42
 */

#include <avr/io.h>
#include "stdint.h"
#include "bittop.h"
#include "blink.h"
#include "hardware.h"


/*
 * Blink struktura z nastavitvami
 *
 */

/*******************************
 ***KONFIGURACIJSKA FUNKCIJA****
 *******************************/

Blink leds[LED_NUM];
Input zero;

void IOCfg(){


	leds[0].pin = GRELEC;
	leds[0].port=&GRELEC_PORT;
	leds[0].dir_port=&GRELEC_DIR_PORT;
	leds[0].value=1;
	leds[0].duty=50;

	leds[1].pin = LUC;
	leds[1].port=&LUC_PORT;
	leds[1].dir_port=&LUC_DIR_PORT;
	leds[1].value=1;
	leds[1].duty=50;

	zero.pin=ZERO;
	zero.dir_port=&ZERO_DIR_PORT;
	zero.port=&ZERO_PORT;
	zero.value_reg=&ZERO_VALUE_REG;
	zero.pcint=ZERO_PCINT;


	for (uint8_t i=0; i<LED_NUM;i++){
		BlinkCfg(&leds[i]);
	}

	InputCfg(&zero);
	CLEARBIT(*zero.port, zero.pin);
};




/*******************************
 ************FUNKCIJE***********
 *******************************/
void BlinkCfg(Blink *ledica){
	SETBIT(*(ledica->dir_port), ledica->pin);
	if(ledica->value==1)SETBIT(*(ledica->port), ledica->pin);
	else CLEARBIT(*(ledica->port), ledica->pin);
}

void SetValue(Blink *ledica){
	if(ledica->value==1){
		SETBIT(*(ledica->port), ledica->pin);
	}
	else {
		CLEARBIT(*(ledica->port), ledica->pin);
	}
}

void InputCfg(Input *button){
	CLEARBIT(*(button->dir_port), button->pin);
	SETBIT(*(button->port), button->pin);
}
