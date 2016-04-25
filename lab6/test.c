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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ece486.h"
#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include "ece486_fft.h"


extern FlagStatus KeyPressed;

int main(int argc, char *argv[])
{
	float *input1, *input2;
	char lcd_str[8];
	int *peak_index;


	setblocksize(FFTSAMPLES); //FUN FACT, THIS NEEDS TO BE CALLED BEFORE initialize
	initialize(FS_48K, STEREO_IN, MONO_OUT);


	input1 = (float *)malloc(sizeof(float)*FFTSAMPLES);
	input2 = (float *)malloc(sizeof(float)*FFTSAMPLES);

	if (input1==NULL || input2==NULL) {
		flagerror(MEMORY_ALLOCATION_ERROR);
		while(1);
	}

	while(1){
		getblockstereo(input1,input2);

		fft(input1, input2, 1, peak_index);

		sprintf(lcd_str, "%f  ", peak_index);

		BSP_LCD_GLASS_DisplayString((uint8_t *)lcd_str);

		putblock(input1);

	}


	return 0;



}
