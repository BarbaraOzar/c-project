/*
 * CFile1.c
 *
 * Created: 2018-04-22 11:33:34
 *  Author: Dell
 */ 

#include "test_board.h"
#include <stdio.h>

static char * test_board_turn_on_led0()
{
	volatile uint8_t result = 0;
	board_t board = board_create(&result, 0, 0, 0);
	board_clear(board);
	board_turn_on_led(board, 0);
	mu_assert("result != 0b11111110 ", result == 0b11111110);
	return 0;
}

static char * test_board_turn_on_led1()
{
	volatile uint8_t result = 0;
	board_t board = board_create(&result, 0, 0, 0);
	board_clear(board);
	board_turn_on_led(board, 1);
	mu_assert("result != 0b11111101 ", result == 0b11111101);
	return 0;
}

static char * test_board_turn_on_led5()
{
	volatile uint8_t result = 0;
	board_t board = board_create(&result, 0, 0, 0);
	board_clear(board);
	board_turn_on_led(board, 5);
	mu_assert("result != 0b11011111 ", result == 0b11011111);
	return 0;
}

static char * test_no_input()
{
	volatile uint8_t input_pin = 0b11111111, port_output = 0;
	int input;
	board_t board = board_create(&port_output, 0, &input_pin, 0);
	board_clear(board);
	input = board_get_input(board);
	mu_assert("result != -1; test_no_input", input == -1);
	return 0;
}

static char * test_board_get_input0() 
{
	volatile uint8_t input_pin = 0b11111110, port_output = 0;
	int input;
	board_t board = board_create(&port_output, 0, &input_pin, 0);
	input = board_get_input(board);
	mu_assert("result != 0; test_board_get_input0", input == 0);
	return 0;
}

static char * test_board_get_input5()
{
	volatile uint8_t input_pin = 0b11011111, port_output = 0;
	int input;
	board_t board = board_create(&port_output, 0, &input_pin, 0);
	board_turn_on_led(board, 5);
	input = board_get_input(board);
	mu_assert("result != 5; test_board_get_input5", input == 5);
	return 0;
}

static char * test_board_get_input_multiple_buttons()
{
	volatile uint8_t input_pin = 0b00111111, port_output = 0;
	int input;
	board_t board = board_create(&port_output, 0, &input_pin, 0);
	input = board_get_input(board);
	mu_assert("result != 7; test_board_get_input_multiple_buttons", input == 7);
	return 0;
}


char * all_board_tests()
{
	mu_run_test(test_board_turn_on_led0);
	mu_run_test(test_board_turn_on_led1);
	mu_run_test(test_board_turn_on_led5);
	mu_run_test(test_no_input);
	mu_run_test(test_board_get_input0);
	mu_run_test(test_board_get_input5);
	mu_run_test(test_board_get_input_multiple_buttons);
	return 0;
}
