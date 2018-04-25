/*
 * board.h
 *
 * Created: 2018-04-22 11:19:19
 *  Author: Dell
 */ 


#ifndef BOARD_H_
#define BOARD_H_

typedef struct board * board_t;

board_t board_create(volatile int *port_output, volatile int *ddr_output, volatile int *input_pin, volatile int *ddr_input);
void board_turn_on_led(board_t self, int number);
int board_get_input(board_t self);
void board_wait_for_button_press(board_t self);
void board_clear(board_t self);

#endif /* BOARD_H_ */