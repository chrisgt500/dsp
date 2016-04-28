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
	float *peak_index, *state, *state1;
	arm_fir_decimate_instance_f32 *s, *s1;
	peak_index = malloc(sizeof(float));
	s = (arm_fir_decimate_instance_f32*)(malloc(sizeof(arm_fir_decimate_instance_f32)));
	s1 = (arm_fir_decimate_instance_f32*)(malloc(sizeof(arm_fir_decimate_instance_f32)));
	int button_flag = 1;
	*peak_index = 0;
	blocksizelpf = FFTSAMPLES;
	decimation = 8;
	numtaps = 55;
	state = (float *)calloc((numtaps + blocksizelpf -1),sizeof(float));
	state1 = (float *)calloc((numtaps + blocksizelpf -1),sizeof(float));
	s->M = decimation;
	s1->M = decimation;
	s->numTaps = numtaps;
	s1->numTaps = numtaps;
	s->pState = state;
	s1->pState = state1;


	float coefs[55] = {
	0.000571, 0.000743, 0.001066, 0.001301, 0.001319, 0.000965, 0.000088, -0.001432,
	-0.003647, -0.006511, -0.009848, -0.013343, -0.016548, -0.018908, -0.019816,
	-0.018679, -0.014995, -0.008436, 0.001084, 0.013363, 0.027890, 0.043871, 0.060279,
	0.075951, 0.089696, 0.100417, 0.107233, 0.109571, 0.107233, 0.100417, 0.089696, 0.075951,
	0.060279, 0.043871, 0.027890, 0.013363, 0.001084, -0.008436, -0.014995, -0.018679, -0.019816,
	-0.018908, -0.016548, -0.013343, -0.009848, -0.006511, -0.003647, -0.001432, 0.000088,
	0.000965, 0.001319, 0.001301, 0.001066, 0.000743, 0.000571
	};


	s->pCoeffs = coefs;
	s1->pCoeffs = coefs;

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
			arm_fir_decimate_f32(s1, input2, input_decimated_2, blocksizelpf);

			// (blocksizelpf/decimation)
			for(i = 0; i < (FFTSAMPLES)/8; i++){
				buffer[2*i+j*(FFTSAMPLES/8)] = input_decimated_1[i];
				buffer[2*i+j*(FFTSAMPLES/8)+1] = input_decimated_2[i];
			}

		}

		fft(buffer, 40, peak_index, button_flag);

		velocity_conversion_display(peak_index, button_flag);
		if (button_flag == 1) printf("FORWARDS %f \n", *peak_index);
		if (button_flag == -1) printf("Backwards %f \n", *peak_index);



	}while(1);

	return 0;

}
