/*
 * toolbox.c
 *
 *  Created on: Mar 11, 2017
 *      Author: colin
 */

#include <math.h>
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
