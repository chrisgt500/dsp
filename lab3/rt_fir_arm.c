/*!
 * @file
 * @brief ECE 486 Lab 3 Real Time ARM FIR implementation
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @Note Help from Don Hummels
 *
 * @date Mar 15 2016
 *
 * This program implements the optimized ARM routine for the FIR filter structure, essentially a
 * convolution. The impulse response vector is stored in a time reversed order, and arm_fir_instance_f32
 * and pState are vectors that must be initialized by the user. The ADC fills up, the data array
 * is passed to arm_fir_f32 function which filters the data, and returns it to the DAC for outputting.
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

	float h[30] = {0.0830,0.0321,0.0084,0.0055,-0.0688,-0.1251,-0.0047,0.1684,0.1265,-0.0722,-0.1293,-0.0274,0.0009,-0.0263,0.0868,0.1951,-0.0021,-0.2930,-0.1819,0.2174,0.2893,
					-0.0521,-0.2470,-0.0603,0.1296,0.0736,-0.0393,-0.0374,0.0048,0.0090};
					/* These came from impz(SOS,n) in MATLAB, for the structure used in task 2*/

	int n_coefs = 30;

	initialize(FS_50K, MONO_IN, MONO_OUT);
	blocksize = getblocksize();


	input = (float *)malloc(sizeof(float)*blocksize); //dynamic allocation of vectors
	output = (float *)malloc(sizeof(float)*blocksize);
	pState = (float *)malloc(sizeof(float)*(n_coefs+blocksize-1));

    if (input==NULL || output==NULL || pState==NULL) {  //error checking
  		flagerror(MEMORY_ALLOCATION_ERROR);
  		while(1);
    }

	arm_fir_init_f32(S,n_coefs,h,pState,blocksize);  //ARM state vector initializations

	while(1){  //waits for ADC to fill, filters data, outputs to DAC
		getblock(input);
		DIGITAL_IO_SET();
		arm_fir_f32(S,input,output,blocksize);
		DIGITAL_IO_RESET();
		putblock(output);
	}
	return 0;
}
