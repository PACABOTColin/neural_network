#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#include "neural.h"
#include "toolbox.h"
#include "file.h"

#define training_size (928682)

extern float training[training_size];

#define nombre_couche (1)
#define network_size (sum_suite_al(nombre_couche))
#define sum_suite_al(n) ((n)*((n)+1)/2)

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
	printf("%.0f\t%0.f\t=>  %.0f \n---------------------\n", (*a), (*b),
		   neural_test.out_value);
	// usleep(200000);
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
	initialise_neural(&and_neural, ((float)rand()) / RAND_MAX, sigmoid,
					  d_sigmoid, 0);
	neural_new_sensor_connection(&and_neural, &a, ((float)rand()) / RAND_MAX);
	neural_new_sensor_connection(&and_neural, &b, ((float)rand()) / RAND_MAX);
	 do
	 {
	 test = true;
	 a = 0;
	 b = 0;
	 neural_set_value_to_not_calculate (&and_neural);
	 neural_update_output (&and_neural);
	 while (and_neural.out_value > 0.5)
	 {
	 test = false;
	 and_neural.out_error = -and_neural.out_value;
	 neural_set_error_to_not_calculate (&and_neural);
	 neural_set_weight_to_not_calculate (&and_neural);
	 neural_set_value_to_not_calculate (&and_neural);
	 neural_update_weigh (&and_neural);
	 neural_update_output (&and_neural);
	 }
	 a = 0;
	 b = 1;
	 neural_set_value_to_not_calculate (&and_neural);
	 neural_update_output (&and_neural);
	 while (and_neural.out_value > 0.5)
	 {
	 test = false;
	 and_neural.out_error = -and_neural.out_value;
	 neural_set_error_to_not_calculate (&and_neural);
	 neural_set_weight_to_not_calculate (&and_neural);
	 neural_set_value_to_not_calculate (&and_neural);
	 neural_update_weigh (&and_neural);
	 neural_update_output (&and_neural);
	 }
	 a = 1;
	 b = 0;
	 neural_set_value_to_not_calculate (&and_neural);
	 neural_update_output (&and_neural);
	 while (and_neural.out_value > 0.5)
	 {
	 test = false;
	 and_neural.out_error = -and_neural.out_value;
	 neural_set_error_to_not_calculate (&and_neural);
	 neural_set_weight_to_not_calculate (&and_neural);
	 neural_set_value_to_not_calculate (&and_neural);
	 neural_update_weigh (&and_neural);
	 neural_update_output (&and_neural);
	 }
	 a = 1;
	 b = 1;
	 neural_set_value_to_not_calculate (&and_neural);
	 neural_update_output (&and_neural);
	 while (and_neural.out_value < 0.5)
	 {
	 test = false;
	 and_neural.out_error = 1 - and_neural.out_value;
	 neural_set_error_to_not_calculate (&and_neural);
	 neural_set_weight_to_not_calculate (&and_neural);
	 neural_set_value_to_not_calculate (&and_neural);
	 neural_update_weigh (&and_neural);
	 neural_update_output (&and_neural);
	 }

	 //test_neral(and_neural, &a, &b);
	 }
	 while (!test);
	 test_neral (and_neural, &a, &b);
	 printf ("end of learning and function\n");
	 // en of and neral
	 sleep (3);

	for (i = 0; i < 3; ++i)
	{
		initialise_neural(&xor_nerals[i], ((float)rand()) / RAND_MAX,
						  sigmoid, d_sigmoid, i + 1);
	}
	neural_new_sensor_connection(&xor_nerals[0], &a, ((float)rand()) / RAND_MAX);
	neural_new_sensor_connection(&xor_nerals[0], &b, ((float)rand()) / RAND_MAX);
	neural_new_sensor_connection(&xor_nerals[1], &a, ((float)rand()) / RAND_MAX);
	neural_new_sensor_connection(&xor_nerals[1], &b, ((float)rand()) / RAND_MAX);
	neural_new_synapse(&xor_nerals[0], &xor_nerals[2], ((float)rand()) / RAND_MAX);
	neural_new_synapse(&xor_nerals[1], &xor_nerals[2], ((float)rand()) / RAND_MAX);
	do
	{
		test = true;
		a = 0;
		b = 0;
		for (i = 0; i < 3; ++i)
		{
			neural_set_error_to_not_calculate(&xor_nerals[i]);
			neural_set_weight_to_not_calculate(&xor_nerals[i]);
			neural_set_value_to_not_calculate(&xor_nerals[i]);
		}
		neural_update_output(&xor_nerals[2]);
		while (xor_nerals[2].out_value > 0.5)
		{
			test = false;
			xor_nerals[2].out_error = -xor_nerals[2].out_value;
			for (i = 0; i < 3; ++i)
			{
				neural_set_error_to_not_calculate(&xor_nerals[i]);
				neural_set_weight_to_not_calculate(&xor_nerals[i]);
				neural_set_value_to_not_calculate(&xor_nerals[i]);
			}
			neural_update_weigh(&xor_nerals[0]);
			neural_update_weigh(&xor_nerals[1]);
			for (i = 0; i < 3; ++i)
			{
				neural_set_error_to_not_calculate(&xor_nerals[i]);
				neural_set_weight_to_not_calculate(&xor_nerals[i]);
				neural_set_value_to_not_calculate(&xor_nerals[i]);
			}
			neural_update_output(&xor_nerals[2]);
		}
		a = 0;
		b = 1;
		for (i = 0; i < 3; ++i)
		{
			neural_set_error_to_not_calculate(&xor_nerals[i]);
			neural_set_weight_to_not_calculate(&xor_nerals[i]);
			neural_set_value_to_not_calculate(&xor_nerals[i]);
		}
		neural_update_output(&xor_nerals[2]);
		while (xor_nerals[2].out_value < 0.5)
		{
			test = false;
			xor_nerals[2].out_error = 1 - xor_nerals[2].out_value;
			for (i = 0; i < 3; ++i)
			{
				neural_set_error_to_not_calculate(&xor_nerals[i]);
				neural_set_weight_to_not_calculate(&xor_nerals[i]);
				neural_set_value_to_not_calculate(&xor_nerals[i]);
			}
			neural_update_weigh(&xor_nerals[0]);
			neural_update_weigh(&xor_nerals[1]);
			for (i = 0; i < 3; ++i)
			{
				neural_set_error_to_not_calculate(&xor_nerals[i]);
				neural_set_weight_to_not_calculate(&xor_nerals[i]);
				neural_set_value_to_not_calculate(&xor_nerals[i]);
			}
			neural_update_output(&xor_nerals[2]);
		}
		a = 1;
		b = 0;
		for (i = 0; i < 3; ++i)
		{
			neural_set_error_to_not_calculate(&xor_nerals[i]);
			neural_set_weight_to_not_calculate(&xor_nerals[i]);
			neural_set_value_to_not_calculate(&xor_nerals[i]);
		}
		neural_update_output(&xor_nerals[2]);
		while (xor_nerals[2].out_value < 0.5)
		{
			test = false;
			xor_nerals[2].out_error = 1 - xor_nerals[2].out_value;
			for (i = 0; i < 3; ++i)
			{
				neural_set_error_to_not_calculate(&xor_nerals[i]);
				neural_set_weight_to_not_calculate(&xor_nerals[i]);
				neural_set_value_to_not_calculate(&xor_nerals[i]);
			}
			neural_update_weigh(&xor_nerals[0]);
			neural_update_weigh(&xor_nerals[1]);
			for (i = 0; i < 3; ++i)
			{
				neural_set_error_to_not_calculate(&xor_nerals[i]);
				neural_set_weight_to_not_calculate(&xor_nerals[i]);
				neural_set_value_to_not_calculate(&xor_nerals[i]);
			}
			neural_update_output(&xor_nerals[2]);
		}
		a = 1;
		b = 1;
		for (i = 0; i < 3; ++i)
		{
			neural_set_error_to_not_calculate(&xor_nerals[i]);
			neural_set_weight_to_not_calculate(&xor_nerals[i]);
			neural_set_value_to_not_calculate(&xor_nerals[i]);
		}
		neural_update_output(&xor_nerals[2]);
		while (xor_nerals[2].out_value > 0.5)
		{
			test = false;
			xor_nerals[2].out_error = -xor_nerals[2].out_value;
			for (i = 0; i < 3; ++i)
			{
				neural_set_error_to_not_calculate(&xor_nerals[i]);
				neural_set_weight_to_not_calculate(&xor_nerals[i]);
				neural_set_value_to_not_calculate(&xor_nerals[i]);
			}
			neural_update_weigh(&xor_nerals[0]);
			neural_update_weigh(&xor_nerals[1]);
			for (i = 0; i < 3; ++i)
			{
				neural_set_error_to_not_calculate(&xor_nerals[i]);
				neural_set_weight_to_not_calculate(&xor_nerals[i]);
				neural_set_value_to_not_calculate(&xor_nerals[i]);
			}
			neural_update_output(&xor_nerals[2]);
		}
		for (i = 0; i < 3; ++i)
		{
			for (u = 1; u < xor_nerals[i].in_table_size; ++u)
			{
				printf("%8f,", xor_nerals[i].coef_table[u]);
			}
			printf("|");
		}
		printf("\n");
	}
	while (!test);

	a = 1;
	b = 1;
	for (i = 0; i < 3; ++i)
	{
		neural_set_error_to_not_calculate(&xor_nerals[i]);
		neural_set_weight_to_not_calculate(&xor_nerals[i]);
		neural_set_value_to_not_calculate(&xor_nerals[i]);
	}
	neural_update_output(&xor_nerals[2]);
	printf("test a=%f, b=%f, out = %f\n", a, b, xor_nerals[2].out_value);
	a = 0;
	b = 1;
	for (i = 0; i < 3; ++i)
	{
		neural_set_error_to_not_calculate(&xor_nerals[i]);
		neural_set_weight_to_not_calculate(&xor_nerals[i]);
		neural_set_value_to_not_calculate(&xor_nerals[i]);
	}
	neural_update_output(&xor_nerals[2]);
	printf("test a=%f, b=%f, out = %f\n", a, b, xor_nerals[2].out_value);
	a = 1;
	b = 0;
	for (i = 0; i < 3; ++i)
	{
		neural_set_error_to_not_calculate(&xor_nerals[i]);
		neural_set_weight_to_not_calculate(&xor_nerals[i]);
		neural_set_value_to_not_calculate(&xor_nerals[i]);
	}
	neural_update_output(&xor_nerals[2]);
	printf("test a=%f, b=%f, out = %f\n", a, b, xor_nerals[2].out_value);
	a = 0;
	b = 0;
	for (i = 0; i < 3; ++i)
	{
		neural_set_error_to_not_calculate(&xor_nerals[i]);
		neural_set_weight_to_not_calculate(&xor_nerals[i]);
		neural_set_value_to_not_calculate(&xor_nerals[i]);
	}
	neural_update_output(&xor_nerals[2]);
	printf("test a=%f, b=%f, out = %f\n", a, b, xor_nerals[2].out_value);
	return 0;

	// float input [network_size]= {};
	// int i, y = 0, sum;
	// srand(time(NULL));
	// neural *network;
	// 
	// for (i = 0; i < training_size; ++i) {
	// training[i]= 80.20;
	// }
	// 
	// network = malloc(sizeof(neural) * (network_size)); // alloc mem for
	// neural network
	// 
	// for (i = 0; i < network_size; ++i) // init neurals
	// {
	// if (i == 0)
	// {
	// initialise_neural(&network[i], (float)rand() * 2.0/ RAND_MAX - 1, tang, 
	// d_tang, i);
	// }
	// else
	// {
	// initialise_neural(&network[i], (float)rand() * 2.0/ RAND_MAX - 1,
	// sigmoid, d_sigmoid, i);
	// }
	// }
	// /*
	// * initialyse all the neural connection
	// * n 0
	// * ---------------------+
	// * o o o o o o o o ... o | n
	// * \|\|\|\|\|\|\|\...\| |
	// * o o o o o o o ... o | n-1
	// * \|\|\|\|\|\|\...\| | n-2
	// * o o o o o o ... o | n-3
	// * \|\|\|\|\|\...\| |
	// * o o o o o ... o |
	// * \|\|\|\|\...\| |
	// * o o o o ... o |
	// * \|\|\|\...\| |
	// * o o o ... o |
	// * \|\|\...\| |
	// * o o ... o |
	// * \|\...\| |
	// * o ... o |
	// * \...\| |
	// * : |
	// * : |
	// * o o | 1
	// * \| |
	// * o | 0
	// */
	// sum = 0;
	// for (i = 0; i < nombre_couche - 1; ++i)
	// {
	// sum += i;
	// for (y = 0; y <= i; ++y)
	// {
	// printf("sum = %3d\t i= %3d\t link : %2d %2d & %2d\n", sum, i, sum + y,
	// sum + y + i + 1, sum + y + i + 2);
	// neural_new_synapse(&network[sum + y + i + 1], &network[sum + y],
	// (float)rand() * 2.0/ RAND_MAX - 1);
	// neural_new_synapse(&network[sum + y + i + 2], &network[sum + y],
	// (float)rand() * 2.0/ RAND_MAX - 1);
	// 
	// }
	// }
	// for (i = network_size - sum_suite_al(nombre_couche - 1); i <
	// network_size; ++i)
	// {
	// neural_new_sensor_connection(&network[i], &input[i], (float)rand() *
	// 2.0/ RAND_MAX - 1);
	// }
	// sum = 0;
	// while(1)
	// {
	// for (i = 0; i < training_size - nombre_couche - 1; ++i)
	// {
	// memcpy(input, &training[i], sizeof(input));
	// for (y = 0; y < network_size; ++y) {
	// neural_set_error_to_not_calculate(&network[y]);
	// neural_set_value_to_not_calculate(&network[y]);
	// neural_set_weight_to_not_calculate(&network[y]);
	// }
	// neural_update_output(&network[0]);
	// network[0].out_error = training[i + nombre_couche + 1] -
	// network[0].out_value;
	// printf("%3d out %f, error = %f\n", i, network[0].out_value,
	// network[0].out_error);
	// neural_update_weigh(&network[0]);
	// }
	// sleep(10);
	// sum ++;
	// }

	// for(ii=0; ii < training_size - network_size; ++ii)
	// {
	// 
	// do {
	// blanc = 1;
	// noir = 1;
	// y=0;
	// for (i = 0; i < network_size; ++i)
	// {
	// initialise_neural(&network[i],(float)rand() * 20.0/ RAND_MAX - 10,
	// sigmoid, d_sigmoid);
	// }
	// for (u = 0; u < nombre_couche; ++u)
	// {
	// for (i = 0; i < nombre_neuronne_couche; ++i)
	// {
	// if(u == 0)
	// {
	// neural_new_sensor_connection(&network[i],&value1, );
	// neural_new_sensor_connection(&network[i],&value2, (float)rand() * 2.0/
	// RAND_MAX - 1);
	// }
	// else
	// {
	// for (y = 0; y < nombre_neuronne_couche; ++y)
	// {
	// neural_new_synapse(&network[(u - 1) * nombre_neuronne_couche + y],
	// &network[u * nombre_neuronne_couche + i], (float)rand() * 2.0/ RAND_MAX 
	// - 1);
	// }
	// }
	// }
	// }
	// for (i = 0; i < nombre_neuronne_couche; ++i)
	// {
	// neural_new_synapse(&network[(nombre_couche -1) * nombre_neuronne_couche 
	// + i], &network[network_size - 1], (float)rand() * 2.0/ RAND_MAX - 1);
	// }
	// for(i = 0; i < image.hauteurImage; ++ i)
	// {
	// for (u = 0; u < image.largeurImage; ++u)
	// {
	// value1 = map((float)i,0, image.hauteurImage, -120, 120);
	// value2 = map((float)u,0, image.largeurImage, -120, 120);
	// for (z = 0; z < network_size; ++z)
	// {
	// neural_set_value_to_not_calculate(&network[z]);
	// }
	// neural_update_output(&network[network_size - 1]);
	// if(network[network_size - 1].out_value > 0)
	// {
	// blanc = 0;
	// w = 255;
	// }
	// else
	// {
	// noir = 0;
	// w = 0;
	// }
	// for (z = 0; z < 3; ++z)
	// {
	// image.donneesRGB[y]=w;
	// ++y;
	// }
	// }
	// }
	// free(network);
	// } while(blanc || noir);
	// sprintf(str, "out%d.bmp", ii);
	// printf("%s\n", str);
	// ecrisBMPRGB_Dans(&image, str);
	// }
	// free(image.donneesRGB);
	return 0;
}
