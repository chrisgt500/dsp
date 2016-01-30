/*!
 * @file
 * @brief ECE 486 Lab 1 running_mean
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @date Jan 27 2016
 *
 */
 

#include "running_mean.h"
#include <stdlib.h>
#include <stdio.h>

void memalloc(int bs, int n) {		//performs allocations and initializations
	struct s *data_props = {
		n, 
		bs,
    	calloc(n, sizeof(float))		//allocate memory for data_array for the running sum
    };
}

void shift(struct s *data_props, float start) {
	int i;  
	for (i = ((data_props->M)-1); i > 0; i--){		//shifts every value right once in data_array, discarding oldest value
		data_props->data_array[i] = data_props->data_array[i-1];
	}
	data_props->data_array[0] = start;		//sets the first array entry to 0 so it can be reinitialized
}



float mean(struct s *data_props) {
	int i;
  	float sum;
  	for (i = 0; i < data_props->M; i++) {
    	sum += data_props->data_array[i];  
    }
  	return sum/data_props->M;
    
}  

float * calc_running_mean(float *x, struct s *data_props) {		//calculates the running mean, given data in array x of blocksize
	int i;
	float y[data_props->blocksize];
  	for (i = 0; i < data_props->blocksize, i++) {
		y[i] = mean(data_props
    }
}
