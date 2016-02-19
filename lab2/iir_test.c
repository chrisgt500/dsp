/*!
 * @file
 * @brief ECE 486 Lab 2 IIR Test Code
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @date Feb 18 2016
 *
 * This is code to show that IIR functions work as expected. A known x array and
 * coefficients are put into MATLABs filter function and put below. The same array
 * and coefficients are put into calc_biquad. Then both MATLAB and our code outputs
 * are printed, and the maximum error between them is printed.
 *
 */

#include "ece486_iir.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void){

	int i,blocksize; //initializations
	BIQUAD_T *data;
	float max_error;

	float matlab_ouput[10] = {6.537809, 11.658430, 23.538379, 35.816608, 52.470271,
								72.979091, 96.685734, 121.053051, 145.744734, 172.094540};
							/* This output is for the same input and coefficients as below
								using MATLAB's filter function */

	float coefs[10] = {2.2044, 0.0, 2.2044, -.6088, .9702, 2.9658,-3.4865,2.9658,-.350,-.4250};
	float g = 1;
	int sections = 2;
	blocksize = 10;
	float input[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	float output[10] = {0};

	data = init_biquad(sections,g,coefs,blocksize);

	calc_biquad(data,input,output);  //performs filtering

	printf("Output				Matlab\n");  //printing formatting

	for (i = 0; i < blocksize; i++){
		printf("%f			%f\n",output[i],matlab_ouput[i]);  //displays matlab and calc_biquad outputs
  	}
	printf("\n\n");
	for( i = 0; i < blocksize; i++){ //calculates maximum error
		if( fabsf( output[i] - matlab_ouput[i] ) > max_error) max_error = fabsf( output[i] - matlab_ouput[i] );
	}
	printf("Maximum Error: %f\n",max_error); // displays maxim error
	destroy_biquad(data); //free allocated memory

}
