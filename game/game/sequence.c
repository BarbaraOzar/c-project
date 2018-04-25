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

#include <util/delay.h>
struct seq {
	int *array;
	int *beginning;
	int max_size;
	int size;
};

void output_value(int value);

int* get_array(seq_t self)
{
	return self->array;
}

int* get_beginning(seq_t self)
{
	return self->beginning;
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

void reset_array_p(seq_t self)
{
	self->array = self->beginning;
}

void increment_array_p(seq_t self) {
	self->array++;
}

seq_t seq_create(int size)
{
	seq_t new_seq = (seq_t)malloc(sizeof(struct seq));
	new_seq->array = calloc(size, sizeof(int));
	new_seq->beginning = new_seq->array;
	new_seq->size = 0;
	new_seq->max_size = size;
	return new_seq;
}

void seq_add_to(seq_t self, int value) 
{
	if (self->size == self->max_size) {
		self = seq_expand(self);
	}
	
	reset_array_p(self);
	self->array += self->size;
	*(self->array) = value;
	increment_size(self);
	reset_array_p(self);
}

void seq_display(seq_t self)
{
	int i;
	int* array_p = self->array;
	for(i = 0; i <= self->size; i++)
	{
		output_value(*array_p);
		array_p++;
	}
	*(self->array) = *(self->beginning);
}

void output_value(int value)
{
	PORTA = ~value;
	_delay_ms(1000);
	PORTA = 0xff;
}

seq_t copy_seq(seq_t self, seq_t new_self)
{
	int i;
	reset_array_p(self);
	reset_array_p(new_self);
	
	for(i = 0; i < self->size; i++)
	{
		*new_self->array = *self->array;
		printf("\r value %d \n", *new_self->array);
		printf("\r value %d \n", *self->array);
		increment_size(new_self);
		increment_array_p(self);
		increment_array_p(new_self);
	}
	
	while(1) {
	//	printf("\r value %d \n", *self->array++);
	//	printf("\r value %d \n", *new_self->array++);
		_delay_ms(3000);
	}
	free(self);
	
	return new_self;
}

seq_t seq_expand(seq_t self)
{
	int new_size = self->size + 50 ; // access size field of self
	seq_t new_seq = seq_create(new_size);
	
	copy_seq(self, new_seq);
	return new_seq;
}
