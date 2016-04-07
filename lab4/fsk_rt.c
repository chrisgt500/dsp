#include <string.h>
#include "ece486_nco.h"
#include "ece486_biquad.h"
#include "ece486_mixer.h"
#include "ece486.h"
#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){

	float *input, *output1, *output2, *output3, *output4, *output5, *output6, *sq_data;
	BIQUAD_T *filter1, *filter2, *filter3;
	FSK_T *real, *imaginary;
	int blocksize;
	int decimation = 5;
	int sections1 = 3;
	int sections2 = 4;
	float gain1 = 0.000916;
	float gain2 = 0.002097;
	float fs;
	int center_freq = 1700;

	initialize(FS_50K, MONO_IN, STEREO_OUT);

	//new coefficients for filter one after talking with hummels
	float lpf1[15] = {
		1.000000, -1.303582, 1.000000, -1.764599, 0.937397,
		1.000000, -0.646373, 1.000000, -1.741520, 0.820410,
		1.000000, 1.000000, 0.000000, -0.873245, 0.000000
	};

	//new coefs for filter two, unsure if the right passband is used
	//filter is for an fs of 10k with a passband of 500hz and a stop band of
	//700hz
	float lpf2[20] = {
		1.000000, -1.012494, 1.000000, -1.342739, 0.958950,
		1.000000, -0.766210, 1.000000, -1.395813, 0.856547,
		1.000000, 0.188094, 1.000000, -1.521996, 0.719358,
		1.000000, 1.000000, 0.000000, -0.800463, 0.000000
	};

	fs = getsamplingfrequency();
	blocksize = getblocksize();

	input = (float *)malloc(sizeof(float)*blocksize);
	output1 = (float *)malloc(sizeof(float)*blocksize);
	output2 = (float *)malloc(sizeof(float)*blocksize);
	output3 = (float *)malloc(sizeof(float)*blocksize);
	output4 = (float *)malloc(sizeof(float)*blocksize/decimation);
	output5 = (float *)malloc(sizeof(float)*blocksize/decimation);
	output6 = (float *)malloc(sizeof(float)*blocksize/decimation);
	sq_data = (float *)malloc(sizeof(float)*blocksize/decimation);

	if (input==NULL || output1==NULL || output2==NULL) {  //error checking
    	flagerror(MEMORY_ALLOCATION_ERROR);
		while(1);
	}

	filter1 = init_biquad(sections1, gain1, lpf1, blocksize);
	filter2 = init_biquad(sections2, gain2, lpf2, blocksize/decimation);
	filter3 = init_biquad(sections2, gain2, lpf2, blocksize/decimation);

	real = init_mixer(blocksize, fs, center_freq, 0.0, decimation);
	imaginary = init_mixer(blocksize, fs, center_freq, PI/2, decimation);

	while(1){
		getblock(input);
		//demod(input, real, imaginary, filter1, filter2, filter3, output1);

		calc_biquad(filter1, input, output1);
		calc_biquad(filter4, output1, output2);


		decimate(real, output2);
		decimate(imaginary, output2);


		sinusoidal_mult(real);
		sinusoidal_mult(imaginary);

		calc_biquad(filter2, real->data, real->data);
		calc_biquad(filter3, imaginary->data, imaginary->data);

		differentiator(real, imaginary, output4, sq_data);

		output_stage(output4,sq_data,blocksize/decimation,gain_calc(real->Fs/real->decimation),output6);

		antidecimate(output6, real->blocksize, real->decimation, output1);


		putblock(output1);
	}
}
