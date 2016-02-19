/*
 * @brief ECE 486 Lab 2 ece486_iir.c
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @date Feb 9 2016
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "ece486_iir.h"
#include <string.h>


BIQUAD_T * init_biquad(int sections, float g, float *biquad_coefs, int blocksize) {

	int i; 	//!< Performs struct initialization based on passed parameters, and dynamically
					//!< allocates required memory
	BIQUAD_T *s = malloc(sizeof(BIQUAD_T));
	s->sections = sections;
	s->g = g;
	s->blocksize = blocksize;
	s->u = malloc(sizeof(float)*sections);
	s->v = malloc(sizeof(float)*sections);
	s->all_coefs = biquad_coefs;

	for ( i = 0; i < sections; i++){ //!< Verifies initial conditions are 0
		s->u[i] = 0;
		s->v[i] = 0;
	}
return s;
}

void calc_biquad(BIQUAD_T *s, float *x, float *y) {
	int i,j;
	float tmp;

	for (i = 0; i < s->blocksize; i++){ //!< Loops over every element in a block
		tmp = x[i] * s->g;
		for (j = 0; j < s->sections; j++){ //!< Filters every element in the block, sections number of times
			tmp = update(s->u,s->v,s->all_coefs,tmp,j); //!< tmp is the ouput of 1 filter, and the input to the next
		}
		y[i] = tmp; //!< This could be returned in the input array to save space, but the
								//!< lab manual requires individual input and output vectors
	}
}

void destroy_biquad(BIQUAD_T *s) {
	free(s->u);//!< Frees all allocated memory
	free(s->v);
	free(s);
}

float update(float *u,float *v, float *coefs, float x, int j){
	float tmp;
	tmp = u[j] + coefs[j*5]*x; //!< Calulates the Transposed direct form II using given equations
	u[j] = v[j] - coefs[3 + j*5]*tmp + coefs[1 + j*5]*x;
	v[j] = coefs[2 + j*5]*x - coefs[4 + j*5]*tmp;
	return tmp;
}
