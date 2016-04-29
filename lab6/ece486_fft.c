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
	if(button_flag == 1){
		for (i = (FFTSAMPLES/3)-1; i > 38 ; i--) {
			if ((data[i] >= thresh) && (data[i-1] < data[i]) && (data[i+1] < data[i])){
				return i;
			}
		}
	}

	if(button_flag == -1){
		for (i = (2*FFTSAMPLES/3) + 1; i < 986; i++) {
			if ((data[i] >= thresh) && (data[i-1] < data[i]) && (data[i+1] < data[i])){
				return i;
			}
		}
	}

	return -1;
}


int fft(float *buffer, float thresh,  int button_flag)
{
	static float output[FFTSAMPLES] = {0};
	int ifftFlag = 0;
	int doBitReverse = 1;

	arm_cfft_f32(&arm_cfft_sR_f32_len1024, buffer, ifftFlag, doBitReverse);
	arm_cmplx_mag_f32(buffer, output, FFTSAMPLES);

	return peak_detect(output, thresh, button_flag);
}

void velocity_conversion_display(int peak_index, int button_flag)
{
	clear_screen();
	if (peak_index == -1){
		BSP_LCD_GLASS_DisplayString((uint8_t *)"------");
		return;
	}
	char lcd_str[8] = {0};
	float scale =  .15153556; //(6e3/1024/2/5.8e9*3e8)
	if (button_flag == 1) sprintf(lcd_str, "-%.1f", peak_index * scale);
	if (button_flag == -1) sprintf(lcd_str, "%.1f", (FFTSAMPLES-peak_index) * scale);
	BSP_LCD_GLASS_DisplayString((uint8_t *)lcd_str);

}

void clear_screen(void)
{
	BSP_LCD_GLASS_DisplayString((uint8_t *)"        ");
}
