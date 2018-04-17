/*
 * game.c
 *
 * Created: 2018-04-17 10:46:13
 * Author : Dell
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "atmega2560_drivers.h"


#ifdef TEST
int main(void)
{
	init_stdio(0, 10000000L);
	sei();
	printf("I'm in the wrong main");
	while(1)
	{
		
	}
}
#endif

