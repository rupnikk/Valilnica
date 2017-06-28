/*
 * main.c
 *
 *  Created on: 27. feb. 2017
 *      Author: urban
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "hardware.h"
#include "blink.h"
#include "bittop.h"
#include "usi_i2c_slave.h"
#include "dht11.h"


extern char usi_i2c_slave_address;
extern char* USI_Slave_register_buffer[USI_SLAVE_REGISTER_COUNT];
char usi_i2c_slave_address=0x40;

typedef enum{
	ONE,
	TWO,
	THREE,
	FOUR
}stepper;

int main(void){
	sei();
	char a=0;
	char b=0;
	char c=0x02;
	char v;
	char error;
	char position;
	char position_old=1;
	char wtchdog;
	//char b;
	//b=0x13;
	//uint8_t run=0;
	//uint8_t step=10;
	uint16_t cnt=0;
	uint16_t cnt1=0;


	stepper my_stepper=ONE;
	IOCfg();

	//uint8_t data[4];

	//initDHT();

	USI_I2C_Init(0x40);


	//sensors[0].data[0]=0x15;
	//sensors[0].data[2]=0x18;


	//USI_Slave_register_buffer[0] = &(sensors[0].data[0]);
	USI_Slave_register_buffer[0]=&a;
	USI_Slave_register_buffer[1]=&c;
	USI_Slave_register_buffer[2]=&leds[0].value;
	USI_Slave_register_buffer[3]=&sensors[0].data[0];
	USI_Slave_register_buffer[4]=&sensors[0].data[2];
	USI_Slave_register_buffer[5]=&sensors[1].data[0];
	USI_Slave_register_buffer[6]=&sensors[1].data[2];
	USI_Slave_register_buffer[7]=&sensors[2].data[0];
	USI_Slave_register_buffer[8]=&sensors[2].data[2];
	USI_Slave_register_buffer[9]=&error;
	USI_Slave_register_buffer[10]=&wtchdog;
	USI_Slave_register_buffer[11]=&position;

	_delay_ms(1000);

	for(;;){
		//cnt1=(c<<8)|b;
		cnt1=abs(position-position_old)*0x0200;

		v=fetchData(&sensors[0]);
		if (v==0){
			for (uint8_t i=0; i<5;i++){
				sensors[0].data[i]=0;
			}
		}

		v=fetchData(&sensors[1]);
		if (v==0){
			for (uint8_t i=0; i<5;i++){
				sensors[1].data[i]=0;
			}
		}


		v=fetchData(&sensors[2]);
		if (v==0){
			for (uint8_t i=0; i<5;i++){
				sensors[2].data[i]=0;
			}
		}

		SetValue(&leds[0]);
		if (a==0){
			_delay_ms(1000);
		}

		else {
			while (cnt<cnt1){
			_delay_ms(5);

			for (uint8_t i=1; i<LED_NUM;i++){
				leds[i].value=0;
			}
			switch(my_stepper){
				case ONE:
					leds[1].value=1;
					if (a==1) my_stepper=TWO;
					else my_stepper=FOUR;
					break;
				case TWO:
					leds[2].value=1;
					if (a==1) my_stepper=THREE;
					else my_stepper=ONE;
					break;
				case THREE:
					leds[3].value=1;
					if (a==1) my_stepper=FOUR;
					else my_stepper=TWO;
					break;
				case FOUR:
					leds[4].value=1;
					if (a==1) my_stepper=ONE;
					else my_stepper=THREE;
					break;

			}
			for (uint8_t i=1; i<LED_NUM;i++){
				SetValue(&leds[i]);
			}
			cnt++;

		}
			a=0;
			cnt=0;
		}
		/*leds[0].value=a;
		leds[1].value=b;
		for (uint8_t i=0; i<LED_NUM;i++){
			SetValue(&leds[i]);
		}*/
	}
	return 0;
}
