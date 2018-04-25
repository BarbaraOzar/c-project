/*
 * test_sequence.c
 *
 * Created: 2018-04-22 11:40:27
 *  Author: Dell
 */ 

#include "test_sequence.h"
#include <stdio.h>
#include "sequence.h"

char * test_seq_create()
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

char * test_seq_add_zero () 
{
	int size = 5, value, *array_start;

	seq_t item = seq_create(size);
	seq_add_to(item, 0);
	
	array_start = get_beginning(item);
	value = *array_start;
	mu_assert("element != 0", value == 0);
	return 0;
}

char * test_seq_add_one ()
{
	int size = 5, value, *array_start;
	seq_t item = seq_create(size);
	seq_add_to(item, 1);
	
	array_start = get_beginning(item);

	value = *array_start
	mu_assert("element != 1", value == 1);
		
	return 0;
}

char * test_seq_add_multiple ()
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

char * test_seq_add_beyond_capacity ()
{
	int size = 5, i, value, *array_start, control;
	seq_t item = seq_create(size);
	seq_add_to(item, 1);
	seq_add_to(item, 2);
	seq_add_to(item, 3);
	seq_add_to(item, 4);
	seq_add_to(item, 5);
	seq_add_to(item, 6);
	
	array_start = get_beginning(item);
	control = 1;
	
	for(i = 0; i < 6; i++)
	{
		value = *array_start;
		mu_assert("element != expected", value == control);
		array_start++;
		control++;
	}
	
	return 0;
}

char * test_copy_seq()
{
	printf("\rIm in the copySeq\n");
	int size1 = 5, size2 =10;
	int  i , j, value1, value2;
	int *array1_p, *array2_p;
		
	seq_t struct1 = seq_create(size1);
	seq_t struct2 = seq_create(size2);
	
	array1_p = get_array(struct1);
	array2_p = get_array(struct2);
	
	/*for(i = 0; i < size1; i++)
	{
		*array1_p = i;
		 array1_p++;
		 increment_size(struct1);
	}*/
	
	*array1_p = 3;
	array1_p++;
	increment_size(struct1);
	*array1_p = 4;
	array1_p++;
	increment_size(struct1);
	
	copy_seq(struct1, struct2);
	
	value2 = *array2_p;
	
	printf("\rVal1: %d\n" , 3);
	printf("\rVal2: %d\n" , value2);
	
	array2_p++;
	
	mu_assert("elements are not equal", 3 == value2);
	
	value2 = *array2_p;
	
	printf("\rVal1: %d\n" , 4);
	printf("\rVal2: %d\n" , value2);
	
	array2_p++;
	
	mu_assert("elements are not equal", 4 == value2);
	return 0;
}

char * all_sequence_tests()
{
	mu_run_test(test_seq_create);
	mu_run_test(test_seq_add_zero);
	mu_run_test(test_seq_add_one);
	mu_run_test(test_seq_add_multiple);
	mu_run_test(test_copy_seq);
	mu_run_test(test_seq_add_beyond_capacity);
	//mu_run_test(test_copy_seq);
	return 0;
}