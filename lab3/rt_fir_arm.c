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

int main(void)
{
	float *input, *output; //initializations
  int blocksize;
	arm_fir_instance_f32 *S = (arm_fir_instance_f32 *)malloc(sizeof(arm_fir_instance_f32));
	float *pState;

	float h[5] = {.2,.2,.2,.2,.2};
	int n_coefs = 5;

	initialize(FS_50K, MONO_IN, MONO_OUT);
  blocksize = getblocksize();


  input = (float *)malloc(sizeof(float)*blocksize);
  output = (float *)malloc(sizeof(float)*blocksize);
	pState = (float *)malloc(sizeof(float)*(n_coefs+blocksize-1));

    if (input==NULL || output==NULL) {  //error checking
  		flagerror(MEMORY_ALLOCATION_ERROR);
  		while(1);
    }

	arm_fir_init_f32(S,n_coefs,h,pState,blocksize);

	while(1){
		getblock(input);
		DIGITAL_IO_SET();
		arm_fir_f32(S,input,output,blocksize);
		DIGITAL_IO_RESET();
		putblock(output);
	}
	return 0;
}
