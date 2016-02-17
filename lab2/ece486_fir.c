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

FIR_T * init_fir(float *fir_coefs, int n_coef, int blocksize) {
	FIR_T *fir_data = malloc(sizeof(FIR_T));
	fir_data->M = n_coef;
	fir_data->blocksize = blocksize;
	fir_data->h = fir_coefs;

	return fir_data;
}

void calc_fir(FIR_T *s, float *x, float *y) {
	int n, k, kmin, kmax;
	float sum;
	for (n = 0; n < s->blocksize; n++){
		sum = 0;
		kmin = (n >= s->M-1) ? n-s->M-1:0;
		kmax = (n < s->blocksize) ? n : s->blocksize;
		for (k = kmin; k < kmax; k++){
			sum += x[k] * s->h[n-k];
		}
		y[n] = sum;
	}
}

void destroy_fir(FIR_T *s) {

	free(s);

}
