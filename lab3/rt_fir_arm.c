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
#include "ece486_fir.h"

#include "ece486.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
	float *input, *output; //initializations
    int blocksize;
	struct arm_fir_instance_f32 *S;
	float *pState;

	float h[20] ={2.2044, 1.3420, .8827, -.7646,-1.3219,-.0629,1.2442,.8185,-.7088,-1.2257,
                  -.0585, 1.1535, .759,-.6571,-1.1364,-.0544,1.0695,.7038,-.6091,-1.0537};
  				/*Not sure if these coefs are correct + ARM might take these backwards*/
	/*float h[20] ={-1.0537, -.6091, .7038, 1.0695, -.0544, -1.1364, -.6571, .759, 1.1535, -.0585,
					-1.2257, -.7088, .8185, 1.2442, -.0629, -1.3219, -.7646, .8827, 1.3420, 2.2044};
					*/
	int n_coefs = 20;

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
