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
	int sections1 = 7;
	int sections2 = 6;
	float gain1 = 0.000790;
	float gain2 = 0.061373;
	float fs;
	int center_freq = 1700;

	initialize(FS_50K, MONO_IN, MONO_OUT);

	//new coefficients for filter one after talking with hummels
	float lpf1[35] = {
		1.000000, -1.816640, 1.000000, -1.819345, 0.999023,
		1.000000, -1.814388, 1.000000, -1.818497, 0.995954,
		1.000000, -1.807075, 1.000000, -1.817614, 0.988390,
		1.000000, -1.784669, 1.000000, -1.815796, 0.968977,
		1.000000, -1.707077, 1.000000, -1.811806, 0.924865,
		1.000000, -1.305013, 1.000000, -1.805433, 0.854065,
		1.000000, 1.000000, 0.000000, -0.900799, 0.000000
	};

	//new coefs for filter two, unsure if the right passband is used
	//filter is for an fs of 10k with a passband of 3.4k and a stop band of
	//3.45k
	float lpf2[30] = {
		1.000000, 1.127121, 1.000000, 1.067634, 0.993139,
		1.000000, 1.156270, 1.000000, 1.028751, 0.972359,
		1.000000, 1.240268, 1.000000, 0.917511, 0.922710,
		1.000000, 1.436222, 1.000000, 0.617678, 0.792323,
		1.000000, 1.775232, 1.000000, -0.104616, 0.479355,
		1.000000, 1.000000, 0.000000, -0.410847, 0.000000
	};

	fs = getsamplingfrequency();
	blocksize = getblocksize();

	input = (float *)malloc(sizeof(float)*blocksize);
	output = (float *)malloc(sizeof(float)*blocksize);

	if (input==NULL || output==NULL) {  //error checking
    	flagerror(MEMORY_ALLOCATION_ERROR);
		while(1);
	}

	filter1 = init_biquad(sections1, gain1, lpf1, blocksize);
	filter2 = init_biquad(sections2, gain2, lpf2, blocksize);

	real = init_mixer(blocksize, fs, center_freq, 0.0, decimation);
	imaginary = init_mixer(blocksize, fs, center_freq, PI/2, decimation);

	while(1){
		getblock(input);
		demod(input, real, imaginary, filter1, filter2, output);
		putblock(output);
	}
}
