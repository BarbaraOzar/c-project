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
} seq_t;

seq_t* seq_create(int size);



#endif /* SEQUENCE_H_ */