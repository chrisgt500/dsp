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
	struct FIR_T *fir_data = malloc(sizeof(struct FIR_T));
	fir_data->M = n_coef;
	fir_data->blocksize = blocksize;
	fir_data->h = calloc(n_coef, sizeof(float));

	for(i=0; i < n_coef; i++) {
		fir_data->h[i] = fir_coefs[i];  //talk to Colin about this
	}
	return fir_data;
}

void calc_fir (struct FIR_T *s, float *x, float *y) {
  int n, k;
  float sum;
  for (n = 0; n < s->blocksize; n++){
    sum = 0;
    for (k = 0; k < s->M; k++){
      sum += s->h[k] * x[n-k];
    }
    y[n] = sum;
  }
}

void destroy_fir (struct FIR_T *s) {

	free(s->h);
	free(s);

}
