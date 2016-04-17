/*
 * @brief ECE 486 Lab 3 ece486_biquad.c
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @date Feb 9 2016
 *
 * The file has the code needed to perform an IIR filter, built on cascaded biquad coefficients
 * Init_biquad initializes any data needed from call to call. Calc_Biquad perfms the Transposed direct
 * Form 2 filter. Free_Biquad frees any memory allocated. Update is a helper function of Calc_Biquad
 * used to filter one data point at a time
 */

#include <stdio.h>
#include <stdlib.h>
#include "ece486_biquad.h"
#include <string.h>


BIQUAD_T * init_biquad(int sections, float g, float *biquad_coefs, int blocksize) {

	int i; 	//!< Performs struct initialization based on passed parameters, and dynamically
					//!< allocates required memory
	BIQUAD_T *s = (BIQUAD_T *)malloc(sizeof(BIQUAD_T));
	if(s == NULL) {
		printf("Could not allocate BIQUAD_T struct");
		return -1;
	}
	s->sections = sections;
	s->blocksize = blocksize;
	s->u = (float *)malloc(sizeof(float)*sections);
	if(s->u == NULL) {
		printf("Could not allocate float array");
		return -1;
	}
	s->v = (float *)malloc(sizeof(float)*sections);
	if(s->v == NULL) {
		printf("Could not allocate float array");
		return -1;
	}
	s->all_coefs = biquad_coefs;
	for(i = 0; i < 3; i++) {	//adds gain to first filter
		s->all_coefs[i] *= g;
	}

	for (i = 0; i < sections; i++){ //!< Verifies initial conditions are 0
		s->u[i] = 0;
		s->v[i] = 0;
	}
return s;
}

void calc_biquad(BIQUAD_T *s, float *x, float *y) {
	int i,j;
	float tmp;

	for (i = 0; i < s->blocksize; i++){ //!< Loops over every element in a block
		tmp = x[i];
		for (j = 0; j < s->sections; j++){ //!< Filters every element in the block, sections number of times
			tmp = update(s->u,s->v,s->all_coefs,tmp,j); //!< tmp is the ouput of 1 filter, and the input to the next
		}
		y[i] = tmp; //!< This could be returned in the input array to save space, but the
								//!< lab manual requires individual input and output vectors
	}
}

void destroy_biquad(BIQUAD_T *s) {
	s->u = NULL;
	s->v = NULL;
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
