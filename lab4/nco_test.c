//#include "stm32l4xx_hal.h"
//#include "stm32l476g_discovery.h"
//#include "ece486.h"

#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "newnco.h"


int main(void){

	int i, blocksize;
	float fs;
	float mod = 0;

	NCO_T *c;
	NCO_T *s;

	float *input, *output1, *output2;
	//initialize(FS_50K, MONO_IN, STEREO_OUT);//
	//fs = getsamplingfrequency();//
	//blocksize = getblocksize();//


	blocksize = 100;

	output2 = (float *)malloc(sizeof(float)*blocksize);
	output1 = (float *)malloc(sizeof(float)*blocksize);
	input = (float *)malloc(sizeof(float)*blocksize);

	c = init_nco(.1, 0);
	s = init_nco(.1, M_PI);

	nco_get_samples(c,output1,blocksize);

	for ( i = 0; i < blocksize ; i++){
		printf("cos(%f) = %f \n",fmodf(0 + 2 * M_PI * .01 * (i+1),(2*M_PI)),output1[i]);
	}

/*
	while(1){
		getblock(input);  //FUN FACT: YOU NEED TO CALL GETBLOCK EVEN IF YOU DONT NEED IT
		nco_get_samples(c,output1,blocksize);
		nco_get_samples(s,output2,blocksize);
		putblockstereo(output1,output2);
	}
	*/
	return 0; 
}
