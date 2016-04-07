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
	BIQUAD_T *filter1, *filter2, *filter3, *filter4;
	FSK_T *real, *imaginary;
	int blocksize;
	int decimation = 5;
	int sections1 = 7;
	int sections2 = 4;
	int sections3 = 5;
	float gain1 = 0.000485;
	float gain2 = 0.000392;
	float gain3 = 0.878701;
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
	//filter is for an fs of 10k with a passband of 500hz and a stop band of
	//700hz
	float lpf2[20] = {
		1.000000, -1.831739, 1.000000, -1.885690, 0.982398,
		1.000000, -1.774479, 1.000000, -1.866369, 0.938575,
		1.000000, -1.443015, 1.000000, -1.851256, 0.881705,
		1.000000, 1.000000, 0.000000, -0.922037, 0.000000
	};

	float hpf1[25] = {
		1.000000, -1.998433, 1.000000, -1.997113, 0.999049,
		1.000000, -1.998603, 1.000000, -1.993821, 0.995965,
		1.000000, -1.999017, 1.000000, -1.983867, 0.986789,
		1.000000, -1.999642, 1.000000, -1.936276, 0.943011,
		1.000000, -1.000000, 0.000000, -0.829941, 0.000000
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
	filter4 = init_biquad(sections3, gain3, hpf1, blocksize);

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
