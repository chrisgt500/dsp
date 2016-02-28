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

	int i,blocksize; //initializations
	arm_biquad_cascade_df2T_instance_f32 *S = (arm_biquad_cascade_df2T_instance_f32 *)malloc(sizeof(arm_biquad_cascade_df2T_instance_f32));
	float *pState;
	float *input, *output;  //initialization


	initialize(FS_50K, MONO_IN, MONO_OUT);

	float coefs[10] = {2.2044, 0.0, 2.2044, -.6088, .9702, 2.9658,-3.4865,2.9658,-.350,-.4250};
	int sections = 2;

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
