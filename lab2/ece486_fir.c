/*!
 * @file
 *
 * @brief Performs a discrete time convolution on two functions
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @date Feb 9 2016
 *
 * This file has the implementation for the initialization and destruction of a
 * struct which holds the data for an FIR filter. It also has the function which
 * calculates the output for a given input.
 *
 * The init_fir function sets the variable values in the struct with the
 * provided values, the calc_fir function performs a convolution of the given
 * x values with the h vlaues in the FIR_T struct: the output is stored in y.
 * The destroy_fir function frees the memory allocated by init_fir.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "ece486_fir.h"

FIR_T * init_fir(float *fir_coefs, int n_coef, int blocksize) {
	FIR_T *fir_data = malloc(sizeof(FIR_T));	/* Allocate memory needed */
	fir_data->M = n_coef;
	fir_data->blocksize = blocksize;
	fir_data->h = fir_coefs;	/* Since h will only be read from, no copy
									needed */
	fir_data->stored_data = malloc(sizeof(float) * n_coef);	/* A circular buffer to hold the
				last M values of input data */
	fir_data->index = 0;			/* Points to oldest data value
					in stored_data */
	int i;
	for (i = 0; i < n_coef; i++) {	/* Set stored data to 0.0 for starting out*/
		fir_data->stored_data[0] = 0.0;
	}
	return fir_data;	/* return pointer to the struct */
}

void shift(float *array, int size, int *index, float newdata) {
	array[(*index)++] = newdata;
	if (*index >= size) *index = 0;
}

void calc_fir(FIR_T *s, float *x, float *y) {
	int n,k,tmp;

	for(n=0; n < s->blocksize; n++) {  //Loops over every element in blocksize
		s->index = s->index%s->M;  //makes sure index is not out of bounds
		tmp = s->index;
		s->stored_data[s->index] = .7*x[n];  //sets some attenuation to prevent overflow
		for(k=0; k < s->M; k++) {  //loops over all M elements in h, and in stored_data
			y[n] = 0;  //prevents garbage data
			if(tmp==-1) tmp = s->M -1;  //Sort of a negative modulo, if the index gets below 0, reset to maximum value
			y[n] += (s->h[k]*s->stored_data[tmp]); //Performs multiplication part of convolution
			tmp -= 1;  //decrements r-index
		}
		s->index += 1;  //increments index of circular buffer
	}


void destroy_fir(FIR_T *s) {  //frees any used data
	free(s->stored_data);
	free(s);

}
