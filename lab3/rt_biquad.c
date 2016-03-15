/*!
 * @file
 * @brief ECE 486 Lab 2 Real Time IIR implementation
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @date Feb 9 2016
 *
 *
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
