#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include "neural.h"
#include "toolbox.h"
#include "file.h"

extern float entrainement [4764][2];


int main(int argc, char **argv)
{
	int i, u, y, w;
	int start_time;
	neural **all_neral;
	float echantillon[512] = {0};
	neural layer1[1];
	neural layer2[2];
	neural layer3[4];
	neural layer4[8];
	neural layer5[16];
	neural layer6[32];
	neural layer7[64];
	neural layer8[128];
	neural layer9[256];
	neural layer10[512];

	neural *layer[10];

	int seed = time(NULL);
	if (argc > 1)
	{
		   sscanf(argv[1], "%d", &seed);
	}
	srand(seed);
	printf("seed : %d\n", seed);

	layer[0] = layer1;
	layer[1] = layer2;
	layer[2] = layer3;
	layer[3] = layer4;
	layer[4] = layer5;
	layer[5] = layer6;
	layer[6] = layer7;
	layer[7] = layer8;
	layer[8] = layer9;
	layer[9] = layer10;

	for (i = 0; i < 10; ++i)
	{
		for (u = 0; u < pow(2,i) - 1; ++u)
		{
			if (i == 0)
			{
				initialise_neural(&layer[i][u], rand() / RAND_MAX, tang, d_tang);
			}
			else
			{
				initialise_neural(&layer[i][u], rand() / RAND_MAX, sigmoid, d_sigmoid);
			}
		}
		printf("%d \t", i);
		printf("%9d", u);
		printf("\n");
	}
	for (u = 0; u < 512; ++u)
	{
		if(layer10[i].in_table_size != 1)
		{
			fprintf(stderr, "error");
		}
	}
	for (i = 0; i < 9; ++i)
	{
		for (u = 0; u < pow(2,i) - 1; ++u)
		{
			for (y = 0; y < pow(2,i + 1) - 1; ++y)
			{
					neural_new_synapse(&layer[i + 1][y], &layer[i][u], rand() / RAND_MAX);
			}
		}
	}
	for (i = 0; i < 512; ++i)
	{
		neural_new_sensor_connection(&layer10[i], &echantillon[i], rand() / RAND_MAX);
	}
	all_neral = malloc(1023 * sizeof(neural*));
	if (all_neral == NULL)
	{
		fprintf(stderr, "malloc error");
		exit(EXIT_FAILURE);
	}
	i=0;
	for (u = 0; u < 10; ++u)
	{
		for (y = 0; y < pow(2, u) - 1; ++y)
		{
			++ i;
			all_neral[i] = &layer[u][y];
		}
	}
//	restor_weight(1023,)
	start_time = time(NULL);
	w = 0;
	for (w = 0; w < 100; ++w)
	{
		for (i = 0; i < 1; ++i)//4764 - (512 + 1); ++i)
		{
			for (u = 0; u < 10; ++u)
			{
				for (y = 0; y < pow(2, u) - 1; ++y)
				{
					neural_set_error_to_not_calculate(&layer[u][y]);
					neural_set_value_to_not_calculate(&layer[u][y]);
					neural_set_weight_to_not_calculate(&layer[u][y]);
				}
			}
			for (u = 0; u < 512; ++u)
			{
				echantillon[u] = entrainement[u + i][1];
			}
			neural_update_output(layer1);
			layer1[0].out_error = entrainement[512 + i + 1][1] - layer1[0].out_value;
			for (int u = 0; u < 512; ++u)
			{
				neural_update_weigh(&layer10[u]);
			}
			if( i == 0 )
			{
				printf("learn one value time = %ld\n", time(NULL) - start_time);
				start_time = time(NULL);
			}
		}
	}
	for (i = 0; i < 4764 - (512 + 1); ++i)
	{
		for (u = 0; u < 10; ++u)
		{
			for (y = 0; y < pow(2, u) - 1; ++y)
			{
				neural_set_value_to_not_calculate(&layer[u][y]);
			}
		}
		for (u = 0; u < 512; ++u)
		{
			echantillon[u] = entrainement[u + i][1];
		}
		neural_update_output(layer1);
		layer1[0].out_error = entrainement[512 + i + 1][1] - layer1[0].out_value;
		printf("error = %lf\n", layer1[0].out_error);
	}
	 save_weight(1023, all_neral, "weight");

	free(all_neral);
	return 0;
}
