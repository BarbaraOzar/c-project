/*
 * board.c
 *
 * Created: 2018-04-22 11:18:57
 *  Author: Dell
 */ 

#define F_CPU 10000000L
#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

struct board
{
	volatile int *port_output;
	volatile int *input_pin;
	volatile int *ddr_output;
	volatile int *ddr_input;
};

board_t board_create(volatile uint8_t *port_output, volatile uint8_t *ddr_output, volatile uint8_t *input_pin, volatile uint8_t *ddr_input)
{
	*ddr_output = 0xff;
	*ddr_input = 0x00;
	board_t new_board = (board_t)malloc(sizeof(struct board));
	new_board->port_output = port_output;
	new_board->ddr_output = ddr_output;
	new_board->input_pin = input_pin;
	new_board->ddr_input = ddr_input;
	return new_board;
}

void board_turn_on_led(board_t self, int number)
{
	*(self->port_output) &= ~(1<<number);
}

int board_get_input(board_t self)
{
	int i = 0; 
	uint8_t input = ~(*(self->input_pin));
	
	while(input != 0)
	{
		input = (input>>1);
		i++;
	}
	_delay_ms(500);
	return i-1;	
}

void board_wait_for_button_press(board_t self)
{
	while(*(self->input_pin) == 0xff)
	{}
}

void board_clear(board_t self)
{
	*(self->port_output) = 0xff;
}