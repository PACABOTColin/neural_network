#ifndef NEURAL_H
#define NEURAL_H

#include <stdbool.h>

#define LEANING_MODE
#define NU 0.1

typedef struct neural
{
	int in_table_size;
	float **in_value_table;
	float *coef_table;
	struct neural **in_neural_table;

//	float (*rv_function)(float);
//	float (*d_rv_function)(float);
	bool error_calculated;
	bool out_value_calculated;
	float out_value;
	float out_error;
	float gradian;
	int out_table_size;
	struct neural **out_neural_table;
}neural;

//void initialise_neural(float *(function)(float), struct neural *new_neural);
void initialise_neural(neural *new_neural, float biais_coef);
int neural_new_synapse(neural* father, neural* child, float coef);
int neural_new_sensor_connection(neural* sensor_neural, float *value, float coef);
void neural_calculate_gradian(neural *current_neural);
void neural_update_weigh(neural *current_neural);
void neural_update_output(neural *current_neral);
void neural_set_value_to_not_calculate(neural *current_neural);
void neural_set_error_to_not_calculate(neural *current_neural);
#endif
