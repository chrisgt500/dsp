/*!
 * @file fsk_rt.c
 *
 * @brief This file implements the functions defined by ece486_fft.c.
 *
 * This takes a real and imaginary signal from a doppler radar, and initialize
 * the required data, in a while(1) loop it fills ADC, filters and decimates, fills
 * a buffer so it can be used with the arm fft routines. The fft is performed, and the
 * magnitudes are found. Then the farthest away peak is found, and the index is converted
 * into a velocity and displayed. The button can be pressed to change whether negative or
 * positive velocity is checked for.
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
	//initalizations
	int blocksize, decimation, j,i, numtaps, button_flag;
	float *input1, *input2, *input_decimated_1, *input_decimated_2;
	static float buffer[FFTSAMPLES*2] = {0};
	float *state, *state1;
	int peak_index;
	float coefs[55] = { //ARM filter coefficients
		0.000571, 0.000743, 0.001066, 0.001301, 0.001319, 0.000965, 0.000088, -0.001432,
		-0.003647, -0.006511, -0.009848, -0.013343, -0.016548, -0.018908, -0.019816,
		-0.018679, -0.014995, -0.008436, 0.001084, 0.013363, 0.027890, 0.043871, 0.060279,
		0.075951, 0.089696, 0.100417, 0.107233, 0.109571, 0.107233, 0.100417, 0.089696, 0.075951,
		0.060279, 0.043871, 0.027890, 0.013363, 0.001084, -0.008436, -0.014995, -0.018679, -0.019816,
		-0.018908, -0.016548, -0.013343, -0.009848, -0.006511, -0.003647, -0.001432, 0.000088,
		0.000965, 0.001319, 0.001301, 0.001066, 0.000743, 0.000571
	};

	arm_fir_decimate_instance_f32 *s, *s1; //decimation structs

	peak_index = 0;
	blocksize = FFTSAMPLES;
	decimation = 8;
	numtaps = 55;
	button_flag = 1;

	//malloc and calloc memory allocation
	state = (float *)calloc((numtaps + blocksize -1),sizeof(float));
	state1 = (float *)calloc((numtaps + blocksize -1),sizeof(float));
	s = (arm_fir_decimate_instance_f32*)(malloc(sizeof(arm_fir_decimate_instance_f32)));
	s1 = (arm_fir_decimate_instance_f32*)(malloc(sizeof(arm_fir_decimate_instance_f32)));
	input1 = (float *)malloc(sizeof(float)*blocksize);
	input2 = (float *)malloc(sizeof(float)*blocksize);
	input_decimated_1 = (float *)malloc(sizeof(float)*(blocksize/decimation));
	input_decimated_2 = (float *)malloc(sizeof(float)*(blocksize/decimation));

	//ARM filter struct initalizations
	s->M = decimation;
	s1->M = decimation;
	s->numTaps = numtaps;
	s1->numTaps = numtaps;
	s->pState = state;
	s1->pState = state1;
	s->pCoeffs = coefs;
	s1->pCoeffs = coefs;

	setblocksize(blocksize); //FUN FACT, THIS NEEDS TO BE CALLED BEFORE initialize
	initialize(FS_48K, STEREO_IN, STEREO_OUT);   //ADC and DAC init

	//Error checking
	if (input1==NULL || input2==NULL || input_decimated_1 == NULL || input_decimated_2 == NULL) {
		flagerror(MEMORY_ALLOCATION_ERROR);
		while(1);
	}

	while(1){ //repeat infinitely

		if (KeyPressed) {  //this changes button flag state on each press
      		KeyPressed = RESET;
			button_flag *= -1; //-1 or 1 differentiates between negative and positive velocity
			BSP_LED_Toggle(LED4); //visual red led indicator
		}

		for( j = 0; j < 8; j++){  //loops over decimation
			getblockstereo(input1,input2); //fill buffers with real and imaginary data

			arm_fir_decimate_f32(s1, input2, input_decimated_2, blocksize);  //magic fir filter and decimate function
			arm_fir_decimate_f32(s, input1, input_decimated_1, blocksize); //both have passband of 2kHz and stopband of 4kHz

			for(i = 0; i < (FFTSAMPLES)/8; i++){  //interlaces the buffer with re[0], im[0], re[1], im[1], ...
				buffer[2*i+j*256] = input_decimated_1[i]; //this is for an 1024 fft, with a 2048 buffer
				buffer[2*i+j*256+1] = input_decimated_2[i];
			}

		}

		peak_index = fft(buffer, 30, button_flag); //performs the fft algorithm, converts to magnitude, and detects the peak. Returns the peak index in the output array
		velocity_conversion_display(peak_index, button_flag); //performs the conversion from peak_index to velocity and displays it

	}

	//frees memory for safety
	free(state);
	free(state1);
	free(s);
	free(s1);
	free(input1);
	free(input2);
	free(input_decimated_1);
	free(input_decimated_2);

	//more safety
	state = NULL;
	state1 = NULL;
	s = NULL;
	s1 = NULL;
	input1 = NULL;
	input2 = NULL;
	input_decimated_1 = NULL;
	input_decimated_2 = NULL;

	//safety level: maximum
	return 0;
}
