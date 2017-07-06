/*
 * main.c
 *
 *  Created on: 27. feb. 2017
 *      Author: urban
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "hardware.h"
#include "blink.h"
#include "bittop.h"
#include "usi_i2c_slave.h"

// določimo I2C naslov (0x41)

extern char usi_i2c_slave_address;
extern char* USI_Slave_register_buffer[USI_SLAVE_REGISTER_COUNT];
char usi_i2c_slave_address=0x41;

uint8_t cnt;
Input zero;

int main(void){

	sei();
	char a;
	char b;
	char error;
	char wtchdog;

	// inicializacija vhodnih in izhodnih pinov ter struktur
	IOCfg();

	// interrupt od zero
	SETBIT(GIMSK, PCIE);
	SETBIT(PCMSK, zero.pcint);


	//Timer1 prescaler (8/8)
	SETBITS(TCCR1, BIT(CS12));
	CLEARBITS(TCCR1, BIT(CS12)|BIT(CS10)|BIT(CS11));

	//interupt od timerja
	OCR1A=0x99;
	SETBIT(TIMSK, OCIE1A);


	// I2C inicializacija z naslovom 0x41
	USI_I2C_Init(0x41);


	// interni registri I2C komunikacije

	// izhod za grelec
	USI_Slave_register_buffer[0]=&leds[0].value;
	// izhod za luc
	USI_Slave_register_buffer[1]=&leds[1].value;
	// register za napake
	USI_Slave_register_buffer[2]=&error;
	// watchdog (ni še)
	USI_Slave_register_buffer[3]=&wtchdog;

	_delay_ms(1000);

	for(;;){
		//_delay_ms(100);
		//leds[0].duty=50;
		//leds[1].duty=50;
		for (uint8_t i=0; i<LED_NUM;i++){
			SetValue(&leds[i]);
		}
		_delay_ms(1000);
	}
	return 0;
}


ISR(PCINT0_vect){
	if(BITVAL(*zero.value_reg,zero.pin)){
		cnt=0;
		for (uint8_t i=0; i<LED_NUM;i++){
//			if(!leds[i].duty){
//				leds[i].value=1;
//			}
//			else
				leds[i].value=1;

			SetValue(&leds[i]);
		}
	}
}

ISR(TIM1_COMPA_vect){
	cnt++;
	for (uint8_t i=0; i<LED_NUM;i++){
		if((100-leds[i].duty)<=cnt){
			leds[i].value=0;
			SetValue(&leds[i]);
		}
	}
}
