/*
 * sequence.c
 *
 * Created: 2018-04-17 10:51:47
 *  Author: Dell
 */ 

#define F_CPU 10000000L
#include "sequence.h"
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>

#define SEQ_SIZE 100

void output_value(int value);

seq_t* seq_create(int size)
{
	seq_t *new_seq = malloc(sizeof(seq_t));
	new_seq->array = calloc(size, sizeof(int));
	new_seq->beginning = (*new_seq).array;
	new_seq->size = 0;
	return new_seq;
}

void seq_display(seq_t* self)
{
	int i;
	int* array_p = self->array;
	for(i = 0; i <= self->size; i++)
	{
		output_value(*array_p);
		array_p++;
	}
	*self->array = *self->beginning;
}

void output_value(int value)
{
	PORTA = ~value;
	_delay_ms(1000);
	PORTA = 0xff;
}