#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include "ece486.h"

#include "ece486_nco.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int main(void){

	int i, blocksize;
	float fs;
	float mod = 0;

	NCO_T *c;
	NCO_T *s;

	float *input, *output1, *output2;
	initialize(FS_50K, MONO_IN, STEREO_OUT);//
	fs = getsamplingfrequency();//
	blocksize = getblocksize();//


	//blocksize = 100;

	output2 = (float *)malloc(sizeof(float)*blocksize);
	output1 = (float *)malloc(sizeof(float)*blocksize);
	input = (float *)malloc(sizeof(float)*blocksize);

	c = init_nco(.01, 0);
	s = init_nco(.01, M_PI);

	/*nco_get_samples(c,output,blocksize);

	for ( i = 0; i < blocksize ; i++){
		printf("cos(%f) = %f \n",fmodf(c->theta_const + 2 * M_PI * c->f0 * (i+1),(2*M_PI)),output[i]);
	}

	nco_get_samples(c,output,blocksize);

	for ( i = 0; i < blocksize ; i++){
		printf("cos(%f) = %f \n",fmodf(c->theta_const + 2 * M_PI * c->f0 * (i+1),(2*M_PI)),output[i]);
	}
	*/

	while(1){
		getblock(input);  //FUN FACT: YOU NEED TO CALL GETBLOCK EVEN IF YOU DONT NEED IT

		mod = fmodf(mod + .02, .1);
		nco_set_frequency(c,mod);
		nco_get_samples(c,output1,blocksize);

		nco_get_samples(s,output2,blocksize);
		putblockstereo(output1,output2);
	}
}
