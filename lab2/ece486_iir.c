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


struct BIQUAD_T * init_biquad (int sections, float g, float *biquad_coefs, int blocksize) {
	
	int totalcoefs, i;
	totalcoefs = 5*sections;
	struct BIQUAD_T *s = malloc(sizeof(struct BIQUAD_T));
	s->sections = sections;
	s->g = g;
	s->blocksize = blocksize;
	s->stored_data[0] = 0;
	s->stored_data[1] = 0;
	s->all_coefs = calloc(totalcoefs, sizeof(float));
	
	for(i = 0; i < totalcoefs; i++) {
		s->all_coefs[i] = biquad_coefs[i];
		if(i < 5) s->current_coefs[i] = biquad_coefs[i];
	}
	
	
	
}

void calc_biquad (BIQUAD_T *s, float *x, float *y) {

}

void  destroy_biquad (BIQUAD_T *s) {

	free(s->all_coefs);
	free(s);

}


