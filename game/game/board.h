/*
 * board.h
 *
 * Created: 2018-04-22 11:19:19
 *  Author: Dell
 */ 


#ifndef BOARD_H_
#define BOARD_H_

typedef struct board * board_t;

board_t board_create(volatile int *port);
void board_turn_on_led(board_t self, int number);



#endif /* BOARD_H_ */