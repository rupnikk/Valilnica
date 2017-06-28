
#ifndef _dht11_h
#define _dht11_h

#include "hardware.h"
#include "bittop.h"
/*#define DHT_PORT_OUT PORTB
#define DHT_PORT_IN PINB
#define DHT_PIN 6

#define LED 3
*/

/*#define SET_BIT(byte, bit) ((byte) |= (1UL << (bit)))

#define CLEAR_BIT(byte,bit) ((byte) &= ~(1UL << (bit)))

#define IS_SET(byte,bit) (((byte) & (1UL << (bit))) >> (bit))

#include <stdint.h>*/

void initDHT(void);

uint8_t fetchData(Senzor* sensor);

#endif
