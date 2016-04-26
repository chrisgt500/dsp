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
#include "arm_math.h"
#include "arm_const_structs.h"


extern FlagStatus KeyPressed;

int main(int argc, char *argv[])
{
	BIQUAD_T *filter1, *filter2;
	int sections1, blocksizelpf, decimation, j,i, numtaps;
	float *input1, *input2, *input_decimated_1, *input_decimated_2, gain1;
	static float buffer[FFTSAMPLES*2*2] = {0};
	float *peak_index;
	//arm_fir_decimate_instance_f32 *s;
	peak_index = malloc(sizeof(float));
	int intermediate1, intermediate2;

	int button_flag = 1;
	*peak_index = 0;
	sections1 = 3;
	blocksizelpf = 96*2;
	decimation = 6;
	gain1 = .000436;
	numtaps = 28;


	float lpf1[15] = {
		1.000000, -1.711824, 1.000000, -1.894179, 0.960442,
		1.000000, -1.365929, 1.000000, -1.855035, 0.885547,
		1.000000, 1.000000, 0.000000, -0.921111, 0.000000
	};
	/*
	float coefs[28] = {
	 -0.001184, -0.002538, -0.004333, -0.005732, -0.005518, -0.002176, 0.005761,
	 0.019233, 0.038204, 0.061389, 0.086280, 0.109517, 0.127547, 0.137404, 0.137404,
	 0.127547, 0.109517, 0.086280, 0.061389, 0.038204, 0.019233, 0.005761, -0.002176,
	 -0.005518, -0.005732, -0.004333, -0.002538, -0.001184
  };
	*/

	setblocksize(blocksizelpf); //FUN FACT, THIS NEEDS TO BE CALLED BEFORE initialize
	initialize(FS_48K, STEREO_IN, STEREO_OUT);

	input1 = (float *)malloc(sizeof(float)*blocksizelpf); //should be blocksizelpf long
	input2 = (float *)malloc(sizeof(float)*blocksizelpf);
	input_decimated_1 = (float *)malloc(sizeof(float)*(blocksizelpf/decimation));
	input_decimated_2 = (float *)malloc(sizeof(float)*(blocksizelpf/decimation));
	//buffer = (float *)malloc(sizeof(float)*FFTSAMPLES*2);


	if (input1==NULL || input2==NULL) {
		flagerror(MEMORY_ALLOCATION_ERROR);
		while(1);
	}

	filter1 = init_biquad(sections1, gain1, lpf1, blocksizelpf);
	filter2 = init_biquad(sections1, gain1, lpf1, blocksizelpf);

	do{

		if (KeyPressed) {
      		KeyPressed = RESET;
			button_flag *= -1;
		}

		// (FFTSAMPLES*2)/(blocksizelpf/decimation) -1
		for( j = 0; j < 63; j++){

			getblockstereo(input1,input2);

			calc_biquad(filter1, input1, input1);
			calc_biquad(filter2, input2, input2);

			decimate(blocksizelpf, decimation, input1, input_decimated_1);
			decimate(blocksizelpf, decimation, input2, input_decimated_2);

			// (blocksizelpf/decimation)
			for(i = 0; i < 32; i++){
				buffer[2*i+j*(32)] = input_decimated_1[i];
				buffer[2*i+j*(32)+1] = input_decimated_2[i];
			}

		}

		fft(buffer, 0, peak_index, button_flag);


		velocity_conversion_display(peak_index);
		printf("%f \n", *peak_index);



	}while(1);

	return 0;

}
