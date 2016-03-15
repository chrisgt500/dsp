/*!
 * @file
 * @brief ECE 486 Lab 3 Real Time Biquad implementation
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @date Mar 15 2016
 *
 * The program is the same as the Lab 2 biquad program, except with different
 * coefficients. The coefficients come from two MATLAB scripts (lab3_task2.m and lab3_task3.m),
 * and are the corresponding second order structure for the hand placed poles. The program uses the
 * direct form II transposed filter structure to keep track of intermediate terms.
 *
 */

#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"

#include "ece486_biquad.h"
#include "ece486.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
	float *input, *output;  //initialization
	int i,blocksize;
	BIQUAD_T *data;

	initialize(FS_50K, MONO_IN, MONO_OUT);
	/* These all came from Lab 3 Task 3 Matlab output for the desired poles and zeroes */
	float g = 0.527133;
	int sections = 5;
	float coefs[25] = {
		0.233139, 0.421901, 0.233139, -0.434761, 0.442225,
		0.210609, -0.400601, 0.210609, -0.212751, 0.462400,
		0.295919, -0.535511, 0.295919, -1.003995, 0.828100,
		0.242158, 0.284674, 0.242158, -0.000000, 0.883600,
		2.569303, -4.157220, 2.569303, -1.220232, 0.944784
	};

	blocksize = getblocksize();

	input = (float *)malloc(sizeof(float)*blocksize);
	output = (float *)malloc(sizeof(float)*blocksize);

	if (input==NULL || output==NULL) {  //error checking
    	flagerror(MEMORY_ALLOCATION_ERROR);
		while(1);
	}

	data = init_biquad(sections,g,coefs,blocksize);  //one initialization

	while(1){  //waits for ADC to fill, filters data, outputs to DAC
		getblock(input);
		DIGITAL_IO_SET();
		calc_biquad(data,input,output);
		DIGITAL_IO_RESET();
		putblock(output);
	}
	destroy_biquad(data);  //frees any allocated memory
	return 0;
}
