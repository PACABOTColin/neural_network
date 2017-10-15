/*
 * file.c
 *
 *  Created on: Mar 10, 2017
 *      Author: colin
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "file.h"

#include "neural.h"
#include "toolbox.h"

int read_neural_networok(char filename[], struct neural **neural_table, float in_values[])
{
//	FILE *fp;
////	float (*rv_function)(float);
////	float (*d_rv_function)(float);
//	char str[70];
//	int tmp, tmp2, rv;
//	int i = 0;
//
//	fp = fopen(filename, "r");
//
//	while(fscanf(fp,"<neural id=%d>\n") != EOF)
//	{
//		*neural_table = realloc((*neural_table), sizeof(neural) * (i + 1));
//		fscanf(fp, "function %s\n", str);
//		do
//		{
//			fscanf(fp, "%s", str);
//			rv = sscanf(str,"neral connection to %d, weight %d", &tmp, &tmp2);
//			if(rv == 1)
//			{
//
//			}
//		}while(rv != 1);
////		if (strcmp(str, "sigmoide"))
////		{float (*rv_function)(float);
//		//	float
////			rv_function = sigmoid;
////			d_rv_function = d_sigmoid;
////		}
////		else if (strcmp(str, "tanh"))
////		{
////			rv_function = tanh;
////			d_rv_function = d_dtanh;
////		}
//		initialise_neural(neural_table[i]);
//		fscanf(fp,"</neural>\n");
//
//		i++;
//	}
//
	return 0;
}

bool is_neural_be_in_list(neural searched_neural, neural *tab[], int tab_lenght)
{
	int i;
	bool rv = false;
	for (i = 0; i < tab_lenght; ++i)
	{
		if(searched_neural.id == tab[i]->id)
		{
			rv = true;
			break;
		}
	}
	return rv;
}

void make_list_of_neurones(neural *from_neural_exploration, int *network_size, neural **out_neural_tab[])
{
	int i;
	bool neural_already_register;
	printf("searching connection arroung neural id : %d\nalready find neurons : ", from_neural_exploration->id);
	(*network_size) ++;
	(*out_neural_tab) = realloc((*out_neural_tab),sizeof(neural*) * (*network_size)); // add new case in the out
	(*out_neural_tab)[*network_size - 1]= from_neural_exploration;

	for (i = 0; i < *network_size; ++i)
	{
		printf("%d,", (*out_neural_tab)[i]->id);
	}
	printf("\n");

	for (i = 0; i < from_neural_exploration->in_table_size; ++i)
	{
		if (from_neural_exploration->in_neural_table[i] != NULL )
		{
			neural_already_register= is_neural_be_in_list(*(from_neural_exploration->in_neural_table[i]), (*out_neural_tab), *network_size);
			if(!neural_already_register)
			{
				make_list_of_neurones(from_neural_exploration->in_neural_table[i], network_size, out_neural_tab);
			}
		}
	}
	for (i = 0; i < from_neural_exploration->out_table_size; ++i)
	{
		if (from_neural_exploration->out_neural_table[i] != NULL )
		{
			neural_already_register= is_neural_be_in_list(*(from_neural_exploration->out_neural_table[i]), (*out_neural_tab), *network_size);
			if(!neural_already_register)
			{
				make_list_of_neurones(from_neural_exploration->out_neural_table[i], network_size, out_neural_tab);
			}
		}
	}
}

void save_network(neural *network, char *file_name)
{
	FILE *fp;
	int i, u;
	int network_size = 0;
	neural **network_tab = NULL;

	make_list_of_neurones(network, &network_size, &network_tab);

	fp = fopen(file_name, "wt");

	if(fp == NULL)
	{
		fprintf(stderr, "error the file %s can't be open for save network\n", file_name);
		return;
	}

	fprintf(fp,"%s\n", "<?xml version=\"1.0\"?>\n\n<network>");

	for (i = 0; i < network_size; ++i)
	{
		fprintf(fp,"\t<neuron id=%d>\n",(network_tab[i])->id);
		fprintf(fp,"\t\t<biais>%lf</biais>\n", network_tab[i]->coef_table[0]);
		fprintf(fp,"\t\t<function>%s</function>\n", get_function_name(network_tab[i]->rv_function));
		fprintf(fp,"\t</neuron>\n");
	}
	fprintf(fp,"</network>\n");

	fprintf(fp,"<synapses>\n");
	for (i = 0; i < network_size; ++i)
	{
		for (u = 1; u < network_tab[i]->in_table_size; ++u)
		{
			fprintf(fp,"\t<synapse>\n");
			if(network_tab[i]->in_neural_table[u] != NULL)
			{
				fprintf(fp, "\t\t<father>%d</father>\n", network_tab[i]->in_neural_table[u]->id);
			}
			fprintf(fp, "\t\t<child>%d</child>\n", network_tab[i]->id);
			fprintf(fp,"\t\t<coef>%lf</coef>\n", network_tab[i]->coef_table[u]);
			fprintf(fp,"\t</synapse>\n");
		}
	}
	fprintf(fp,"</synapses>\n");
	fclose(fp);
	free(network_tab);
}


void restor_weight(int neural_table_lenght, neural **network, char *file_name)
{
	FILE *fp;
	fp = fopen(file_name, "rt");
	int tmp;
	for (int i = 0; i < neural_table_lenght; ++i)
	{
		fscanf(fp, "|%d,", &(tmp));
		if (network[i]->in_table_size != tmp)
		{
			fprintf(stderr, "error in file");
		}
		for (int u = 0; u < network[i]->in_table_size; ++u)
		{
			fscanf(fp, "%e,", &(network[i]->coef_table[u]));
		}
	}
}
