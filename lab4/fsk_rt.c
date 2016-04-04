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
	int blocksize, i;
	int decimation = 5;
	float fs;

	initialize(FS_50K, MONO_IN, STEREO_OUT);

	fs = getsamplingfrequency();
	blocksize = getblocksize();

	int gain = 1;

	int sections1 = 7;

	float lpf1[35] = {
	1.000000, -1.817556, 1.000000, -1.819743, 0.999390,
	1.000000, -1.815710, 1.000000, -1.819609, 0.997400,
	1.000000, -1.809520, 1.000000, -1.820264, 0.992202,
	1.000000, -1.789869, 1.000000, -1.822402, 0.978073,
	1.000000, -1.719773, 1.000000, -1.827677, 0.943908,
	1.000000, -1.347252, 1.000000, -1.836727, 0.885450,
	1.000000, 1.000000, 0.000000, -0.921214, 0.000000
	};

	int sections2 = 6;

	float lpf2[30] = {
	1.000000, 1.102977, 1.000000, 1.054108, 0.990851,
	1.000000, 1.143693, 1.000000, 1.004208, 0.971942,
	1.000000, 1.257170, 1.000000, 0.853557, 0.915905,
	1.000000, 1.527773, 1.000000, 0.400933, 0.747899,
	1.000000, 1.918684, 1.000000, -0.652235, 0.357073,
	1.000000, 1.090314, 1.000000, 1.069894, 0.997867
	};

	filter1 = init_biquad(sections1, gain, lpf1, blocksize);
	filter2 = init_biquad(sections2, gain, lpf2, blocksize);

	while(1){

		bs_nco = real->blocksize / real->decimation ;

		// First LP filter
		calc_biquad(filter1, input, output1);

		//"Decimating" the data
		decimate(real, output1);
		decimate(imaginary, output1);

		//Separating real and imaginary signals
		sinusoidal_mult(real);
		sinusoidal_mult(imaginary);

		//Filter each signal separately
		calc_biquad(filter2, real->data, real->data);
		calc_biquad(filter2, imaginary->data, imaginary->data);

		//Differentation of the signals
		output1 = differentiator(real, imaginary);
		output2 = differentiator(imaginary, real);

		//antidecimation();
		//putblockstereo

	}


}
