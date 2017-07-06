

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

// definiranje naslovov I2C
#define OUT 	0x40
#define POW_OUT	0x41


// definicije internih naslovov za OUT


#define VENT			0x00
#define S0_H			0x01
#define S0_T			0x02
#define S1_H			0x03
#define S1_T			0x04
#define S2_H			0x05
#define S2_T			0x06
#define ERROR			0x07
#define WTCH			0x08
#define STEP_LOAD		0x09
#define STEP_POSW_UP	0x0A
#define STEP_POSW_DOWN	0x0B
#define STEP_POS_UP 	0x0C
#define STEP_POS_DOWN 	0x0D

// definicije internih naslovov za POW_OUT

#define HEAT		0x00
#define HEAT_DUTY	0x01
#define VENT_POW 	0x02
#define VENT_DUTY	0x03
#define ERROR_POW	0x04
#define WTCH_POW	0x05

int main (void)
{

	int sens = wiringPiI2CSetup(OUT);
	int pow= wiringPiI2CSetup(POW_OUT);

	uint8_t temp[3];
	uint8_t hum[3];
	uint8_t temp_max;
	uint8_t temp_min:
	uint8_t max_t=33; 
	uint8_t min_t=30;

	time_t cnt=10;
	time_t cnt2=2;


	uint8_t pos=1;
	uint8_t dir=1;
	uint8_t step_cnt;
	uint8_t turning=1;
	uint8_t error_sens=0;
	uint8_t error_pow=0;

	uint8_t days =21;
	uint8_t not_turn_days=3;


    time_t sec= time(NULL);
    
    if(sec!= -1)
        printf("The current time is (%ju seconds since the Epoch)\n",(uintmax_t)sec);

	time_t sec_tmp=sec;
	time_t sec_tmp2=sec;
	
	for( ; ; ){	
	
		sleep(1);
		//wiringPiI2CWriteReg8 (sens, WTCH, 0x01) ;
		//wiringPiI2CWriteReg8 (pow, WTCH_POW, 0x01) ;
		
		sec=time(NULL);	
		 if(sec != -1) {
			if ((sec-sec_tmp)>=cnt && turning==1) {
				sec_tmp=sec;

				//0x02000 == cca. 90 stopinj
				switch(pos){
					case 0: pos_down=0x00;
							pos_up=0x00;
							if (last==1)pos=1
							else pos=2;
							break;

					case 1: pos_down=0x00;
							pos_up=0x02;
							turning=0;
							break;

					case 2: pos_down=0x00;
							pos_up=0x04;
							if (last==1)pos=1
							else pos=0;
							break;
				}
				wiringPiI2CWriteReg8 (sens, STEP_POS_UP, pos_up) ;
				wiringPiI2CWriteReg8 (sens, STEP_POS_DOWN, pos_down) ;
				wiringPiI2CWriteReg8 (sens, STEP_LOAD, 0x01) ;

			}
			
			if ((sec-sec_tmp2)>=cnt2) {
				sec_tmp2=sec;

				temp[0]=wiringPiI2CReadReg8(sens,  S0_T);
				temp[1]=wiringPiI2CReadReg8(sens,  S1_T);
				temp[2]=wiringPiI2CReadReg8(sens,  S2_T);
				//temp[3]=wiringPiI2CReadReg8(sens,  S3_T);
		
				printf("T1=%u, T2=%u, T3=%u\n", temp[0], temp[1], temp[2]);
				

				hum[0]=wiringPiI2CReadReg8(sens,  S0_H);
				hum[1]=wiringPiI2CReadReg8(sens,  S1_H);
				hum[2]=wiringPiI2CReadReg8(sens,  S2_H);
				//hum[3]=wiringPiI2CReadReg8(sens,  S3_H);

				printf("H1=%u, H2=%u, H3=%u\n", hum[0], hum[1], hum[2]);
			}			
		}
		else{
			printf("There might be a time problem\n");
		}


		temp_max=temp[2];
		temp min=temp[0];

		hum_av=(hum[0]+hum[1]+hum[2])/3;
		
		if (temp_max < min_t)
		{
			wiringPiI2CWriteReg8 (pow, HEAT, 0x01) ;
			wiringPiI2CWriteReg8 (pow, VENT_POW, 0x01) ;
		}
		else if(temp_max > max_t && temp_max-temp_min > 4){
			wiringPiI2CWriteReg8 (pow, HEAT, 0x00) ;
			wiringPiI2CWriteReg8 (pow, VENT_POW, 0x01) ;
		}
		else{
			wiringPiI2CWriteReg8 (pow, HEAT, 0x00) ;
			wiringPiI2CWriteReg8 (pow, VENT_POW, 0x00) ;			
		}

		error_sens=wiringPiI2CReadReg8(sens,  ERROR);
		error_pow=wiringPiI2CReadReg8(pow,  ERROR_POW);
		if (error_sens==0x01 || error_pow==0x01){
			wiringPiI2CWriteReg8 (pow, HEAT, 0x00) ;
			wiringPiI2CWriteReg8 (pow, VENT_POW, 0x00) ;
		}
	}
  return 0 ;
}
