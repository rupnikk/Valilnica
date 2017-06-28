/*
 * usi_i2c_slave.h
 *
 *  Created on: 24. jan. 2017
 *      Author: urban
 */


// NEPREVERJENO !!!!!!!!!!!!!!!!!!!!!!!!

#ifndef USI_I2C_SLAVE_H
#define USI_I2C_SLAVE_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "hardware.h"

#define USI_SLAVE_REGISTER_COUNT 20

//Microcontroller Dependent Definition
//USI I2C Initialize
//  address - If slave, this parameter is the slave address
void USI_I2C_Init(char address);

#endif
