/*
 * blink.h
 *
 *  Created on: 19. dec. 2016
 *      Author: Urban Rupnik
 *      City: Zadlog 42
 */

#ifndef _BLINK_H_
#define _BLINK_H_

/*******************************
 ***********STRUKTURE***********
 *******************************/
// structura za izhod
typedef volatile struct  Blink{
	volatile uint8_t pin;
	volatile uint8_t* port;
	volatile uint8_t* dir_port;
	uint8_t value;
	uint8_t pwm;
	uint8_t freq;
	uint8_t duty;
}Blink;



//struktura senzorjev
typedef enum{
	DHT11
}sensor_type;

typedef volatile struct  Senzor{
	volatile uint8_t pin;
	volatile uint8_t* port;
	volatile uint8_t* dir_port;
	volatile uint8_t* in_port;
	volatile char data[5];
	sensor_type type;
}Senzor;



typedef struct input{
	volatile uint8_t pin;
	volatile uint8_t* port;
	volatile uint8_t* dir_port;
}Input;

#define LED_NUM 5
#define SEN_NUM 3

extern Blink leds[LED_NUM];
extern Senzor sensors[SEN_NUM];

/*******************************
 ***KONFIGURACIJSKA FUNKCIJA****
 *******************************/
// vhodi in izhodi
void IOCfg();



/*******************************
 ************FUNKCIJE***********
 *******************************/

// konfiguraj ledico
void  BlinkCfg(Blink *ledica);
void SetValue(Blink *ledica);

//vhod
void InputCfg();

#endif /* BLINK_H_ */
