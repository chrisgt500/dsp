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


BIQUAD_T * init_biquad (int sections, float g, float *biquad_coefs, int blocksize) {

	int totalcoefs, i;
	totalcoefs = 5*sections;
	BIQUAD_T *s = malloc(sizeof(BIQUAD_T));
	s->sections = sections;
	s->g = g;
	s->blocksize = blocksize;
	s->stored_data[0] = 0; // v1(n)
	s->stored_data[1] = 0; //v2(n)
	s->all_coefs = calloc(totalcoefs, sizeof(float));

	for(i = 0; i < totalcoefs; i++) {
		s->all_coefs[i] = biquad_coefs[i];
		//if(i < 5) s->current_coefs[i] = biquad_coefs[i];
	}

return s;

}

void calc_biquad (BIQUAD_T *s, float *x, float *y) {
	int i,j;
	for (j = 0; j < s->sections ; j++ ){
		for(i = 0; i < 5; i++){
			s->current_coefs[i] = s->all_coefs[i+j*5];
		}
		for (i = 0; i < s->blocksize; i++){
			y[i] = s->stored_data[0] + s->current_coefs[0]*x[i];
			s->stored_data[0] = s->stored_data[1] - s->current_coefs[3]*y[i] + s->current_coefs[1]*x[i];
			s->stored_data[1] = s->current_coefs[2]*x[i] - s->current_coefs[4]*y[i];
		}
	}

}

void  destroy_biquad (BIQUAD_T *s) {

	free(s->all_coefs);
	free(s);

}
