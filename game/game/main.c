/*
 * game.c
 *
 * Created: 2018-04-17 10:46:13
 * Author : Dell
 */ 

#define F_CPU 10000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "atmega2560_drivers.h"
#include "sequence.h"
#include <time.h>
#include <util/delay.h>

void wait_and_clear(board_t board);

#ifndef TEST
int main(void)
{
	init_stdio(0, 10000000L);
	sei();
	
	// random generator set up
	time_t msec = time(NULL) * 1000;
	srand((unsigned) time(&msec));
	
	// create welcome sequence
	int i;
	seq_t welcome = seq_create(8);
	for(i = 0; i < get_max_size(welcome); i++)
	{
		seq_add_to(welcome, i);
	}

	// create error sequence
	seq_t error = seq_create(8);
	seq_add_to(error, 0);
	seq_add_to(error, 7);
	seq_add_to(error, 1);
	seq_add_to(error, 6);
	seq_add_to(error, 2);
	seq_add_to(error, 5);
	seq_add_to(error, 3);
	seq_add_to(error, 4);
		
	// set up board struct
	PORTA = 0xff;
	board_t board = board_create(&PORTA, &DDRA, &PINB, &DDRB);
	
	while(1)
	{
		int level = 3, input, running = 0, comparison, game_on = 1;
		
		// set up sequence struct
		seq_t game_sequence = seq_create(20);
		for (i = 0 ; i < level ; i++)
		{ 
			seq_add_to(game_sequence, rand() % 8);
		}
		
		// welcome
		seq_display(welcome, board, 3, 0);
		board_wait_for_button_press(board);
		
		// game
		while(game_on == 1)
		{
			seq_display(game_sequence, board, 7, 1);
			
			for(i = 0; i < get_size(game_sequence); i++)
			{
				board_wait_for_button_press(board);
				input = board_get_input(board);
				comparison = seq_compare(game_sequence, input, running++);
				
				if (comparison == 0)
				{
					game_on = 0;
					board_turn_on_led(board, seq_get_value(game_sequence, --running));
					wait_and_clear(board);
					seq_display(error, board, 3, 0);
					break;
				}
			}
			running = 0;
			seq_add_to(game_sequence, rand() % 8 );
		}
		board_clear(board);
		seq_destroy(game_sequence);
	}
	seq_destroy(welcome);
	seq_destroy(error);
}
#endif

void wait_and_clear(board_t board)
{
	_delay_ms(800);
	board_clear(board);
	_delay_ms(800);
}

