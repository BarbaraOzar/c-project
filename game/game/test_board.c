/*
 * CFile1.c
 *
 * Created: 2018-04-22 11:33:34
 *  Author: Dell
 */ 

#include "test_board.h"

static char * test_board_turn_on_led0()
{
	volatile int result = 0, port_input = 0;
	board_t board = board_create(&result, &port_input);
	board_turn_on_led(board, 0);
	mu_assert("result != 0b11111110 ", result == 0b11111110);
	return 0;
}

static char * test_board_turn_on_led1()
{
	volatile int result = 0, port_input = 0;
	board_t board = board_create(&result, &port_input);
	board_turn_on_led(board, 1);
	mu_assert("result != 0b11111101 ", result == 0b11111101);
	return 0;
}

static char * test_board_turn_on_led5()
{
	volatile int result = 0, port_input = 0;
	board_t board = board_create(&result, &port_input);
	board_turn_on_led(board, 5);
	mu_assert("result != 0b11011111 ", result == 0b11011111);
	return 0;
}

static char * test_board_get_input0()
{
	volatile int input_pin = 0, port_output = 0;
	int input;
	board_t board = board_create(&port_output, &input_pin);
	input = board_get_input()
	mu_assert("result != 0; test_board_get_input0", input == 0);
}

static char * test_board_get_input1() 
{
	volatile int input_pin = 0, port_output = 0;
	int input;
	board_t board = board_create(&port_output, &input_pin);
	board_turn_on_led(board, 1);
	input = board_get_input()
	mu_assert("result != 1; test_board_get_input1", input == 1);
}

static char * test_board_get_input5()
{
	volatile int input_pin = 0, port_output = 0;
	int input;
	board_t board = board_create(&port_output, 0, &input_pin, 0);
	board_turn_on_led(board, 5);
	input = board_get_input()
	mu_assert("result != 5; test_board_get_input5", input == 5);
}

static char * test_board_get_input7()
{
	volatile int input_pin = 0, port_output = 0;
	int input;
	board_t board = board_create(&port_output, &input_pin);
	board_turn_on_led(board, 5);
	input = board_get_input()
	mu_assert("result != 5; test_board_get_input5", input == 5);
}

char * all_board_tests()
{
	mu_run_test(test_board_turn_on_led0);
	mu_run_test(test_board_turn_on_led1);
	mu_run_test(test_board_turn_on_led5);
	mu_run_test(test_board_get_input1);
	return 0;
}
