/*
 * toolbox.c
 *
 *  Created on: Mar 11, 2017
 *      Author: colin
 */
#include <stdlib.h>
#include <math.h>

struct function_attribute
{
	char name[20];
	float (*function_addr)(float);
};

float sigmoid(float x)
{
	float rv = x / (1.0 + fabsf(x));
	return rv;
}

float d_sigmoid(float x)
{
	return 1 / (x * x + 2 * fabsf(x) + 1);
}

float d_tanh(float x)
{
	float tanh_x = tanhf(x);
	return - tanh_x * tanh_x + 1;
}

float tang(float x)
{
	return (2 * x)/(x * x -1);
}

float d_tang(float x)
{
	return ((-2) * x * x - 2)/(x * x * x * x - 2 * x * x + 1);
}

char* get_function_name(void *function_pt)
{
	int i;
	char *rv = NULL;
	static struct function_attribute functions[]=
	{
			{"sigmoid", sigmoid},
			{"tang", tang},
			{"tan", tan},

	};
	for (i = 0; i < sizeof(functions)/sizeof(functions); ++i)
	{
		if(function_pt == functions[i].function_addr)
		{
			rv = functions[i].name;
		}
	}
	return rv;
}
