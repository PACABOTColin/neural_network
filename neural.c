#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "toolbox.h"
#include "neural.h"


#include <unistd.h>

const float Biais = 1.0;

/**
 * @brief
 * @detail
 * @param
 * @return
 */
/* add this bloc to the function for use */
void initialise_neural(struct neural *new_neural, float biais_coef, float (*function)(float), float (*d_function)(float), unsigned int id)
{
	static unsigned int auto_id = 0;

	printf("init %d\n", id);

 	new_neural->rv_function = function;
 	new_neural->d_rv_function = d_function;

//void initialise_neural(neural *new_neural, float biais_coef)
//{

 	new_neural->in_table_size = 0;
 	new_neural->in_value_table=NULL;
 	new_neural->coef_table = NULL;
 	new_neural->in_neural_table = NULL;
 	new_neural->out_value = 0;
 	new_neural->out_error = 0;
 	new_neural->out_table_size = 0;
 	new_neural->out_neural_table = NULL;
 	new_neural->friendly_id = id;
 	new_neural->network_id = auto_id;
 	new_neural->out_value_calculated = false;
 	new_neural->error_calculated = false;
 	new_neural->weight_calculated = false;
 	++auto_id;
 	neural_new_sensor_connection(new_neural, &Biais, biais_coef);
	neural_set_value_to_not_calculate(new_neural);
	neural_set_error_to_not_calculate(new_neural);
}

int neural_new_synapse(neural* father, neural* child, float coef)
{
	father->out_table_size ++;
	child->in_table_size ++;
	
	father->out_neural_table = realloc(father->out_neural_table, sizeof(neural*) * father->out_table_size);
	
	child->in_neural_table = realloc(child->in_neural_table, sizeof(neural*) * child->in_table_size);
	child->in_value_table = realloc(child->in_value_table, sizeof(float *) * child->in_table_size);
	child->coef_table = realloc(child->coef_table, sizeof(float) * child->in_table_size);

	if(father->out_neural_table == NULL || child->in_neural_table == NULL || child->in_value_table == NULL || child->coef_table == NULL)
	{
		printf("error, no more memory is available\n");
		exit(-1);
	}
	
	father->out_neural_table[father->out_table_size - 1] = child;

	child->in_neural_table[child->in_table_size - 1] = father;
	child->in_value_table[child->in_table_size - 1] = &(father->out_value);
	child->coef_table[child->in_table_size - 1] = coef;
	return 0;
}

int neural_new_sensor_connection(neural* sensor_neural, float *value, float coef)
{
	sensor_neural->in_table_size ++;
	sensor_neural->in_value_table = realloc(sensor_neural->in_value_table, sizeof(float*) * sensor_neural->in_table_size);
	sensor_neural->coef_table = realloc(sensor_neural->coef_table, sizeof(float) * sensor_neural->in_table_size);
	sensor_neural->in_neural_table = realloc(sensor_neural->in_neural_table, sizeof(neural*) * sensor_neural->in_table_size);

	if(sensor_neural->in_neural_table == NULL || sensor_neural->in_value_table == NULL || sensor_neural->coef_table == NULL)
	{
		printf("error, no more memory is available\n");
		exit(-1);
	}

	sensor_neural->in_neural_table[sensor_neural->in_table_size - 1] = NULL;
	sensor_neural->in_value_table[sensor_neural->in_table_size - 1] = value;
	sensor_neural->coef_table[sensor_neural->in_table_size - 1] = coef;
	return 0;
}

void neural_calculate_gradian(neural *current_neural)
{
	float rv = 0;
	float sum = 0;
	int i;
	if(current_neural->error_calculated == false)
	{
		current_neural->error_calculated = true;
		if (current_neural->out_table_size != 0)
		{
			for (i = 0; i < current_neural->out_table_size; ++i)
			{
				if(current_neural->out_neural_table[i] != NULL)
				{
					neural_calculate_gradian(current_neural->out_neural_table[i]);
					rv += current_neural->out_neural_table[i]->out_value * current_neural->out_neural_table[i]->out_error; // todo : change value of current_neural->out_neural_table[i]->out_error
				}
				else
				{
					fprintf(stderr, "warning: the neural is currently use with motor and neural output, this can affect the neural network learning process\n");
					rv = current_neural->out_error;
					break;
				}
			}
			for (i = 0; i < current_neural->in_table_size; ++i)
			{
				sum += current_neural->coef_table[i] * (*(current_neural->in_value_table[i]));
			}
			current_neural->out_error = sum;
			rv *= current_neural->d_rv_function(sum); // uncomment this line if you whant use different neural transfer function
//			rv *= d_sigmoid(sum);
			current_neural->gradian = rv;
		}
		else
		{
			for (i = 0; i < current_neural->in_table_size; ++i)
			{
				sum += *current_neural->in_value_table[i] * current_neural->coef_table[i];
			}
			current_neural->gradian = current_neural->out_error * d_sigmoid(rv);
		}
	}
}

void neural_update_weigh(neural *current_neural)
{
	printf("neural : %d\n", current_neural->friendly_id);
	usleep(100000);
	if (current_neural->weight_calculated == false)
	{
		current_neural->weight_calculated = true;
		for (int i = 0; i < current_neural->in_table_size; ++i)
		{
			neural_calculate_gradian(current_neural);
			current_neural->coef_table[i] += NU * current_neural->gradian * *(current_neural->in_value_table[i]);
		}
		for (int i = 0; i < current_neural->out_table_size; ++i)
		{
			if(current_neural->out_neural_table != NULL && current_neural->out_neural_table[i] != NULL)
			{
				neural_update_weigh(current_neural->out_neural_table[i]);
			}
		}
	}
}

void neural_update_output(neural *current_neural)
{
	printf("neural : %d\n", current_neural->friendly_id);
	usleep(100000);
	int i;
	if(current_neural->out_value_calculated == false) // if the value is not already calculated
	{
		current_neural->out_value_calculated = true;  // set the value to calculated
		current_neural->out_value = 0; 					//reset the out value
		for (i = 0; i < current_neural->in_table_size; ++i) // for all the input into the neural
		{
			if(current_neural->in_neural_table[i] != NULL) // if the input is a neural
			{
				neural_update_output(current_neural->in_neural_table[i]); // update the output of the input neural
			}
			current_neural->out_value += *(current_neural->in_value_table[i]) * current_neural->coef_table[i]; // add the input value to the output value
			current_neural->out_value = 0;
			if(isnan(current_neural->out_value)) // verify if there is not an error (should not be true)
			{
				printf("error in id : %d\n", current_neural->friendly_id);
			}
		}
		printf("neural : %d l84\n", current_neural->friendly_id); // debug print
		current_neural->out_value = current_neural->rv_function(current_neural->out_value); // put the out value into the transfert function
		if(isnan(current_neural->out_value)) // verify if there is not an error (should not be true)
		{
			printf("error in id %d\n", current_neural->friendly_id);
		}
		printf("the neural : %d done updated\n", current_neural->friendly_id); // debug print
	}
}

void neural_set_value_to_not_calculate(neural *current_neural)
{
	current_neural->out_value_calculated = false;
}

void neural_set_error_to_not_calculate(neural *current_neural)
{
	current_neural->error_calculated = false;
}
void neural_set_weight_to_not_calculate(neural *current_neural)
{
	current_neural->weight_calculated = false;
}
