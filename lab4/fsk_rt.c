#include "ece486_nco.h"
#include "ece486_biquad.h"
#include "ece486_mixer.h"
#include "ece486.h"
#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){

	float *input, *output1, *output2;
	BIQUAD_T *filter1, *filter2;
	FSK_T *real, *imaginary;
	int blocksize;
	int decimation = 5;
	int sections1 = 7;
	int sections2 = 6;
	float gain1 = 0.000488;
	float gain2 = 0.061373;
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
	//filter is for an fs of 10k with a passband of 3.4k and a stop band of
	//3.4
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
	output1 = (float *)malloc(sizeof(float)*blocksize);
	output2 = (float *)malloc(sizeof(float)*blocksize);

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
		DIGITAL_IO_SET();
		//demod(input, real, imaginary, filter1, filter2, output);
		calc_biquad(filter1,input,output1);
		DIGITAL_IO_RESET();

		decimate(real, output1);
		decimate(imaginary, output1);

		sinusoidal_mult(real);
		sinusoidal_mult(imaginary);

		calc_biquad(filter2, real->data, real->data);
		calc_biquad(filter2, imaginary->data, imaginary->data);

		antidecimate(real->data,blocksize,decimation,output1);
		antidecimate(imaginary->data,blocksize,decimation,output2);


		putblockstereo(output1,output2);
	}
}
