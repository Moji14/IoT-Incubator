/*
 * dht11.h
 *
 *DHT11 libraty for ATmega4808
 *
 * Created: 28/03/2019 18:06:29
 *  Author: Mohamed Lanjri El Halimi email: moji14@hotmail.com
 *References:
 * - DHT-11 Library, by Charalampos Andrianakis on 18/12/11
 * - DHT Library 0x03 Davide Gironi, 2012
 */ 

//#include <stdio.h>
//#include <string.h>
//#include <avr/io.h>
#include <util/delay.h>
#include <atmel_start.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>

#include "dht11.h"

#define RX_LOW !RX_get_level()
#define RX_HIGH RX_get_level()
//#define BLUE_LED_ON BLUE_LED_set_level(false)
//#define BLUE_LED_OFF BLUE_LED_set_level(true)


void dht11_getdata(int *temperature, int *humidity){
		//atmel_start_init();
		uint8_t bits[5];
		uint8_t i,j = 0;
		uint8_t result;
		*temperature = 0;
		*humidity = 0;
		//sei();
			//Pin initialization
			RX_set_pull_mode(PORT_PULL_UP);
			RX_set_dir(PORT_DIR_OUT);
			RX_set_level(true);//Set pin level to 1=high
			//BLUE_LED_OFF;
			//Wait one second
			_delay_ms(1200);
			RX_set_level(false);//Set pin level to low for 18ms
			_delay_ms(180);
			RX_set_level(true);//Set pin level to high for 40us
			_delay_us(400);//Min 12-Max93  has to wait at least
			RX_set_dir(PORT_DIR_IN);//Set pin direction as input
			RX_set_pull_mode(PORT_PULL_UP);
			//RX_set_isc(PORT_ISC_INTDISABLE_gc);
			//_delay_us(40);//Wait for 40Us to check in the middle of response signal
			
			if (RX_LOW){
				_delay_us(800);//Wait 80us to check in the middle of the Pull-up signal

				//BLUE_LED_ON;
				if (RX_HIGH){
					//After Pull-up signal we'll receive 5 bytes of 8 bits of information
					
					_delay_us(800);// Wait to be in the middle of start to transmit 1-bit data signal

					//uint16_t timeoutcounter = 0;//Auxiliary variable to count time
					for (j=0; j<5; j++) { //Five times loop to get each byte
						result=0;//Auxiliary variable to save the
						for(i=0; i<8; i++) {//Second loop to read every bit
							if (RX_LOW){
								_delay_us(500);//Wait 50us
								//Determine what we have and then decide which delay use
								if (RX_HIGH){
									_delay_us(270);	//27
									if(RX_HIGH){
										result |= (1<<(7-i));//If we have "1" bit we store it and wait until it ends
										_delay_us(435);//43
									}
								}
							}
							else{
								//return -1;	
							}
						}
						bits[j] = result;
					}
					//check checksum
					if ((uint8_t)(bits[0] + bits[1] + bits[2] + bits[3]) == bits[4]) {
						//return temperature and humidity
						*temperature = bits[2];//2
						*humidity = bits[0];//0
						//return 0;
					}
					else{
						//return -1;
					}
				}
				else{
					//return -1;
				}
			}
			else{
				//return -1;
			}
}