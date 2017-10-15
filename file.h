/*
 * file.h
 *
 *  Created on: Mar 10, 2017
 *      Author: colin
 */

#ifndef FILE_H_
#define FILE_H_

#include "neural.h"

int read_neural_networok(char filename[], struct neural *neural_table[], float in_values[]);
void read_learn_value(char filename[], float in_values[]);
void save_network(neural *network, char *file_name);
void restor_weight(int neural_table_lenght, neural **network, char *file_name);

#endif /* FILE_H_ */
