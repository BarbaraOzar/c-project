/*
 * test.c
 *
 * Created: 2018-04-17 10:48:59
 *  Author: Dell
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "sequence.h"
#include "atmega2560_drivers.h"
#include "minunit.h"

int tests_run = 0;
 
static char * test_seq_create()
{
	printf("\rI'm in the function\n\r");
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
	
	array_start = get_beginning(item);
	value = *array_start;
	mu_assert("element != 0", value == 0);
	return 0;
}

static char * test_seq_add_one ()
{
	int size = 5,  value, *array_start;
	seq_t item = seq_create(size);
	seq_add_to(item, 1);
		
	array_start = get_beginning(item);
	value = *array_start;
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
		
	array_start = get_beginning(item);
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

static char * test_copy_seq()
{
	printf("\rIm in the copySeq\n");
	int size1 = 5, size2 =10;
	int  i , j, value1, value2;
	int *array_start1, *array_start2;
		
	seq_t struct1 = seq_create(size1);
	seq_t struct2 = seq_create(size2);
	
	array_start1 = get_array(struct1);
	array_start2 = get_array(struct2);
	
	for(i = 0; i < size1; i++)
	{
		*array_start1 = i;
		 array_start1++;
		 increment_size(struct1);
	}
	
	reset_array_p(struct1);
	
	copy_seq(struct1, struct2);
	
	for (j=0; j<size1; j++)
	{
		value1 = *array_start1;
		value2 = *array_start2;
		
		printf("\rVal1: %d\n" , value1);
		printf("\rVal2: %d\n" , value2);
		
		array_start1++;
		array_start2++;
		
		mu_assert("elements are not equal", value1 == value2);
		
		reset_array_p(struct1);
		reset_array_p(struct2);
	}
	return 0;
}

static char * all_tests()
{
	mu_run_test(test_seq_create);
	mu_run_test(test_seq_add_zero);
	mu_run_test(test_seq_add_one);
	mu_run_test(test_seq_add_multiple);
	mu_run_test(test_copy_seq);
	return 0;
}

#ifdef TEST
int main()
{
	init_stdio(0, 10000000L);
	sei();
	
	DDRA = 0xff;
	PORTA = 0xff;
	PORTA = ~2;
	
	char *result = all_tests();
	if (result != 0) {
		printf("error: %s\n\r", result);
	}
	else {
		printf("ALL TESTS PASSED\n\r");
	}

	printf("Tests run: %d\n", tests_run);

	while(1);
	return result != 0;
}
#endif