#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <unistd.h>

#include "neural.h"


//int nerone(float input[3], float lenght[3])
//{
//	input[2] = 1;
//	float sum = 0;
//	for(int i = 0; i < 3; ++i)
//	{
//		sum += input[i] * lenght[i];
//	}
//	if(sum > 0)
//	{
//		return 1;
//	}
//	return 0;
//}
//
//int learn_one_value(float input[3], float lenght[3], int theoric_result)
//{
//	int result, cnt = 0;
//	printf("learn for value in : %lf; %lf", input[1], input[2]);
//	result = nerone(input, lenght);
//	while(result != theoric_result)
//	{
//		cnt++;
//		for(int i = 0; i < 3; ++i)
//		{
//			lenght[i] += NU * (theoric_result - result) * input[i];
//		}
//		result = nerone(input, lenght);
//	}
//	if(cnt > 0)
//	{
//		return 1;
//	}
//	return 0;
//}

//int main(void)
//{
//	float input[3], lenght[3]={0,0,0};
//	int condition;
//	do
//	{
//		condition = 0;
//		input[0] = 1;
//		input[1] = 1;
//		condition |= learn_one_value(input, lenght, 1);
//		input[0] = 0;
//		input[1] = 1;
//		condition |= learn_one_value(input, lenght, 0);
//		input[0] = 1;
//		input[1] = 0;
//		condition |= learn_one_value(input, lenght, 0);
//		input[0] = 0;
//		input[1] = 0;
//		condition |= learn_one_value(input, lenght, 0);
//	}while(condition == 1);
//
//	for(int i = 0; i < 3; ++i)
//	{
//		printf("%E\n", lenght[i]);
//	}
//}

void test_neral(neural neural_test, float *a, float *b)
{
	(*a) = 1;
	(*b) = 1;
	neural_set_value_to_not_calculate(&neural_test);
	neural_update_output(&neural_test);
	printf("%.0f\t%0.f\t=>  %.0f \n", (*a), (*b), neural_test.out_value);
	(*a) = 0;
	(*b) = 1;
	neural_set_value_to_not_calculate(&neural_test);
	neural_update_output(&neural_test);
	printf("%.0f\t%0.f\t=>  %.0f \n", (*a), (*b), neural_test.out_value);
	(*a) = 1;
	(*b) = 0;
	neural_set_value_to_not_calculate(&neural_test);
	neural_update_output(&neural_test);
	printf("%.0f\t%0.f\t=>  %.0f \n", (*a), (*b), neural_test.out_value);
	(*a) = 0;
	(*b) = 0;
	neural_set_value_to_not_calculate(&neural_test);
	neural_update_output(&neural_test);
	printf("%.0f\t%0.f\t=>  %.0f \n---------------------\n", (*a), (*b), neural_test.out_value);
	//usleep(200000);
}

int main(int argc, char **argv)
{
	neural and_neural;
	neural xor_nerals[3];
	float a, b;
	bool test;
	int i, u;
	int seed = time(NULL);
	if (argc > 1)
	{
		sscanf(argv[1], "%d", &seed);
	}
	srand(seed);
	printf("seed : %d\n", seed);
	initialise_neural(&and_neural, ((float)rand())/RAND_MAX);
	neural_new_sensor_connection(&and_neural, &a, ((float)rand())/RAND_MAX);
	neural_new_sensor_connection(&and_neural, &b, ((float)rand())/RAND_MAX);
	do
	{
		test = true;
		a = 0;
		b = 0;
		neural_set_value_to_not_calculate(&and_neural);
		neural_update_output(&and_neural);
		while(and_neural.out_value > 0.5)
		{
			test = false;
			and_neural.out_error = -and_neural.out_value;
			neural_set_error_to_not_calculate(&and_neural);
			neural_update_weigh(&and_neural);
			neural_set_value_to_not_calculate(&and_neural);
			neural_update_output(&and_neural);
		}
		a = 0;
		b = 1;
		neural_set_value_to_not_calculate(&and_neural);
		neural_update_output(&and_neural);
		while(and_neural.out_value > 0.5)
		{
			test = false;
			and_neural.out_error = - and_neural.out_value;
			neural_set_error_to_not_calculate(&and_neural);
			neural_update_weigh(&and_neural);
			neural_set_value_to_not_calculate(&and_neural);
			neural_update_output(&and_neural);
		}
		a = 1;
		b = 0;
		neural_set_value_to_not_calculate(&and_neural);
		neural_update_output(&and_neural);
		while(and_neural.out_value > 0.5)
		{
			test = false;
			and_neural.out_error = -and_neural.out_value;
			neural_set_error_to_not_calculate(&and_neural);
			neural_update_weigh(&and_neural);
			neural_set_value_to_not_calculate(&and_neural);
			neural_update_output(&and_neural);
		}
		a = 1;
		b = 1;
		neural_set_value_to_not_calculate(&and_neural);
		neural_update_output(&and_neural);
		while(and_neural.out_value < 0.5)
		{
			test = false;
			and_neural.out_error = 1 - and_neural.out_value;
			neural_set_error_to_not_calculate(&and_neural);
			neural_update_weigh(&and_neural);
			neural_set_value_to_not_calculate(&and_neural);
			neural_update_output(&and_neural);
		}

		//test_neral(and_neural, &a, &b);
	}while( !test);
	test_neral(and_neural, &a, &b);
	printf("end of learning and function\n");
//	 en of and neral

	for (i = 0; i < 3; ++i)
	{
		initialise_neural(&xor_nerals[i], ((float)rand())/RAND_MAX);
	}
	printf("end of initialyse nerals\n");
	neural_new_sensor_connection(&xor_nerals[0], &a, ((float)rand())/RAND_MAX);
	neural_new_sensor_connection(&xor_nerals[0], &b, ((float)rand())/RAND_MAX);
	neural_new_sensor_connection(&xor_nerals[1], &a, ((float)rand())/RAND_MAX);
	neural_new_sensor_connection(&xor_nerals[1], &b, ((float)rand())/RAND_MAX);
	neural_new_synapse(&xor_nerals[0],&xor_nerals[2], ((float)rand())/RAND_MAX);
	neural_new_synapse(&xor_nerals[1],&xor_nerals[2], ((float)rand())/RAND_MAX);
	do
	{
		test = true;
		a = 0;
		b = 0;
		for (i = 0; i < 3; ++i)
		{
			neural_set_value_to_not_calculate(&xor_nerals[i]);
		}
		neural_update_output(&xor_nerals[2]);
		while(xor_nerals[2].out_value > 0.5)
		{
			test = false;
			xor_nerals[2].out_error =  - xor_nerals[2].out_value;
			for (i = 0; i < 3; ++i)
			{
				neural_set_error_to_not_calculate(&xor_nerals[i]);
			}
			neural_update_weigh(&xor_nerals[0]);
			neural_update_weigh(&xor_nerals[1]);
			for (i = 0; i < 3; ++i)
			{
				neural_set_value_to_not_calculate(&xor_nerals[i]);
			}
			neural_update_output(&xor_nerals[2]);
		}
		a = 0;
		b = 1;
		for (i = 0; i < 3; ++i)
		{
			neural_set_value_to_not_calculate(&xor_nerals[i]);
		}
		neural_update_output(&xor_nerals[2]);
		while(xor_nerals[2].out_value < 0.5)
		{
			test = false;
			xor_nerals[2].out_error = 1 -xor_nerals[2].out_value;
			for (i = 0; i < 3; ++i)
			{
				neural_set_error_to_not_calculate(&xor_nerals[i]);
			}
			neural_update_weigh(&xor_nerals[0]);
			neural_update_weigh(&xor_nerals[1]);
			for (i = 0; i < 3; ++i)
			{
				neural_set_value_to_not_calculate(&xor_nerals[i]);
			}
			neural_update_output(&xor_nerals[2]);
		}
		a = 1;
		b = 0;
		for (i = 0; i < 3; ++i)
		{
			neural_set_value_to_not_calculate(&xor_nerals[i]);
		}
		neural_update_output(&xor_nerals[2]);
		while(xor_nerals[2].out_value < 0.5)
		{
			test = false;
			xor_nerals[2].out_error = 1 - xor_nerals[2].out_value;
			for (i = 0; i < 3; ++i)
			{
				neural_set_error_to_not_calculate(&xor_nerals[i]);
			}
			neural_update_weigh(&xor_nerals[0]);
			neural_update_weigh(&xor_nerals[1]);
			for (i = 0; i < 3; ++i)
			{
				neural_set_value_to_not_calculate(&xor_nerals[i]);
			}
			neural_update_output(&xor_nerals[2]);
		}
		a = 1;
		b = 1;
		for (i = 0; i < 3; ++i)
		{
			neural_set_value_to_not_calculate(&xor_nerals[i]);
		}
		neural_update_output(&xor_nerals[2]);
		while(xor_nerals[2].out_value > 0.5)
		{
			test = false;
			xor_nerals[2].out_error = -xor_nerals[2].out_value;
			for (i = 0; i < 3; ++i)
			{
				neural_set_error_to_not_calculate(&xor_nerals[i]);
			}
			neural_update_weigh(&xor_nerals[0]);
			neural_update_weigh(&xor_nerals[1]);
			for (i = 0; i < 3; ++i)
			{
				neural_set_value_to_not_calculate(&xor_nerals[i]);
			}
			neural_update_output(&xor_nerals[2]);
		}
	}while( !test );
	a = 1;
	b = 1;
	for (i = 0; i < 3; ++i)
	{
		neural_set_value_to_not_calculate(&xor_nerals[i]);
	}
	neural_update_output(&xor_nerals[2]);
	printf("test a=%f, b=%f, out = %.0f\t", a, b, xor_nerals[2].out_value);
	for (int i = 0; i < 3; ++i)
	{
//			printf("%5f|", xor_nerals[i].out_error);
		for (int u = 0; u < xor_nerals[i].in_table_size; ++u)
		{
			printf("%5f|", *(xor_nerals[i].in_value_table[u]));
		}
		printf("|");
	}
	printf("\t%5f|\n", xor_nerals[2].out_value);
	a = 0;
	b = 1;
	for (i = 0; i < 3; ++i)
	{
		neural_set_value_to_not_calculate(&xor_nerals[i]);
	}
	neural_update_output(&xor_nerals[2]);
	printf("test a=%f, b=%f, out = %.0f\t", a, b, xor_nerals[2].out_value);
	for (int i = 0; i < 3; ++i)
	{
//			printf("%5f|", xor_nerals[i].out_error);
		for (int u = 0; u < xor_nerals[i].in_table_size; ++u)
		{
			printf("%5f|", *(xor_nerals[i].in_value_table[u]));
		}
		printf("|");
	}
	printf("\t%5f|\n", xor_nerals[2].out_value);
	a = 1;
	b = 0;
	for (i = 0; i < 3; ++i)
	{
		neural_set_value_to_not_calculate(&xor_nerals[i]);
	}
	neural_update_output(&xor_nerals[2]);
	printf("test a=%f, b=%f, out = %.0f\t", a, b, xor_nerals[2].out_value);
	for (int i = 0; i < 3; ++i)
	{
//			printf("%5f|", xor_nerals[i].out_error);
		for (int u = 0; u < xor_nerals[i].in_table_size; ++u)
		{
			printf("%5f|", *(xor_nerals[i].in_value_table[u]));
		}
		printf("|");
	}
	printf("\t%5f|\n", xor_nerals[2].out_value);
	a = 0;
	b = 0;
	for (i = 0; i < 3; ++i)
	{
		neural_set_value_to_not_calculate(&xor_nerals[i]);
	}
	neural_update_output(&xor_nerals[2]);
	printf("test a=%f, b=%f, out = %.0f\t", a, b, xor_nerals[2].out_value);
	for (int i = 0; i < 3; ++i)
	{
//			printf("%5f|", xor_nerals[i].out_error);
		for (int u = 0; u < xor_nerals[i].in_table_size; ++u)
		{
			printf("%5f|", *(xor_nerals[i].in_value_table[u]));
		}
		printf("|");
	}
	printf("\t%5f|\n", xor_nerals[2].out_value);
	return 0;
}
