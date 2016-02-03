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
 
#include <stdio.h>
#include <stdlib.h>
#include "running_mean.h"


struct s * memalloc(int bs, int n) {		//performs allocations and initializations
    struct s *data_props = malloc(sizeof(struct s));
    data_props->M = n;
    data_props->blocksize = bs;
    data_props->data_array = calloc(n, sizeof(float));

	/*struct s *data_props = {
		n, 
		bs,
		calloc(n, sizeof(float))		//allocate memory for data_array for the running sum
	};*/
	return data_props;
	
}

void shift(struct s *data_props, float start) {
	int i;  
	
	for (i = ((data_props->M)-1); i > 0; i--){		//shifts every value right once in data_array, discarding oldest value
		data_props->data_array[i] = data_props->data_array[i-1];
		}
	data_props->data_array[0] = start;		//sets the first array entry to 0 so it can be reinitialized
}



float mean(struct s *data_props) {			//calculates the mean of the data_array in data_props
	int i;
	float sum;			//holds the sum
	for (i = 0; i < data_props->M; i++) {
			sum += data_props->data_array[i];
	}
  	return sum/data_props->M;
    
}  

float * calc_running_mean(float *x, struct s *data_props) {		//calculates the running mean, given data in array x of blocksize
	int i;
	//float y[data_props->blocksize];					//hold calculated means
  	float *y = malloc(data_props->blocksize*sizeof(float));
    
  	for (i = 0; i < data_props->blocksize; i++) {	//calculates the runnning mean
		shift(data_props, x[i]);
        y[i] = mean(data_props);
        //printf("%f\n",y[i]);
    }
	return y;
}

void memclean(struct s *data_props) {
  	free(data_props->data_array);
  	free(data_props);					//cleanly deallocate memory
}