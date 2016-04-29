/*!
 * @file ece486_fft.c
 *
 * @brief This file implements the fft, peak detecting, and display functions
 * necessary for the Doppler radar.
 *
 * This file contains all the functions neccesary to implement a Dopler radar. The
 * peak_detect function takes an array of fft outputs of length 1024 from the fft function
 * and finds the maximum value of the fft for the appropriate ranges.  The fft function uses
 * the arm_cfft_f32 and arm_cmplx_mag_f32 to perform an fft and then calls peak_detect to
 * find the maximum value in the appropriate ranges.  The velocity_conversion_display function
 * takes an fft index from peak_detect and converts it into an appropriate velocity, which is
 * then displayed on the LCD.  The clear screen function clears the screen, in a rather ghetto
 * manner.
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary
 * @author Forrest Smith
 * @author Sean Turner
 *
 * @date April 29, 2016
 *
 */
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "arm_math.h"
#include "arm_const_structs.h"
#include "ece486_fft.h"
#include "ece486.h"
#include "init486.h"



int peak_detect(float *data, float thresh, int button_flag)
{
	int i;


	// This assumes that 0-.5 is positive freqs and .5 - 1 is negative freqs
	if(button_flag == 1){		//flag for negative velocities
		for (i = (FFTSAMPLES/3)-1; i > 38 ; i--) {		//only search fft array in the region necessary
			//checks fft output to ensure it is above threshhold and greater than the previous and
			//precdining points, if all conditions are met return the fft index
			if ((data[i] >= thresh) && (data[i-1] < data[i]) && (data[i+1] < data[i])){
				return i;
			}
		}
	}

	if(button_flag == -1){	//flag for positive velocities
		for (i = (2*FFTSAMPLES/3) + 1; i < 986; i++) {	//only search for positive velocities
			//same peak detecting conditions as loop above
			if ((data[i] >= thresh) && (data[i-1] < data[i]) && (data[i+1] < data[i])){
				return i;
			}
		}
	}
	//if no peak is found return negative one
	return -1;
}


int fft(float *buffer, float thresh,  int button_flag)
{
	static float output[FFTSAMPLES] = {0};	//output array for arm_cmplx_mag_f32
	int ifftFlag = 0;	//appropriate ifftFlag and BitReverse flag values
	int doBitReverse = 1;

	//performs 1024 point fft on real and complex data
	arm_cfft_f32(&arm_cfft_sR_f32_len1024, buffer, ifftFlag, doBitReverse);
	//combines the complex and real fft data into a single magnitude
	arm_cmplx_mag_f32(buffer, output, FFTSAMPLES);

	//does peak detecting and function returns the peak fft index
	return peak_detect(output, thresh, button_flag);
}

void velocity_conversion_display(int peak_index, int button_flag)
{

	clear_screen();	//clears screen initially
	//if a peak was not found, display the string below
	if (peak_index == -1){
		BSP_LCD_GLASS_DisplayString((uint8_t *)"------");
		return;
	}
	char lcd_str[8] = {0};	//character array for the lcd write
	float scale =  .15153556; //(6e3/1024/2/5.8e9*3e8) calculation for scale factor
	//write negative velocities to lcd_str
	if (button_flag == 1) sprintf(lcd_str, "-%.1f", peak_index * scale);
	//write positive velocities to lcd_str
	if (button_flag == -1) sprintf(lcd_str, "%.1f", (FFTSAMPLES-peak_index) * scale);
	BSP_LCD_GLASS_DisplayString((uint8_t *)lcd_str); //display values

}

void clear_screen(void)
{
	//the most ghetto clear screen function you've ever seen
	BSP_LCD_GLASS_DisplayString((uint8_t *)"        ");
}
