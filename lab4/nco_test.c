#include "ece486_nco.h"
#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include "ece486.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


void main(void){

	int i, blocksize;
	float *s, *c;
	float *output1, *output2;

	initialize(FS_50k, MONO_IN, STEREO_OUT)

	fs = getsamplingfrequency();
	blocksize = getblocksize();

	while(1){
		c = init_nco(.1, 0.0);
		s = init_nco(.1,-PI/2);

		nco_get_samples(s,output1,blocksize);
		nco_get_samples(c,output2,blocksize);

		putblockstereo(output1, output2);
	}

}
