/*
 * CFile1.c
 *
 * Created: 2018-04-22 11:33:34
 *  Author: Dell
 */ 

#include "test_board.h"

char * test_board_turn_on_led0()
{
	volatile int result = 0;
	board_t board = board_create(&result);
	board_turn_on_led(board, 0);
	mu_assert("result != 0b11111110 ", result == 0b11111110);
	return 0;
}

char * test_board_turn_on_led1()
{
	volatile int result = 0;
	board_t board = board_create(&result);
	board_turn_on_led(board, 1);
	mu_assert("result != 0b11111101 ", result == 0b11111101);
	return 0;
}

char * all_board_tests()
{
	mu_run_test(test_board_turn_on_led0);
	mu_run_test(test_board_turn_on_led1);
	
	return 0;
}
