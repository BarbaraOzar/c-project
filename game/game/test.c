/*
 * test.c
 *
 * Created: 2018-04-17 10:48:59
 *  Author: Dell
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "atmega2560_drivers.h"
#include "minunit.h"
#include <util/delay.h>
#include "test_board.h"  
#include "test_sequence.h"


int tests_run = 0;

static char * test_seq_add_beyond_capacity ()
{
	int size = 5;
	int i, value, control;
	seq_t item = seq_create(size);
	seq_add_to(item, 1);
	seq_add_to(item, 2);
	seq_add_to(item, 3);
	seq_add_to(item, 4);
	seq_add_to(item, 5);
	seq_add_to(item, 6);
	seq_add_to(item, 7);
	seq_add_to(item, 8);
	seq_add_to(item, 9);

	reset_array_p(item);
	control = 1;
	
	for(i = 0; i < 6; i++)
	{
		value = *get_array(item);
	//	if (control > 4) {
			printf("\r value %d \n", value);
			printf("\r control %d \n", control);
			printf("\r size %d \n", get_size(item));
	//	}
		mu_assert("element != expected", value == control);
		
		increment_array_p(item);
		control++;
	}
	
	return 0;
}

static char * test_copy_seq()
{
	int size1 = 5, size2 =10;
	int  i , value;
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
	
	copy_seq(item1, item2);
	
	for(i = 3; i <= 6; i++) {
		value = *array2_p;
		array2_p++;
		mu_assert("elements are not equal", i == value);
	}
	return 0;
}

static char * test_expand()
{
	printf("\r ExpandMethod is tested\n");
	
	/* int value1, size1 = 5;
	seq_t *struct1 = seq_create(size1);
	
	printf("\r Value: %d\n", value1);
	seq_expand(struct1);
	
	value1 = (*struct1).size;
	printf("\r Value: %d\n", value1);
	
	mu_assert("\rSeq. has expanded", value1 == 55);

	return 0; */
}

static char * all_tests()
{
	mu_run_test(test_seq_create); 
	mu_run_test(test_seq_add_zero);
	mu_run_test(test_seq_add_one);
	mu_run_test(test_seq_add_multiple);
	mu_run_test(test_copy_seq); 
	mu_run_test(test_seq_add_beyond_capacity);
	/*mu_run_test(test_expand);
	mu_run_suite(all_sequence_tests);
	mu_run_suite(all_board_tests);*/
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