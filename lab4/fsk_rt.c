#include "ece486_nco.h"
#include "ece486_biquad.h"
#include "ece486_mixer.h"
#include "ece486.h"
#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){

	float *input, *output;
	BIQUAD_T *filter1, *filter2;
	FSK_T *real, *imaginary;
	int blocksize;
	int decimation = 5;
	int sections1 = 6;
	int sections2 = 6;
	float gain = 1;
	float fs;
	int center_freq = 1700;

	initialize(FS_50K, MONO_IN, MONO_OUT);

	float lpf1[30] = {
	1.000000, -1.812420, 1.000000, -1.819182, 0.995557,
	1.000000, -1.801493, 1.000000, -1.820299, 0.986835,
	1.000000, -1.765173, 1.000000, -1.823778, 0.964238,
	1.000000, -1.615794, 1.000000, -1.831308, 0.916347,
	1.000000, -0.373252, 1.000000, -1.840377, 0.858834,
	1.000000, -1.815631, 1.000000, -1.819408, 0.998953
	};

	float lpf2[30] = {
	1.000000, 1.102977, 1.000000, 1.054108, 0.990851,
	1.000000, 1.143693, 1.000000, 1.004208, 0.971942,
	1.000000, 1.257170, 1.000000, 0.853557, 0.915905,
	1.000000, 1.527773, 1.000000, 0.400933, 0.747899,
	1.000000, 1.918684, 1.000000, -0.652235, 0.357073,
	1.000000, 1.090314, 1.000000, 1.069894, 0.997867
	};

	fs = getsamplingfrequency();
	blocksize = getblocksize();

	input = (float *)malloc(sizeof(float)*blocksize);
	output = (float *)malloc(sizeof(float)*blocksize);

	if (input==NULL || output==NULL) {  //error checking
    	flagerror(MEMORY_ALLOCATION_ERROR);
		while(1);
	}

	filter1 = init_biquad(sections1, gain, lpf1, blocksize);
	filter2 = init_biquad(sections2, gain, lpf2, blocksize);

	real = init_mixer(blocksize, fs, center_freq, 0.0, decimation);
	imaginary = init_mixer(blocksize, fs, center_freq, PI/2, decimation);

	while(1){
		getblock(input);
		//demod(input, real, imaginary, filter1, filter2, output);
		calc_biquad(filter2, input, output);
		putblock(output);
	}
}
