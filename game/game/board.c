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
	volatile int *port;
};

board_t board_create(volatile int *port)
{
	*port = 0xff;
	board_t new_board = (board_t)malloc(sizeof(struct board));
	new_board->port = port;
	return new_board;
}


void board_turn_on_led(board_t self, int number)
{
	*(self->port) &= ~(1<<number);
}
