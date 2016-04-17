#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include "ece486.h"

#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ece486_nco.h"


int main(void){

	int i, blocksize;	//initialize variables for a counter and blocksize
	float fs;	//initialize variable for sampling frequency

	//declarations for NCO_T structures for testing
	NCO_T *c;
	NCO_T *s;


	float *input, *output1, *output2;	//declarations for testing array
	initialize(FS_50K, MONO_IN, STEREO_OUT);	//STM board initializations
	fs = getsamplingfrequency();	//STM function to get frequency
	blocksize = getblocksize();		//STM function to get blocksize

	//memory allocations for arrays that will store the tested data
	output2 = (float *)malloc(sizeof(float)*blocksize);
	output1 = (float *)malloc(sizeof(float)*blocksize);
	input = (float *)malloc(sizeof(float)*blocksize);

	//NCO_T initializations for different phase shifted signals
	c = init_nco(.1, 0);
	s = init_nco(.1, M_PI);

	//test case used to output to the terminal instead of the board.

	//blocksize = 100;
	/*
	nco_get_samples(c,output1,blocksize);

	for ( i = 0; i < blocksize ; i++){
		printf("Value of %d: [%f]\n",i,output1[i]);
	}
	*/

	//testing NCO using the STM board
	while(1){
		getblock(input);  //FUN FACT: YOU NEED TO CALL GETBLOCK EVEN IF YOU DONT NEED IT
		nco_get_samples(c,output1,blocksize);
		nco_get_samples(s,output2,blocksize);
		putblockstereo(output1,output2);
	}

	return 0;
}
