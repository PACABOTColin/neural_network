#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#include "neural.h"
#include "toolbox.h"
#include "file.h"

#define TRACE_DEEP 5000

#define training_size (928682)

extern float training[training_size];

#define nombre_couche (4)
#define network_size (sum_suite_al(nombre_couche))
#define sum_suite_al(n) ((n)*((n)+1)/2)

int main(int argc, char **argv)
{
	double error_avr = 0;
	float input[nombre_couche + 1];
	int i, y = 0, sum, z;
	srand(time(NULL));
	neural *network_temperature;
	neural *network_temp_cetitude;


	network_temperature = malloc(sizeof(*network_temp_cetitude) * (network_size));	// alloc mem for all the neural network
	network_temp_cetitude = malloc(sizeof(*network_temp_cetitude) * (network_size));	// alloc mem for all the neural network
	for (i = 0; i < network_size; ++i)	// init neurons
	{
		initialise_neural(&network_temp_cetitude[i], (float)rand() * 2.0 / RAND_MAX - 1, sigmoid, d_sigmoid, 1000+i);
		initialise_neural(&network_temperature[i], (float)rand() * 2.0 / RAND_MAX - 1, sigmoid, d_sigmoid, i);
	}
	/* 
	 * initialyse all the neural connection
	 * n                   0
	 * ---------------------+
	 * o o o o o o o o ... o | n
	 *  \|\|\|\|\|\|\|\...\| |
	 *   o o o o o o o ... o | n-1
	 *    \|\|\|\|\|\|\...\| |
	 *     o o o o o o ... o | n-2
	 *      \|\|\|\|\|\...\| |
	 *       o o o o o ... o |
	 *        \|\|\|\|\...\| |
	 *         o o o o ... o |
	 *          \|\|\|\...\| |
	 *                     : |
	 *                   o o | 1
	 *                    \| |
	 *                     o | 0
	 */
	sum = 0;
	for (i = 0; i < nombre_couche - 1; ++i)
	{
		sum += i;
		for (y = 0; y <= i; ++y)
		{
			/*** link temperature neurons ***/
			neural_new_synapse(&network_temperature[sum + y + i + 1], &network_temperature[sum + y],
							   (float)rand() * 2.0 / RAND_MAX - 1);
			neural_new_synapse(&network_temperature[sum + y + i + 2], &network_temperature[sum + y],
							   (float)rand() * 2.0 / RAND_MAX - 1);

			/*** link temperature certitude neurons ***/
			neural_new_synapse(&network_temp_cetitude[sum + y + i + 1], &network_temp_cetitude[sum + y],
							   (float)rand() * 2.0 / RAND_MAX - 1);
			neural_new_synapse(&network_temp_cetitude[sum + y + i + 2], &network_temp_cetitude[sum + y],
							   (float)rand() * 2.0 / RAND_MAX - 1);
		}
	}
	/*** link the tow network ***/
	for (i = 0; i < network_size; ++i)
	{
		neural_new_synapse(&network_temperature[i], &network_temp_cetitude[i],
									   (float)rand() * 2.0 / RAND_MAX - 1);
	}

	for (i = network_size - nombre_couche - 1; i < network_size; ++i)
	{
		/*** link temperature neurons ***/
		neural_new_sensor_connection(&network_temperature[i], &input[i], (float)rand() *
									 2.0 / RAND_MAX - 1);
		neural_new_sensor_connection(&network_temperature[i], &input[i + 1], (float)rand() *
									 2.0 / RAND_MAX - 1);

		/*** link temperature certitude neurons ***/
		neural_new_sensor_connection(&network_temp_cetitude[i], &input[i], (float)rand() *
									 2.0 / RAND_MAX - 1);
		neural_new_sensor_connection(&network_temp_cetitude[i], &input[i + 1], (float)rand() *
									 2.0 / RAND_MAX - 1);
	}
	sum = 0;
	for (z = 0; z < 1; ++z)
	{
//		for (i = 0; i < training_size - nombre_couche - 1; ++i)
		for (i = 0; i < 1; ++i)
		{
			memcpy(input, &training[i], sizeof(input));
			for (y = 0; y < network_size + 1; ++y)
			{
				input[y] = training[i + y];
				printf("%f, ", input[i]);
			}
			printf("\n");
			for (y = 0; y < network_size; ++y)
			{
				neural_set_error_to_not_calculate(&network_temperature[y]);
				neural_set_value_to_not_calculate(&network_temperature[y]);
				neural_set_weight_to_not_calculate(&network_temperature[y]);
			}
			neural_update_output(&network_temperature[0]);
			network_temperature[0].out_error = training[i + nombre_couche + 1]/100.00 - network_temperature[0].out_value;
			error_avr += fabs(network_temperature[0].out_error);
			if(i % TRACE_DEEP == 0)
			{
				printf("%3d out %f, error = %f\n", i, network_temperature[0].out_value * 100, (error_avr / TRACE_DEEP) * 100);
				error_avr = 0;
			}
			for (y = network_size - nombre_couche; y < network_size; ++y) {
				neural_update_weigh(&network_temperature[y]);

			}
		}
		sleep(1);
		sum++;
	}

	// for (ii = 0; ii < training_size - network_size; ++ii)
	// {
	// 
	// do
	// {
	// blanc = 1;
	// noir = 1;
	// y = 0;
	// for (i = 0; i < network_size; ++i)
	// {
	// initialise_neural(&network[i],
	// (float)rand() * 20.0 / RAND_MAX - 10,
	// sigmoid, d_sigmoid);
	// }
	// for (u = 0; u < nombre_couche; ++u)
	// {
	// for (i = 0; i < nombre_neuronne_couche; ++i)
	// {
	// if (u == 0)
	// {
	// neural_new_sensor_connection(&network[i], &value1,);
	// neural_new_sensor_connection(&network[i], &value2,
	// (float)rand() * 2.0 /
	// RAND_MAX - 1);
	// }
	// else
	// {
	// for (y = 0; y < nombre_neuronne_couche; ++y)
	// {
	// neural_new_synapse(&network
	// [(u -
	// 1) * nombre_neuronne_couche +
	// y],
	// &network[u *
	// nombre_neuronne_couche
	// + i],
	// (float)rand() * 2.0 / RAND_MAX -
	// 1);
	// }
	// }
	// }
	// }
	// for (i = 0; i < nombre_neuronne_couche; ++i)
	// {
	// neural_new_synapse(&network[(nombre_couche -1) *
	// nombre_neuronne_couche 
	// 
	// + i], &network[network_size - 1], (float)rand() * 2.0/
	// RAND_MAX - 1);
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
