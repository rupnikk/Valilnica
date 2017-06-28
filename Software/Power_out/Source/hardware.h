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

	#define DDR_USI			DDRB
	#define PORT_USI		PORTB
	#define PIN_USI			PINB
	#define PORT_USI_SDA	PB0
	#define PORT_USI_SCL	PB2
	#define PIN_USI_SDA		PINB0
	#define PIN_USI_SCL		PINB2


	#define GRELEC 			PB3
	#define GRELEC_PORT		PORTB
	#define GRELEC_DIR_PORT	DDRB

	#define LUC 			PB4
	#define LUC_PORT		PORTB
	#define LUC_DIR_PORT	DDRB

	#define ZERO			PB1
	#define ZERO_PORT		PORTB
	#define ZERO_DIR_PORT	DDRB
	#define ZERO_VALUE_REG 	PINB
	#define ZERO_PCINT		PCINT1



#endif /* HARDWARE_H_ */
