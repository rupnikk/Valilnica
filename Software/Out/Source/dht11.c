
//#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include "blink.h"
#include "dht11.h"

/*int main(void)
{
    uint8_t data [4];
    
    int8_t i;
    
    initDHT();
    
    if(fetchData(data))
    {
        for(i = data[2]; i >= 0; --i)
        {
            SET_BIT(PORTB,LED);
            _delay_ms(100);
            
            CLEAR_BIT(PORTB,LED);
            _delay_ms(500);
        }
    }

    return 0;
}*/

void initDHT(void)
{
    /* Set LED as output */
    //SET_BIT(DDRB,LED);
	//SET_BIT(DHT_PORT_OUT,LED);
    
    /* According to the DHT11's datasheet, the sensor needs about
       1-2 seconds to get ready when first getting power, so we
       wait
     */
    _delay_ms(2000);
}


//uint8_t fetchData(uint8_t* arr)
uint8_t fetchData(Senzor *sensor)
{
    char data[5];
    uint8_t cnt, check;
    int8_t i,j;
    //return 1;
    /******************* Sensor communication start *******************/
    
    /* Set data pin as output first */
    SETBIT(*(sensor->dir_port),sensor->pin);
    
    /* First we need milliseconds delay, so set clk/1024 prescaler */
    TCCR0B = 0x05;
    
    TCNT0 = 0;
    
     /* Clear bit for 20 ms */
 	//CLEAR_BIT(DHT_PORT_OUT,LED);
    //CLEAR_BIT(DHT_PORT_OUT,DHT_PIN);
    CLEARBIT(*(sensor->port), sensor->pin);
//     
 //   return 1;
//     /* Wait about 20 ms */
     while(TCNT0 < 160);
//     
//     /* Now set Timer0 with clk/8 prescaling.
//      Gives 1µs per cycle @8Mhz */
     TCCR0B = 0x02;
//     
    TCNT0 = 0;
//     
//     /* Pull high again */
    SETBIT(*(sensor->port),sensor->pin);
  // while(TCNT0 < 30);
//     /* And set data pin as input */
    CLEARBIT(*(sensor->dir_port),sensor->pin);
 	CLEARBIT(*(sensor->port), sensor->pin);
//     

// 	
 	TCNT0 = 0;
//     /* Wait for response from sensor, 20-40µs according to datasheet */
     while(BITSET(*(sensor->in_port),sensor->pin))
     { if (TCNT0 >= 60) return 0; }
     //return 1;
//     /************************* Sensor preamble *************************/
//     
     TCNT0 = 0;
//     
//     /* Now wait for the first response to finish, low ~80µs */
     while(!BITSET(*(sensor->in_port),sensor->pin))
     { if (TCNT0 >= 100) return 0; }
//     

     TCNT0 = 0;
//     
//     /* Then wait for the second response to finish, high ~80µs */
     while(BITSET(*(sensor->in_port),sensor->pin))
     { if (TCNT0 >= 100) return 0; }
//     /********************* Data transmission start **********************/
// 
//    

    for (i = 0; i < 5; i++)
    {
        for(j = 7; j >= 0; j--)
        {
            TCNT0 = 0;
            
            /* First there is always a 50µs low period */
            while(!BITSET(*(sensor->in_port),sensor->pin))
            { if (TCNT0 >= 70) { return 0;} }

            TCNT0 = 0;
            
            /* Then the data signal is sent. 26 to 28µs (ideally)
             indicate a low bit, and around 70µs a high bit */
            while(BITSET(*(sensor->in_port),sensor->pin))
            { if (TCNT0 >= 90) return 0; }
            
            /* Store the value now so that the whole checking doesn't
             move the TCNT0 forward by too much to make the data look
             bad */

            cnt = TCNT0;
            if ((cnt >=10) && (cnt <= 45))
            { CLEARBIT(data[i],j);}
            
            else if ((cnt > 45) && (cnt <= 85))
            { SETBIT(data[i],j); }
           
            else {return 0;}
			
        }
		
    }


// 	
//    
//     /********************* Sensor communication end *********************/
// 
     check = (data[0] + data[1] + data[2] + data[3]) & 0xFF;

// 	
    // return 1;
    if (check != data[4])return 0;
     //sensor->data[2] = 0x25;
//     
    for(i = 0; i < 4; i++)
    { sensor->data[i] = data[i]; }
   // SET_BIT(DHT_PORT_OUT,LED);
     return 1;
}
