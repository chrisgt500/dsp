/*!
 * @file
 * @brief ECE 486 Lab 2 ece486_fir.c
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @date Feb 9 2016
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "ece486_fir.h"
 
struct FIR_T * init_fir (float *fir_coefs, int n_coef, int blocksize) {

	int i;
	struct s *fir_data = malloc(sizeof(struct FIR_T));
	fir_data->M = n_coef;
	fir_data->blocksize = blocksize;
	fir_data->data_array = calloc(n_coef, sizeof(float));

	for(i=0; i < n_coef; i++) {

		fir_data->data_array[i] = fir_coefs[i];

	}	
			
}

void calc_fir (FIR_T *s, float *x, float *y) {

}

void destroy_fir (FIR_T *s) {
	
	free(fir_data->array_data);
	free(fir_data);
		
}
