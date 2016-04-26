/*!
 * @file fsk_rt.c
 *
 * @brief
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary
 * @author Forrest Smith
 * @author Sean Turner
 *
 * @date April 23, 2016
 *
 */

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "ece486.h"
#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include "ece486_fft.h"
#include "ece486_biquad.h"


extern FlagStatus KeyPressed;

int main(int argc, char *argv[])
{
	BIQUAD_T *filter1, *filter2;
	int sections1, blocksizelpf, decimation, j;
	volatile int i;
	float *input1, *input2, *input_decimated_1, *input_decimated_2, gain1;
	static float buffer[2048] = {0};
	float *peak_index;
	peak_index = malloc(sizeof(float));
	*peak_index = 0;
	sections1 = 3;
	blocksizelpf = 96;
	decimation = 6;
	gain1 = .000436;

	float lpf1[15] = {
		1.000000, -1.711824, 1.000000, -1.894179, 0.960442,
		1.000000, -1.365929, 1.000000, -1.855035, 0.885547,
		1.000000, 1.000000, 0.000000, -0.921111, 0.000000
	};

	setblocksize(blocksizelpf); //FUN FACT, THIS NEEDS TO BE CALLED BEFORE initialize
	initialize(FS_48K, STEREO_IN, MONO_OUT);

	input1 = (float *)malloc(sizeof(float)*blocksizelpf); //should be blocksizelpf long
	input2 = (float *)malloc(sizeof(float)*blocksizelpf);
	input_decimated_1 = (float *)malloc(sizeof(float)*(blocksizelpf/decimation));
	input_decimated_2 = (float *)malloc(sizeof(float)*(blocksizelpf/decimation));


	if (input1==NULL || input2==NULL) {
		flagerror(MEMORY_ALLOCATION_ERROR);
		while(1);
	}

	filter1 = init_biquad(sections1, gain1, lpf1, blocksizelpf);
	filter2 = init_biquad(sections1, gain1, lpf1, blocksizelpf);

	while(1){



		for( j = 0; j < (FFTSAMPLES/blocksizelpf/decimation); j++){

			getblockstereo(input1,input2);

			calc_biquad(filter1, input1, input1);
			calc_biquad(filter2, input2, input2);

			decimate(blocksizelpf, decimation, input1, input_decimated_1);
			decimate(blocksizelpf, decimation, input2, input_decimated_2);

			for(i = 0; i < blocksizelpf/decimation; i+=2){
				buffer[i+j*(blocksizelpf/decimation)] = input_decimated_1[i];
			}

			for(i = 1; i < blocksizelpf/decimation; i+=2){
				buffer[i+j*(blocksizelpf/decimation)] = input_decimated_2[i];
			}
		}

		fft(buffer, 0, peak_index);
		
		velocity_conversion_display(peak_index);

	}

	return 0;

}
