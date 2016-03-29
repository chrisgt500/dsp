#include "ece486_nco.h"
#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include "ece486.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


void main(void){

	int i, blocksize;
	float fs;
	
	NCO_T *s = (NCO_T *)malloc(sizeof(NCO_T));
	NCO_T *c = (NCO_T *)malloc(sizeof(NCO_T));

	float *output1, *output2;

	initialize(FS_50K, MONO_IN, STEREO_OUT);

	fs = getsamplingfrequency();
	blocksize = getblocksize();

	output1 = (float *)malloc(sizeof(float)*blocksize);
	output2 = (float *)malloc(sizeof(float)*blocksize);

	while(1){
		c = init_nco(.1, 0.0);
		s = init_nco(.1,-M_PI/2);

		nco_get_samples(s,output1,blocksize);
		nco_get_samples(c,output2,blocksize);

		putblockstereo(output1, output2);
	}

}
