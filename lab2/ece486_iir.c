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


BIQUAD_T * init_biquad (int sections, float g, float *biquad_coefs, int blocksize) {

	int i;
	//totalcoefs = 5*sections;
	BIQUAD_T *s = malloc(sizeof(BIQUAD_T));
	s->sections = sections;
	s->g = g;
	s->blocksize = blocksize;
	s->u = malloc(sizeof(float)*sections); // v1(n)
	s->v = malloc(sizeof(float)*sections);//v2(n)
	s->all_coefs = biquad_coefs;

	for ( i = 0; i < sections; i++){
		s->u[i] = 0;
		s->v[i] = 0;
	}

return s;

}

void calc_biquad (BIQUAD_T *s, float *x, float *y) {
	int i,j;
	float tmp;

	for ( i = 0; i < s->blocksize; i++){
		tmp = x[i] * s->g;
		for( j = 0; j < s->sections; j++){
			tmp = update(s->u,s->v,s->all_coefs,tmp,j);
		}
		y[i] = tmp;
	}



	/*int i,j;
	int flag;
	flag = 0;

	for (j = 0; j < s->sections ; j++ ){
		for(i = 0; i < 5; i++){
			s->current_coefs[i] = s->all_coefs[i+j*5];
		}

		/f(flag == 0){
			s->current_coefs[0] *= s->g;
			s->current_coefs[1] *= s->g;
			s->current_coefs[2] *= s->g;
			flag++;
		}
		for (i = 0; i < s->blocksize; i++){
			y[i] = s->stored_data[0] + s->current_coefs[0]*x[i];
			s->stored_data[0] = s->stored_data[1] - s->current_coefs[3]*y[i] + s->current_coefs[1]*x[i];
			s->stored_data[1] = s->current_coefs[2]*x[i] - s->current_coefs[4]*y[i];
		}

		for ( i = 0; i < s->blocksize; i++){
			x[i] = y[i];
		}

		s->stored_data[0] = 0; // v1(n)
		s->stored_data[1] = 0; //v2(n)
	} */
}

void  destroy_biquad (BIQUAD_T *s) {

	free(s->all_coefs);
	free(s->u);
	free(s->v);
	free(s);

}

float update(float *u,float *v, float *coefs, float x, int j){
	float tmp;
	tmp = u[j] + coefs[j*5]*x;
	u[j] = v[j] - coefs[3 + j*5]*tmp + coefs[1 + j*5]*x;
	v[j] = coefs[2 + j*5]*x - coefs[4 + j*5]*tmp;
	return tmp;
}
