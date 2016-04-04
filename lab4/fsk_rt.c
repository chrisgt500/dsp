#include "ece486_nco.h"
#include "ece486_biquad.h"
#include "ece486_mixer.h"
//#include "ece486.h"
//#include "stm32l4xx_hal.h"
//#include "stm32l476g_discovery.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){

	float *input, *output1, *output2;
	BIQUAD_T *filter1;
	BIQUAD_T *filter2;
	int blocksize, i;
	int decimation = 5;
	int sections1 = 7;
	int sections2 = 6;
	float gain = 1;
	float fs;

	//initialize(FS_50K, MONO_IN, STEREO_OUT);
	blocksize = 100;
	//fs = getsamplingfrequency();
	//blocksize = getblocksize();

	float lpf1[35] = {
	1.000000, -1.818543, 1.000000, -1.819877, 0.999565,
	1.000000, -1.817198, 1.000000, -1.819724, 0.998058,
	1.000000, -1.812439, 1.000000, -1.819981, 0.993753,
	1.000000, -1.796425, 1.000000, -1.820970, 0.980982,
	1.000000, -1.736438, 1.000000, -1.823665, 0.946998,
	1.000000, -1.404771, 1.000000, -1.828775, 0.882739,
	1.000000, 1.000000, 0.000000, -0.916116, 0.000000
	};

	float lpf2[30] = {
	1.000000, 1.093320, 1.000000, 1.069351, 0.997195,
	1.000000, 1.110386, 1.000000, 1.048001, 0.987411,
	1.000000, 1.168039, 1.000000, 0.976079, 0.958710,
	1.000000, 1.334212, 1.000000, 0.742831, 0.866916,
	1.000000, 1.701731, 1.000000, 0.025044, 0.584819,
	1.000000, 1.000000, 0.000000, -0.461086, 0.000000
	};

	filter1 = init_biquad(sections1, gain, lpf1, blocksize);
	filter2 = init_biquad(sections2, gain, lpf2, blocksize);

	while(1){




	}


}
