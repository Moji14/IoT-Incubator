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
//#include <avr/io.h>


#ifndef DHT11_H_
#define DHT11_H_

void dht11_getdata(int *temperature, int *humidity);

#endif /* DHT11_H_ */