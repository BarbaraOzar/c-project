/*
 * sequence.h
 *
 * Created: 2018-04-17 11:04:09
 *  Author: Dell
 */ 


#ifndef SEQUENCE_H_
#define SEQUENCE_H_

typedef struct seq * seq_t;

int* get_array(seq_t self);
int* get_beginning(seq_t self);
int get_size(seq_t self);
int get_max_size(seq_t self);
void increment_size(seq_t self);
void reset_array_p(seq_t self);

seq_t seq_create(int size);
void seq_destroy(seq_t self);

void seq_add_to(seq_t self, int value);
void seq_display(seq_t self);
seq_t seq_expand(seq_t self);
seq_t copy_seq(seq_t self, seq_t new_self);


#endif /* SEQUENCE_H_ */