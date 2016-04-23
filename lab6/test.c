/*!
 * @file fsk_rt.c
 *
 * @brief
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary
 * @author Forrest Smith
 * @author Sean Turner
 *
 * @date April 23, 2016
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "ece486.h"
#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include "ece486_fft.h"

extern FlagStatus KeyPressed;

int main(int argc, char *argv[])
{
	/*float data[] = {1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,9.,8.,9.,6.,5.,4.,3.,2.,4.,5.,6.,7.,6.,5.,4.};
	int size = 25;
	float thresh = 3.;
	int max_peak;
	int peaks[] = {0,0,0,0,0,0,0,0,0,0};

	int ret;
	ret = peak_detect(data, size, thresh, peaks, max_peak);

	printf("%d peaks found.\n", ret);
	printf("Peaks found at: ");
	for (ret = 0; ret < 10; ret++) {
		if (peaks[ret]) printf("%d\n", peaks[ret]);
	}*/
	float *input1, *input2;

	setblocksize(FFTSAMPLES); //FUN FACT, THIS NEEDS TO BE CALLED BEFORE initialize
	initialize(FS_50K, STEREO_IN, MONO_OUT);


	input1 = (float *)malloc(sizeof(float)*FFTSAMPLES);
	input2 = (float *)malloc(sizeof(float)*FFTSAMPLES);

	if (input1==NULL || input2==NULL) {
		flagerror(MEMORY_ALLOCATION_ERROR);
		while(1);
	}

	while(1){
		getblockstereo(input1,input2);

		if (KeyPressed) {
			BSP_LED_Toggle(LED5);
			KeyPressed = RESET;
			BSP_LCD_GLASS_DisplayString("Fuck");
		}

	}






	return 0;



}
