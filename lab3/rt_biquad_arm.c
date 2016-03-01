/*!
 * @file
 * @brief ECE 486 Lab 2 Real Time IIR implementation
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @Note Help from Don Hummels
 *
 * @date Feb 24 2016
 *
 *
 *
 */

#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include "arm_math.h"

#include "ece486.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void){

	int blocksize; //initializations
	arm_biquad_cascade_df2T_instance_f32 *S = (arm_biquad_cascade_df2T_instance_f32 *)malloc(sizeof(arm_biquad_cascade_df2T_instance_f32));
	float *pState;
	float *input, *output;

	int sections = 5;
	float coefs[25] = {
		0.233139, 0.421901, 0.233139, 0.434761, -0.442225,
		0.210609, -0.400601, 0.210609, 0.212751, -0.462400,
		0.295919, -0.535511, 0.295919, 1.003995, -0.828100,
		0.242158, 0.284674, 0.242158, 0.000000, -0.883600,
		2.569303, -4.157220, 2.569303, 1.220232, -0.944784
	};

	initialize(FS_50K, MONO_IN, MONO_OUT);
	blocksize = getblocksize();

	input = (float *)malloc(sizeof(float)*blocksize);
	output = (float *)malloc(sizeof(float)*blocksize);
	pState = (float *)malloc(sizeof(float)*2*sections);

	if (input==NULL || output==NULL || S==NULL || pState==NULL) {  //error checking
	  flagerror(MEMORY_ALLOCATION_ERROR);
	  while(1);
	}

	arm_biquad_cascade_df2T_init_f32(S,sections,coefs,pState);

	while(1){  //waits for ADC to fill, filters data, outputs to DAC
	  getblock(input);
	  DIGITAL_IO_SET();
	  arm_biquad_cascade_df2T_f32(S,input,output,blocksize);
	  DIGITAL_IO_RESET();
	  putblock(output);
	}
	return 0;
 }
