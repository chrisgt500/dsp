/*!
 * @file fsk_rt.c
 *
 * @brief Tests the operation of ece486_mixer
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary
 * @author Forrest Smith
 * @author Sean Turner
 *
 * @date April 7, 2016
 *
 * This code sets up the filters, NCO and FSK. It then reads from the ADC on then
 * STM board,then performs the FM demodulation and outputs the results to the
 * DAC on the STM board.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ece486.h"
#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include "ece486_nco.h"
#include "ece486_biquad.h"
#include "ece486_mixer.h"


int main(void) {

	float *input, *output1, *output2, *output3, *sq_data;
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

	//read in sampling frequency and blocksize
	fs = getsamplingfrequency();
	blocksize = getblocksize();

	//allocate memory for needed arrays
	input = (float *)malloc(sizeof(float)*blocksize);
	output1 = (float *)malloc(sizeof(float)*blocksize);
	output2 = (float *)malloc(sizeof(float)*blocksize/decimation);
	output3 = (float *)malloc(sizeof(float)*blocksize/decimation);
	sq_data = (float *)malloc(sizeof(float)*blocksize/decimation);


	//error check
	if (input==NULL || output1==NULL || output2==NULL || output3 == NULL) {
    	flagerror(MEMORY_ALLOCATION_ERROR);
		while(1);
	}

	if (sq_data == NULL) {
    	flagerror(MEMORY_ALLOCATION_ERROR);
		while(1);
	}

	//initialize filters
	filter1 = init_biquad(sections1, gain1, lpf1, blocksize);
	filter2 = init_biquad(sections2, gain2, lpf2, blocksize/decimation);
	filter3 = init_biquad(sections2, gain2, lpf2, blocksize/decimation);

	//initialize FSK_T
	real = init_mixer(blocksize, fs, center_freq, 0.0, decimation);
	imaginary = init_mixer(blocksize, fs, center_freq, PI/2, decimation);

	while(1){
		//get input
		getblock(input);

		DIGITAL_IO_SET();

		//filter inputs
		calc_biquad(filter1, input, output1);

		//decimate and separate
		decimate(real, output1);
		decimate(imaginary, output1);

		//multiply with sin/cos
		sinusoidal_mult(real);
		sinusoidal_mult(imaginary);

		//filter real and imaginary components
		calc_biquad(filter2, real->data, real->data);
		calc_biquad(filter3, imaginary->data, imaginary->data);

		//differentiate the signals
		differentiator(real, imaginary, output2, sq_data);

		//calculare the output of the FM demodulator
		output_stage(output2,sq_data,blocksize/decimation,gain_calc(real->Fs/real->decimation),output3);

		//extend the signal to match the input signal size
		antidecimate(output3, real->blocksize, real->decimation, output1);

		DIGITAL_IO_RESET();

		//output to the DAC
		putblock(output1);
	}

	//cleanup
	destroy_mixer(real);
	destroy_mixer(imaginary);
	real = NULL;
	imaginary = NULL;

	free(input);
	free(output1);
	free(output2);
	free(output3);
	free(sq_data);

	input = NULL;
	output1 = NULL;
	output2 = NULL;
	output3 = NULL;
	sq_data = NULL;

	destroy_biquad(filter1);
	destroy_biquad(filter2);
	destroy_biquad(filter3);
}
