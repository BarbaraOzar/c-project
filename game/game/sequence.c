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


seq_t* seq_expand(seq_t *self)
{
	int i;
	seq_t *new_seq;  //variable creation    /* seq_t *new_seq= malloc(sizeof(seq_t)); //allocates memory for the expanded struct */

	int new_size = *self->size + 50 ; // access size field of self
	new_seq = seq_create(new_size);
	
	copy_seq(self, new_seq);
	/*new_seq->array = calloc(new_size, sizeof(int)); // i reserve new_size spaces of sizeOf(int) each of the new_size space 
	new_seq->beginning = (*new_seq).array;
	new_seq->size = 0; //cuz' you are not able to check the size of the array with pointer , must keep track of size*/
	
}

seq_t* copy_seq(seq_t *self, seq_t *new_self){
	int i;
	int *arrayInitial_p = self->array;
	int *array2_p = new_self->array;
	
	for(i = 0; i <= self->size; i++)
	{
		*array2_p = *arrayInitial_p;
		new_self->size++;	//cuz' you are not able to check the size of the array with pointer , must keep track of size
		arrayInitial_p++;
		array2_p++;	
	}
	
	*self->array = *self->beginning; //when reusing this array, the pointer is reseted to point to the beginning
	*new_self->array = *new_self->beginning;
	
	free(self->array);
	free(self);
	
	return new_self;
	
	
}

