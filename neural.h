#ifndef NEURAL_H
#define NEURAL_H

#include <stdbool.h>

/********debug define*******/

#define VERBOSE_NEW_CONNECTION
//#define VERBOSE_UPDATE_WEIGH
//#define VERBOSE_UPDATE_OUTPUT

/****end of debug define****/

#define NU 0.00001

typedef struct neural
{
	unsigned int friendly_id;
	unsigned int id;

	int in_table_size;
	float **in_value_table;
	float *coef_table;
	struct neural **in_neural_table;

	float (*rv_function)(float);
	float (*d_rv_function)(float);
	bool error_calculated;
	bool weight_calculated;
	bool out_value_calculated;
	float out_value;
	float out_error;
	float gradian;
	int out_table_size;
	struct neural **out_neural_table;
}neural;

void initialise_neural(struct neural *new_neural, float biais_coef, float (*function)(float), float (*d_function)(float), unsigned int id);
//void initialise_neural(neural *new_neural, float biais_coef);
int neural_new_synapse(neural* father, neural* child, float coef);
int neural_new_sensor_connection(neural* sensor_neural, float *value, float coef);
void neural_calculate_gradian(neural *current_neural);
void neural_update_weigh(neural *current_neural);
void neural_update_output(neural *current_neral);
void neural_set_value_to_not_calculate(neural *current_neural);
void neural_set_error_to_not_calculate(neural *current_neural);
void neural_set_weight_to_not_calculate(neural *current_neural);

#endif
