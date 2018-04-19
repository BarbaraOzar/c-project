/*
 * sequence.c
 *
 * Created: 2018-04-17 10:51:47
 *  Author: Dell
 */ 

#include "sequence.h"
#include <stdlib.h>
#include <stdio.h>

#define SEQ_SIZE 100;

void display_seq(seq_t seq);

seq_t* seq_create(int size)
{
	seq_t *new_seq = malloc(sizeof(seq_t));
	new_seq->array = calloc(size, sizeof(int));
	new_seq->beginning = (*new_seq).array;
	return new_seq;
}

void seq_add_to(seq_t self, int value) 
{
	*(self).array = value;
	(self).array += 1;
}