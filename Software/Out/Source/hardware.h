/*
 * hardware.h
 *
 *  Created on: 16. jan. 2017
 *      Author: Urban Rupnik
 *      City: Zadlog 42
 */

#include <avr/io.h>
#include <util/delay.h>


#ifndef HARDWARE_H_
#define HARDWARE_H_

	#define DDR_USI			DDRA
	#define PORT_USI		PORTA
	#define PIN_USI			PINA
	#define PORT_USI_SDA	PA6
	#define PORT_USI_SCL	PA4
	#define PIN_USI_SDA		PINA6
	#define PIN_USI_SCL		PINA4


	#define VENT 			PB3
	#define VENT_PORT		PORTB
	#define VENT_DIR_PORT	DDRB

	#define PH0 			PB0
	#define PH0_PORT		PORTB
	#define PH0_DIR_PORT	DDRB

	#define PH1 			PB1
	#define PH1_PORT		PORTB
	#define PH1_DIR_PORT	DDRB

	#define PH2 			PB2
	#define PH2_PORT		PORTB
	#define PH2_DIR_PORT	DDRB

	#define PH3 			PA7
	#define PH3_PORT		PORTA
	#define PH3_DIR_PORT	DDRA

	#define S0				PA0
	#define S0_PORT 		PORTA
	#define S0_DIR_PORT		DDRA
	#define S0_VALUE_REG	PINA

	#define S1				PA1
	#define S1_PORT 		PORTA
	#define S1_DIR_PORT		DDRA
	#define S1_VALUE_REG	PINA

	#define S2				PA2
	#define S2_PORT 		PORTA
	#define S2_DIR_PORT		DDRA
	#define S2_VALUE_REG	PINA

	#define S3				PA3
	#define S3_PORT 		PORTA
	#define S3_DIR_PORT		DDRA
	#define S3_VALUE_REG	PINA


#endif /* HARDWARE_H_ */
