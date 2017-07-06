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


// določimo I2C naslov (0x40)
extern char usi_i2c_slave_address;
extern char* USI_Slave_register_buffer[USI_SLAVE_REGISTER_COUNT];
char usi_i2c_slave_address=0x40;


/*
 * enum tip za koračne motorje
 */
typedef enum{
	ONE,
	TWO,
	THREE,
	FOUR
}stepper;

typedef enum{
	IDLE,
	LOAD,
	RUN
}stepper_run;

int main(void){
	sei();
	char load=0x00;
	char dir;
	char v;
	char error;
	char position_up=0x02;
	char position_down=0x00;
	char position_wnt_up;
	char position_wnt_down;
	uint16_t pos_wnt;
	uint16_t pos;
	char wtchdog;


	// default pozicija za koračni motor
	stepper my_stepper=ONE;

	stepper_run states=IDLE;

	// konfiguracija vhodnih in izhodnih pinov
	IOCfg();

	//uint8_t data[4];

	//initDHT();

	// inicializacija na I2C
	USI_I2C_Init(0x40);


	//sensors[0].data[0]=0x15;
	//sensors[0].data[2]=0x18;


	// I2C register povežemo z naslovi spremenljivk

	// 12V izhod
	USI_Slave_register_buffer[0]=&leds[0].value;
	// senzor 0 -> vlaga
	USI_Slave_register_buffer[1]=&sensors[0].data[0];
	// senzor 0 -> temperatura
	USI_Slave_register_buffer[2]=&sensors[0].data[2];
	// senzor 1 -> vlaga
	USI_Slave_register_buffer[3]=&sensors[1].data[0];
	// senzor 1 -> temperatura
	USI_Slave_register_buffer[4]=&sensors[1].data[2];
	// senzor 2 -> vlaga
	USI_Slave_register_buffer[5]=&sensors[2].data[0];
	// senzor 2 -> temperatura
	USI_Slave_register_buffer[6]=&sensors[2].data[2];
	// register za napake
	USI_Slave_register_buffer[7]=&error;
	// watchdog (ni še uporabljen)
	USI_Slave_register_buffer[8]=&wtchdog;
	// pozicija motorja
	USI_Slave_register_buffer[9]=&load;
	USI_Slave_register_buffer[10]=&position_wnt_up;
	USI_Slave_register_buffer[11]=&position_wnt_down;
	USI_Slave_register_buffer[12]=&position_up;
	USI_Slave_register_buffer[13]=&position_down;

	_delay_ms(1000);

	for(;;){

		switch(states){
			case IDLE:
				if (load==1){
					load=0;
					states=LOAD;
				}
				break;
			case LOAD:
				pos_wnt=(position_wnt_up<<8)|position_wnt_down;
				pos=(position_up << 8)|position_down;
				if(pos_wnt-pos >= 0)dir=1;
				else dir=0;

				states=RUN;
				break;
			case RUN:
				if((pos_wnt-pos)!=0){
					switch(my_stepper){
						case ONE:
							leds[1].value=1;
							if (dir==1) my_stepper=TWO;
							else my_stepper=FOUR;
							break;
						case TWO:
							leds[2].value=1;
							if (dir==1) my_stepper=THREE;
							else my_stepper=ONE;
							break;
						case THREE:
							leds[3].value=1;
							if (dir==1) my_stepper=FOUR;
							else my_stepper=TWO;
							break;
						case FOUR:
							leds[4].value=1;
							if (dir==1) my_stepper=ONE;
							else my_stepper=THREE;
							break;
					}
					for (uint8_t i=1; i<LED_NUM;i++){
						SetValue(&leds[i]);
					}

					if(dir==1)pos++;
					else pos--;

					position_up=(pos>>8)&0x00FF;
					position_down=pos&0x00FF;
				}
				else{
					states=IDLE;
				}
				break;
		}


		// zajem podatkov za posamezni senzor
		// vrne 0, če je zajem z napako oziroma ni uspel
		// in ponastavi vse registre na 0
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

		// nastavi 12V izhod na vrednost
		SetValue(&leds[0]);


	}
	return 0;
}
