#include "ece486_nco.h"
#include "ece486_biquad.h"
#include "ece486_mixer.h"
#include "ece486.h"
#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){

	float *input, *output1, *output2, *output3, *sq_data;
	BIQUAD_T *filter1, *filter2;
	FSK_T *real, *imaginary;
	int blocksize;
	int decimation = 5;
	int sections1 = 7;
	int sections2 = 6;
	float gain1 = 0.000488;
	float gain2 = 0.014720;
	float fs;
	int center_freq = 1700;

	initialize(FS_50K, MONO_IN, STEREO_OUT);

	//new coefficients for filter one after talking with hummels
	float lpf1[35] = {
		1.000000, -1.814993, 1.000000, -1.819085, 0.998727,
		1.000000, -1.812095, 1.000000, -1.818121, 0.994915,
		1.000000, -1.803049, 1.000000, -1.817536, 0.986204,
		1.000000, -1.776503, 1.000000, -1.816784, 0.965472,
		1.000000, -1.687836, 1.000000, -1.815417, 0.922019,
		1.000000, -1.243234, 1.000000, -1.813444, 0.857727,
		1.000000, 1.000000, 0.000000, -0.906163, 0.000000
	};

	//new coefs for filter two, unsure if the right passband is used
	//filter is for an fs of 10k with a passband of 2.6k and a stop band of
	//2.65k
	float lpf2[30] = {
		1.000000, 0.188985, 1.000000, 0.123364, 0.994580,
		1.000000, 0.226666, 1.000000, 0.087047, 0.977808,
		1.000000, 0.343342, 1.000000, -0.023010, 0.937207,
		1.000000, 0.657954, 1.000000, -0.307774, 0.835238,
		1.000000, 1.367721, 1.000000, -0.893370, 0.626398,
		1.000000, 1.000000, 0.000000, -0.678880, 0.000000
	};

	fs = getsamplingfrequency();
	blocksize = getblocksize();

	input = (float *)malloc(sizeof(float)*blocksize);
	output1 = (float *)malloc(sizeof(float)*blocksize);
	output2 = (float *)malloc(sizeof(float)*blocksize);
	output3 = (float *)malloc(sizeof(float)*blocksize);
	sq_data = (float *)malloc(sizeof(float)*blocksize/decimation);

	if (input==NULL || output1==NULL || output2==NULL) {  //error checking
    	flagerror(MEMORY_ALLOCATION_ERROR);
		while(1);
	}

	filter1 = init_biquad(sections1, gain1, lpf1, blocksize);
	filter2 = init_biquad(sections2, gain2, lpf2, blocksize/decimation);

	real = init_mixer(blocksize, fs, center_freq, 0.0, decimation);
	imaginary = init_mixer(blocksize, fs, center_freq, PI/2, decimation);

	while(1){
		getblock(input);
		//demod(input, real, imaginary, filter1, filter2, output);
		calc_biquad(filter1,input,output1);

		decimate(real, output1);
		decimate(imaginary, output1);

		sinusoidal_mult(real);
		sinusoidal_mult(imaginary);

		calc_biquad(filter2, real->data, real->data);
		calc_biquad(filter2, imaginary->data, imaginary->data);

		differentiator(real, imaginary, output1);
		differentiator(imaginary, real, output2);

		data_squared(real,imaginary,sq_data);

		output_stage(output1,output2,sq_data,blocksize/decimation,gain_calc(real->Fs/real->decimation),output3);

		antidecimate(output3,blocksize,decimation,output1);

		putblock(output1);
	}
}
