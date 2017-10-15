/*
 * toolbox.h
 *
 *  Created on: Mar 11, 2017
 *      Author: colin
 */

#ifndef TOOLBOX_H_
#define TOOLBOX_H_

#define map(in , in_min, in_max, out_min, out_max) (((in) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)) + (out_min))

float sigmoid(float x);
float d_sigmoid(float x);
//float tang(float x);
//float d_tang(float x);
//float d_tanh(float x);
char* get_function_name(void *function_pt);

#endif /* TOOLBOX_H_ */
