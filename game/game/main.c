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

void ports_configuration();

#ifndef TEST
int main(void)
{
	ports_configuration();
	int i, value = 2;
	
	seq_t seq = seq_create(5);
	
	
	for(i = 0; i <= 5; i++)
	{
		seq.array = value;
		seq.array++;
		value+=2;
	}
	
	
	init_stdio(0, 10000000L);
	sei();
	
	printf("I'm in the wrong main");
	while(1)
	{
		
	}
}
#endif

void ports_configuration() 
{
	DDRA = 0xff;
	DDRB = 0x00;
	PORTA = 0xff;
}
