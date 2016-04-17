/*!
 * @file ece486_mixer.c
 *
 * @brief Gives function declarations for ece486_mixer.c
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary
 * @author Forrest Smith
 * @author Sean Turner
 *
 * @date April 7, 2016
 *
 * This file contains the functions needed to implement several filters, a decimator,
 * an antidecimator, and an FM demodulator. The struct definition declares the values
 * needed and places them within a typedeffed FSK_T struct. The init_mixer function sets the
 * initial values of of the struct.  Decimate and antidecimate reduce the sample rate by a decimation value
 * and increase the sample rate by a decimation value, respectively.  sinusoidal_mult takes a decimated signal
 * and multiplies it by e^(-j2*pi*f0*n).  The differentior function takes the derivative of the
 * inputs, and also produces squared data of the last values (n-1) of the inputs.  gain_calc
 * calculates the gain of the system.  The output_stage calculates the division of the imaginary
 * derivative minus the real derivative over the squared data, and then applies the gain.
 * destroy_mixer destroys the structure and cleans up the memory.
 *
 */

#include "ece486_nco.h"
#include "ece486_biquad.h"
#include "ece486_mixer.h"
#include <stdio.h>
#include <stdlib.h>
#include "ece486.h"
#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"


void decimate(FSK_T *s, float *input){
	int i;

	for (i = 0; i < s->blocksize/s->decimation; i++){  //Only keep every fifth sample
		s->data[i] = input[i*5];
	}
}

void sinusoidal_mult(FSK_T *s){
	int i;
	float y[s->blocksize/s->decimation];

	nco_get_samples(s->nco_data, y, s->blocksize/s->decimation); //Loads blocksize/decimation values of a cos
																 // or -sin into a y array

	for(i = 0; i < s->blocksize/s->decimation; i++){ //multiply by said sinusoid
		s->data[i] = s->data[i] * y[i];
	}
}

FSK_T * init_mixer(int bs, float Fs, int center_freq, float theta, int decimation){
	FSK_T *mixer = (FSK_T *)malloc(sizeof(FSK_T));  //memory allocation and error checking for the struct
	if(mixer == NULL) {
		printf("Could not allocate an FSK_T struct");
		exit(0);
	}
	mixer->data = (float *)malloc(sizeof(float)*bs/decimation); //memory allocation and error checking for a data array
	if(mixer->data == NULL) {
		printf("Could not allocate a data array");
		exit(0);
	}
	mixer->blocksize = bs; //holds some helpful information
	mixer->Fs = Fs;
	mixer->decimation = decimation;
	mixer->nco_data = init_nco(center_freq/(Fs/decimation),theta); //initializes and stores the NCO struct
	mixer->z = (float *)malloc(sizeof(float) * 2);  //memory allocation and error checking for an array to hold two intermediate values
	if(mixer->z == NULL) {
		printf("Could not allocate a z array");
		exit(0);
	}
	(mixer->z)[0] = 0;  //Make sure these are zero
	(mixer->z)[1] = 0;


	return mixer;
}

void destroy_mixer(FSK_T *mixer){
	destroy_nco(mixer->nco_data); //frees and set to NULL the NCO struct
	free(mixer->z);  //frees and sets to NULL all allcoated arrrays
	mixer->z = NULL;
	free(mixer->data);
	mixer->data = NULL;
	free(mixer); //frees and sets to NULL the mixer array
	mixer = NULL;
}

void differentiator(FSK_T *real, FSK_T *imaginary, float *output, float *sq_data){
	int i;
	//Performs edge cases require an intermediate array z[]. These are done
	//outside of the loop to prevent nested if statements in the for loop
	output[0] = ((imaginary->data[0] - imaginary->z[0]) * real->z[1]) -
				((real->data[0] - real->z[0]) * imaginary->z[1]);
	sq_data[0] = (real->z[1] * real->z[1]) + (imaginary->z[1]* imaginary->z[1]);

	output[1] = ((imaginary->data[1] - imaginary->z[1]) * real->data[0]) -
				((real->data[1] - real->z[1]) * imaginary->data[0]);
	sq_data[1] = (real->data[0] * real->data[0]) + (imaginary->data[0] * imaginary->data[0]);

	//Loops over most values in the array, and performs the differentiation as
	//calculated and shown in Homework 4
	for ( i = 2; i < ((real->blocksize)/(real->decimation)); i++){

		output[i] = ((imaginary->data[i] - imaginary->data[i-2]) * real->data[i-1]) -
					((real->data[i] - real->data[i-2]) * imaginary->data[i-1]);
		sq_data[i] = (real->data[i-1] * real->data[i-1]) + (imaginary->data[i-1] * imaginary->data[i-1]);
	}

	//Updates the last two values into an intermediate array
	(real->z)[0] = real->data[i-2];
	(real->z)[1] = real->data[i-1];
	(imaginary->z)[0] = imaginary->data[i-2];
	(imaginary->z)[1] = imaginary->data[i-1];
}

void output_stage(float *x, float *y, int bs_nco, float gain, float *output_stage_output){
	int i;

	//Performs the needed division and appplies the appropriate gain
	for (i = 0; i < bs_nco ; i++){
		output_stage_output[i] = x[i]*gain/y[i];
	}
}

float gain_calc(float fs){
	return (fs/(4*PI*1000));  //calculates the required gain to shift 1V for a 1kHz difference
}


void antidecimate(float *demod_data, int blocksize, int decimation, float *output){
	int i;

	//Extrapolates every point by decimation value (ensures proper DAC output)
	for (i = 0; i < blocksize; i++){
		output[i] = demod_data[i/decimation];
	}
}
