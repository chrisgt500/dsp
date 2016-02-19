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
	fir_data->stored_data = malloc(sizeof(float) * n_coef);
	fir_data->oldest = fir_data->stored_data;
	return fir_data;	/* return pointer to the struct */
}

void calc_fir(FIR_T *s, float *x, float *y) {
	int n, k, kmin, kmax;
	/* n starts at zero and goes (length of s->h + length of x -1) times */
	for (n = 0; n < s->blocksize + s->M - 1; n++) {
		y[n] = 0;
		for (k = 0; k < M; k++){	/* for all valid values of k */
			if
			y[n] += x[k] * s->h[n-k];
		}
	}
}

void destroy_fir(FIR_T *s) {
	free(s);

}
