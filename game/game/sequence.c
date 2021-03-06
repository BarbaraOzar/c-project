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
#include <avr/interrupt.h>
#include <avr/io.h>


struct seq {
	int *array;
	int max_size;
	int size;
};

void output_value(int value);

int* get_array(seq_t self)
{
	return self->array;
}

int get_size(seq_t self)
{
	return self->size;
}

int get_max_size(seq_t self)
{
	return self->max_size;
}

void increment_size(seq_t self)
{
	self->size++;
}

seq_t seq_create(int size)
{
	seq_t new_seq = (seq_t)malloc(sizeof(struct seq));
	new_seq->array = calloc(size, sizeof(int));
	new_seq->size = 0;
	new_seq->max_size = size;
	return new_seq;
}

void seq_add_to(seq_t self, int value) 
{
	if (get_size(self) == get_max_size(self)) {
		self = seq_expand(self);
	}
	
	int* array_p = get_array(self);
	array_p += get_size(self);
	*array_p = value;
	increment_size(self);
}

void seq_display(seq_t self, board_t board, int delay, int clear)
{
	seq_display_only(self, board, delay, clear);
	board_clear(board);
}

void seq_display_only(seq_t self, board_t board, int delay, int clear)
{
	int i, d;
	int* array_p = get_array(self);
	for(i = 0; i < get_size(self); i++)
	{
		d = delay;
		board_turn_on_led(board, *array_p);
		
		while(d > 0)
		{
			_delay_ms(100);
			d--;
		}
		
		if(clear)
		{
			board_clear(board);
			_delay_ms(200);
		}
		array_p++;
	}
}

seq_t seq_copy(seq_t self, seq_t new_self)
{
	int i;
	
	if(get_max_size(self) <= get_max_size(new_self))
	{
		int* array_p = get_array(self);
		int* new_array_p = get_array(new_self);
		
		for(i = 0; i < get_size(self); i++)
		{
			seq_add_to(new_self, *array_p);
			array_p++;
			new_array_p++;
		}
	
		free(self);
	}
	return new_self;
}

seq_t seq_expand(seq_t self)
{
	int new_size = get_max_size(self) + 50 ; // access size field of self
	seq_t new_seq = seq_create(new_size);
	
	seq_copy(self, new_seq);
	return new_seq;
}

int seq_compare(seq_t self, int value, int index) 
{
	int* array_p = get_array(self);
	array_p += index;
	if(*array_p == value) {
		return 1;
	}
	return 0;
}

int seq_get_value(seq_t self, int index)
{
	int* array_p = get_array(self);
	array_p += index;
	return *array_p;
}

void seq_destroy(seq_t self) 
{
	//free(self->array);
	//free(self);
}
