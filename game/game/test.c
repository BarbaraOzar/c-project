/*
 * test.c
 *
 * Created: 2018-04-17 10:48:59
 *  Author: Dell
 */ 

#ifdef TEST

#include <avr/io.h>
#include <avr/interrupt.h>
#include "atmega2560_drivers.h"
#include "minunit.h"
#include <util/delay.h>
#include "test_board.h"  
#include "test_sequence.h"


int tests_run = 0;
 
static char * all_tests() 
{
	mu_run_suite(all_sequence_tests);
	mu_run_suite(all_board_tests);
	return 0;
}

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