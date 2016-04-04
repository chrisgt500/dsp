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
	int sections1 = 5;
	int sections2 = 4;
	float gain = 1;
	float fs;
	int center_freq = 1700;

	initialize(FS_50K, MONO_IN, MONO_OUT);

	float lpf1[25] = {
		1.000000, -1.802793, 1.000000, -1.816862, 0.995651,
		1.000000, -1.787718, 1.000000, -1.815504, 0.981259,
		1.000000, -1.726035, 1.000000, -1.818170, 0.946206,
		1.000000, -1.383865, 1.000000, -1.824551, 0.880614,
		1.000000, 1.000000, 0.000000, -0.914493, 0.000000
	};

	float lpf2[30] = {
		1.000000, 1.272696, 1.000000, 1.048769, 0.972109,
		1.000000, 1.408362, 1.000000, 0.834758, 0.873649,
		1.000000, 1.736140, 1.000000, 0.122820, 0.586595,
		1.000000, 1.000000, 0.000000, -0.436084, 0.000000
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
		demod(input, real, imaginary, filter1, filter2, output);
		putblock(output);
	}
}
