/*
 * test_sequence.c
 *
 * Created: 2018-04-22 11:40:27
 *  Author: Dell
 */ 

#include "test_sequence.h"
#include <stdio.h>
#include "sequence.h"
#define F_CPU 10000000L
#include <util/delay.h>

static char * test_seq_create()
{
	int size = 10, i, value, *array_start;
	seq_t item = seq_create(size);
	
	array_start = get_array(item);
	
	for(i = 0; i < 10; i++)
	{
		value = *array_start;
		mu_assert("element != 0", value == 0);
		array_start++;
	}
	return 0;
}

static char * test_seq_add_zero () 
{
	int size = 5, value, *array_start;

	seq_t item = seq_create(size);
	seq_add_to(item, 0);
	
	array_start = get_array(item);
	value = *array_start;
	mu_assert("element != 0", value == 0);
	return 0;
}

static char * test_seq_add_one ()
{
	int size = 5, value, *array_start;
	seq_t item = seq_create(size);
	seq_add_to(item, 1);
	
	array_start = get_array(item);

	value = *array_start
	mu_assert("element != 1", value == 1);
		
	return 0;
}

static char * test_seq_add_multiple ()
{
	int size = 5, i, value, *array_start, control;
	seq_t item = seq_create(size);

	seq_add_to(item, 1);
	seq_add_to(item, 2);
	seq_add_to(item, 3);
		
	array_start = get_array(item);
	control = 1;
		
	for(i = 0; i < 3; i++)
	{
		value = *array_start;
		mu_assert("element != expected", value == control);
		array_start++;
		control++;
	}
		
	return 0;
}

static char * test_seq_add_beyond_capacity ()
{
	int size = 5;
	int i, value, control;
	seq_t item = seq_create(size);
	int* array_p = get_array(item);
	seq_add_to(item, 1);
	seq_add_to(item, 2);
	seq_add_to(item, 3);
	seq_add_to(item, 4);
	seq_add_to(item, 5);
	seq_add_to(item, 6);
	seq_add_to(item, 7);
	seq_add_to(item, 8);
	seq_add_to(item, 9);

	control = 1;
	
	for(i = 0; i < 6; i++)
	{
		value = *array_p;
		mu_assert("element != expected", value == control);
		array_p++;
		control++;
	}
	
	return 0;
}

static char * test_seq_copy()
{
	int size1 = 5, size2 = 10;
	int  i, value;
	int *array1_p, *array2_p;
		
	seq_t item1 = seq_create(size1);
	seq_t item2 = seq_create(size2);
	
	array1_p = get_array(item1);
	array2_p = get_array(item2);
	
	*array1_p = 3;
	array1_p++;
	increment_size(item1);
	*array1_p = 4;
	array1_p++;
	increment_size(item1);
	*array1_p = 5;
	array1_p++;
	increment_size(item1);
	*array1_p = 6;
	array1_p++;
	increment_size(item1);
	
	seq_copy(item1, item2);
	
	for(i = 3; i <= 6; i++) {
		value = *array2_p;
		mu_assert("elements are not equal", i == value);
		array2_p++;
	}
	return 0;
}

static char * test_expand_size()
{
	int value1, size1 = 5;
	seq_t item1 = seq_create(size1);
	item1 = seq_expand(item1);
	value1 = get_max_size(item1);
	
	mu_assert("\rSeq. has not expanded\n", value1 == 55);
	return 0;
}

static char * test_expand_elements()
{
	int size = 5;
	int i;
	seq_t item = seq_create(size);
	int* array_p = get_array(item);
	seq_add_to(item, 1);
	seq_add_to(item, 2);
	seq_add_to(item, 3);
	seq_add_to(item, 4);
	item = seq_expand(item);
	
	for (i = 1; i <= 4; i++)
	{
		mu_assert("values in arrays != test_expand_elements", *array_p == i);
		array_p++;
	}
	mu_assert("last value != 0 test_expand_elements", *array_p == 0);
	return 0;
}

static char * test_compare()
{
	int size = 5;
	int i, check;
	seq_t item = seq_create(size);
	
	seq_add_to(item, 1);
	seq_add_to(item, 2);
	seq_add_to(item, 3);
	seq_add_to(item, 4);
	
	for (i = 1; i <= 4; i++)
	{
		check = seq_compare(item, i, i-1);
		mu_assert("values in arrays != test_compares", check == 1);
	}
	return 0;
}

static char * test_compare_fail()
{
	int size = 5;
	int i, check;
	seq_t item = seq_create(size);
	
	seq_add_to(item, 1);
	seq_add_to(item, 2);
	seq_add_to(item, 3);
	seq_add_to(item, 4);
	
	for (i = 1; i <= 4; i++)
	{
		check = seq_compare(item, 10, i-1);
		mu_assert("values in arrays != test_compares", check == 0);
	}
	return 0;
}

static char * test_seq_get_value0()
{
	int size = 5;
	seq_t item = seq_create(size);
	seq_add_to(item, 1);
	seq_add_to(item, 2);
	seq_add_to(item, 3);
	seq_add_to(item, 4);
	int value = seq_get_value(item, 5);
	mu_assert("value != 0; test_seq_get_value0", value == 0);	
	return 0;
}

static char * test_seq_get_value1()
{
	int size = 5;
	seq_t item = seq_create(size);
	seq_add_to(item, 1);
	seq_add_to(item, 2);
	seq_add_to(item, 3);
	seq_add_to(item, 4);
	int value = seq_get_value(item, 1);
	mu_assert("value != 1; test_seq_get_value1", value == 1);
	return 0;
}

static char * test_seq_get_value_fail()
{
	int size = 5;
	seq_t item = seq_create(size);
	seq_add_to(item, 1);
	seq_add_to(item, 2);
	seq_add_to(item, 3);
	seq_add_to(item, 4);
	int value = seq_get_value(item, 2);
	mu_assert("value == 2; test_seq_get_value_fail", value != 2);
	return 0;
}

static char * test_seq_display_only0()
{
	volatile uint8_t result = 0;
	board_t board = board_create(&result, 0, 0, 0);
	board_clear(board);
	
	int size = 5;
	seq_t item = seq_create(size);
	seq_display_only(item, board, 1, 0);
	
	mu_assert("result != 0b11111111; test_seq_display_only0", result == 0b11111111);
	return 0;
}

static char * test_seq_display_only1()
{
	volatile uint8_t result = 0;
	board_t board = board_create(&result, 0, 0, 0);
	board_clear(board);
	
	int size = 5;
	seq_t item = seq_create(size);
	seq_display_only(item, board, 1, 0);
	seq_add_to(item, 0);
	
	mu_assert("result != 0b11111110; test_seq_display_only1", result == 0b11111110);
	return 0;
}

static char * test_seq_display_only_seq1()
{
	volatile uint8_t result = 0;
	board_t board = board_create(&result, 0, 0, 0);
	board_clear(board);
	
	int size = 5;
	seq_t item = seq_create(size);
	seq_display_only(item, board, 1, 0);
	seq_add_to(item, 1);
	seq_add_to(item, 2);
	seq_add_to(item, 3);
	
	mu_assert("result != 0b11110001; test_seq_display_only_seq1", result == 0b11110001);
	return 0;
}

static char * test_seq_display_only_seq2()
{
	volatile uint8_t result = 0;
	board_t board = board_create(&result, 0, 0, 0);
	board_clear(board);
	
	int size = 5;
	seq_t item = seq_create(size);
	seq_display_only(item, board, 1, 0);
	seq_add_to(item, 1);
	seq_add_to(item, 3);
	seq_add_to(item, 5);
	seq_add_to(item, 7);
	
	mu_assert("result != 0b01010101; test_seq_display_only_seq2", result == 0b01010101);
	return 0;
}

static char * test_seq_display_only_seq_fail()
{
	volatile uint8_t result = 0;
	board_t board = board_create(&result, 0, 0, 0);
	board_clear(board);
	
	int size = 5;
	seq_t item = seq_create(size);
	seq_display_only(item, board, 1, 1);
	seq_add_to(item, 1);
	seq_add_to(item, 2);
	seq_add_to(item, 3);
	
	mu_assert("result != 0b11110001; test_seq_display_seq_fail", result != 0b11110001);
	return 0;
}

char * all_sequence_tests()
{
	mu_run_test(test_seq_create);
	mu_run_test(test_seq_add_zero);
	mu_run_test(test_seq_add_one);
	mu_run_test(test_seq_add_multiple);
	mu_run_test(test_seq_copy);
	mu_run_test(test_expand_size);
	mu_run_test(test_seq_add_beyond_capacity);
	mu_run_test(test_expand_elements);
	mu_run_test(test_compare);
	mu_run_test(test_compare_fail);
	mu_run_test(test_seq_get_value0);
	mu_run_test(test_seq_get_value1);
	mu_run_test(test_seq_get_value_fail);
	mu_run_test(test_seq_display_only0);
	mu_run_test(test_seq_display_only1);
	mu_run_test(test_seq_display_only_seq1);
	mu_run_test(test_seq_display_only_seq2);
	mu_run_test(test_seq_display_only_seq_fail);
	return 0;
}