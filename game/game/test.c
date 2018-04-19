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
	seq_t* item = seq_create(size);
	
	array_start = (*item).array;
	
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
	
}

static char * all_tests()
{
	mu_run_test(test_seq_create);
	return 0;
}

#ifndef TEST
int main()
{
	init_stdio(0, 10000000L);
	sei();
	
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