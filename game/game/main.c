/*
 * game.c
 *
 * Created: 2018-04-17 10:46:13
 * Author : Dell
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "atmega2560_drivers.h"
#include "sequence.h"
#include <time.h>


#ifndef TEST
int main(void)
{

	//INTERRUPT SETUP
	PCICR ^= (1<<PCIE0);            // enabling interrupts for PCINT0 (portb)
	PCMSK0 ^= (1<<PB0) | (1<<PB7);  // enabling interrupts on port b bit 1 and 7
	
	init_stdio(0, 10000000L);
	sei();
	
	//random set up
	
	time_t msec = time(NULL) * 1000;
	srand((unsigned) time(&msec));
	
	//create Welcome sequence
	int i;
	seq_t welcome = seq_create(8);
	for(i=0; i<get_max_size(welcome); i++)
	{
		seq_add_to(welcome, i);
	}

	//create Error sequence
	seq_t error = seq_create(8);
	seq_add_to(error, 0);
	seq_add_to(error, 7);
	seq_add_to(error, 1);
	seq_add_to(error, 6);
	seq_add_to(error, 2);
	seq_add_to(error, 5);
	seq_add_to(error, 3);
	seq_add_to(error, 4);
		
	while(1)
	{
		int level=3, input, i, running=0, comparison, control=1 ;
		seq_t game_sequence = seq_create(20);
		for (i = 0 ; i<level ; i++)
		{ 
			seq_add_to(game_sequence, rand() % 8);
		}
		
		PORTA = 0xff;
		board_t b = board_create(&PORTA, &DDRA, &PINB, &DDRB);
		
		printf("\rdisplay welcome\n");
		
		seq_display(welcome, b, 7, 0);
		board_wait_for_button_press(b);
		
		while(control==1)
		{
			printf("\rgame sequence\n");
			seq_display(game_sequence, b, 10, 1);
			for(i = 0; i<get_size(game_sequence); i++)
			{
				board_wait_for_button_press(b);
				input = board_get_input(b);
				printf("\rinput %d\n", input);
				comparison = seq_compare(game_sequence, input, running++);
				if (comparison == 0)
				{
					control=0;
					seq_display(error, b, 4, 0);
					break;
				}
			}
			running=0;
			seq_add_to(game_sequence, rand() % 8 );
		}
			
	}
}

#endif



ISR(PCINT0_vect)
{
	uint8_t port_b_state = ~PINB;
	
	//board to be declared globally
	board_t board = board_create(PORTA, DDRA, PINB, DDRB);

	switch (port_b_state)
	{
		case ( (1<<PB0) | (1<<PB7) ):
		board_wait_for_button_press(board);
		break;
	}
}

