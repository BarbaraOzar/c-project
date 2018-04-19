/*
 * sequence.h
 *
 * Created: 2018-04-17 11:04:09
 *  Author: Dell
 */ 


#ifndef SEQUENCE_H_
#define SEQUENCE_H_

typedef struct {
	int *array;
	int *beginning;
	int size;
} seq_t;

seq_t* seq_create(int size);
void seq_destroy(seq_t self);

void seq_add_to(seq_t self, int value);
<<<<<<< HEAD
<<<<<<< HEAD
void seq_display(seq_t self);
void seq_expand(seq_t self);
=======
void seq_display(seq_t* self);

>>>>>>> master
=======
void seq_display(seq_t * self);
void seq_expand(seq_t self);
>>>>>>> a851e488c1251b595ffb40fe1cf787e42cedd9e3



#endif /* SEQUENCE_H_ */