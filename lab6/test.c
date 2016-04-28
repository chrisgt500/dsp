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
#include "arm_math.h"
#include "arm_const_structs.h"


extern FlagStatus KeyPressed;

int main(int argc, char *argv[])
{
	int blocksizelpf, decimation, j,i, numtaps;
	float *input1, *input2, *input_decimated_1, *input_decimated_2;
	static float buffer[FFTSAMPLES*2] = {0};
	float *peak_index, *state;
	arm_fir_decimate_instance_f32 *s;
	peak_index = malloc(sizeof(float));
	s = (arm_fir_decimate_instance_f32*)(malloc(sizeof(arm_fir_decimate_instance_f32)));
	int button_flag = 1;
	*peak_index = 0;
	blocksizelpf = FFTSAMPLES;
	decimation = 8;
	numtaps = 28;
	state = (float *)calloc((numtaps + blocksizelpf -1),sizeof(float));
	s->M = decimation;
	s->numTaps = numtaps;
	s->pState = state;


	float coefs[28] = {
	 -0.001184, -0.002538, -0.004333, -0.005732, -0.005518, -0.002176, 0.005761,
	 0.019233, 0.038204, 0.061389, 0.086280, 0.109517, 0.127547, 0.137404, 0.137404,
	 0.127547, 0.109517, 0.086280, 0.061389, 0.038204, 0.019233, 0.005761, -0.002176,
	 -0.005518, -0.005732, -0.004333, -0.002538, -0.001184
  };


	s->pCoeffs = coefs;

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


	do{

		if (KeyPressed) {
      		KeyPressed = RESET;
			button_flag *= -1;
		}

		// (FFTSAMPLES*2)/(blocksizelpf/decimation) -1
		for( j = 0; j < 15; j++){

			getblockstereo(input1,input2);

			//unsure if we need two seperate arm_fir_decimate_instance_f32's for filtering or just one
			arm_fir_decimate_f32(s, input1, input_decimated_1, blocksizelpf);
			arm_fir_decimate_f32(s, input2, input_decimated_2, blocksizelpf);

			// (blocksizelpf/decimation)
			for(i = 0; i < (FFTSAMPLES)/8; i++){
				buffer[2*i+j*(FFTSAMPLES/8)] = input_decimated_1[i];
				buffer[2*i+j*(FFTSAMPLES/8)+1] = input_decimated_2[i];
			}

		}

		fft(buffer, 20, peak_index, button_flag);

		velocity_conversion_display(peak_index, button_flag);
		if (button_flag == 1) printf("FORWARDS %f \n", *peak_index);
		if (button_flag == -1) printf("Backwards %f \n", *peak_index);



	}while(0);

	return 0;

}
