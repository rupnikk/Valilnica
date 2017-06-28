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
Senzor sensors[SEN_NUM];


void IOCfg(){
	uint8_t i;

	leds[0].pin = VENT;
	leds[0].port=&VENT_PORT;
	leds[0].dir_port=&VENT_DIR_PORT;
	leds[0].value=0;

	leds[1].pin = PH0;
	leds[1].port=&PH0_PORT;
	leds[1].dir_port=&PH0_DIR_PORT;
	leds[1].value=0;

	leds[2].pin = PH1;
	leds[2].port=&PH1_PORT;
	leds[2].dir_port=&PH1_DIR_PORT;
	leds[2].value=0;

	leds[3].pin = PH2;
	leds[3].port=&PH2_PORT;
	leds[3].dir_port=&PH2_DIR_PORT;
	leds[3].value=0;

	leds[4].pin = PH3;
	leds[4].port=&PH3_PORT;
	leds[4].dir_port=&PH3_DIR_PORT;
	leds[4].value=0;


	sensors[0].pin=S1;
	sensors[0].port=&S1_PORT;
	sensors[0].dir_port=&S1_DIR_PORT;
	sensors[0].in_port=&S1_VALUE_REG;
	sensors[0].type=DHT11;
	for (i=0; i<5;i++){
		sensors[0].data[i]=0;
	}

	sensors[1].pin=S2;
	sensors[1].port=&S2_PORT;
	sensors[1].dir_port=&S2_DIR_PORT;
	sensors[1].in_port=&S2_VALUE_REG;
	sensors[1].type=DHT11;
	for (i=0; i<5;i++){
		sensors[1].data[i]=0;
	}

	sensors[2].pin=S3;
	sensors[2].port=&S3_PORT;
	sensors[2].dir_port=&S3_DIR_PORT;
	sensors[2].in_port=&S3_VALUE_REG;
	sensors[2].type=DHT11;
	for (i=0; i<5;i++){
		sensors[2].data[i]=0;
	}

	for ( i=0; i<LED_NUM;i++){
		BlinkCfg(&leds[i]);
	}
	for ( i=0; i<SEN_NUM;i++){
		InputCfg(&sensors[i]);
	}

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
