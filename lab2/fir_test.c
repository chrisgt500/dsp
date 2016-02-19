/*!
 * @file
 * @brief ECE 486 Lab 2 FIR Test Code
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @date Feb 18 2016
 *
 * This is code to show that FIR functions work as expected. A known x array and
 * impulse response are put into MATLABs filter function and put below. The same array
 * and impulse response are put into calc_fir. Then both MATLAB and our code outputs
 * are printed, and the maximum error between them is printed.
 *
 */

#include "ece486_fir.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void){

	int i; //initializations
	FIR_T *data;
	float max_error;

	float matlab_ouput[10] = { 0.0381361, 0.099489, 0.176114, 0.239510, 0.280036,
   								0.319474, 0.380437, 0.455561, 0.518423, 0.560080};
								/* This output is for the same input and h as below, using the
							first blocksize number of terms of MATLAB's conv function, scaled by a gain term of .0173 */

	float h[20] ={2.2044, 1.3420, .8827, -.7646,-1.3219,-.0629,1.2442,.8185,-.7088,-1.2257,
                  -.0585, 1.1535, .759,-.6571,-1.1364,-.0544,1.0695,.7038,-.6091,-1.0537};
  				/*This is an output from MATLAB's impz function with coefficients from
  				Homework 2*/

	int n_coefs = 20;

	float input[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	float output[10] = {0};
	int blocksize = 10;

	data = init_fir(h,n_coefs,blocksize);

	calc_fir(data,input,output);  //performs filtering


	printf("Output				Matlab\n");  //printing formatting

	for (i = 0; i < blocksize; i++){
		printf("%f			%f\n",output[i],matlab_ouput[i]);  //displays matlab and calc_biquad outputs
  	}
	printf("\n\n");
	for( i = 0; i < blocksize; i++){ //calculates maximum error
		if( fabsf( output[i] - matlab_ouput[i] ) > max_error) max_error = fabsf( output[i] - matlab_ouput[i] );
	}
	printf("Maximum Error: %f\n",max_error); // displays maxim error

	destroy_fir(data); //free allocated memory

}
