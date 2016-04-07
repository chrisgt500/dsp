#include "newnco.h"
#include "ece486_biquad.h"
#include "ece486_mixer.h"
#include <stdio.h>
#include <stdlib.h>
#include "ece486.h"
#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"


void decimate(FSK_T *s, float *input){
	int i;

	for (i = 0; i < s->blocksize/s->decimation; i++){
		s->data[i] = input[i*5];
	}
}

void sinusoidal_mult(FSK_T *s){
	int i;
	float y[s->blocksize/s->decimation];

	nco_get_samples(s->nco_data, y, s->blocksize/s->decimation);

	for(i = 0; i < s->blocksize/s->decimation; i++){
		s->data[i] = s->data[i] * y[i];
	}
}

FSK_T * init_mixer(int bs, float Fs, int center_freq, float theta, int decimation){
	FSK_T *mixer = (FSK_T *)malloc(sizeof(FSK_T));
	if(mixer == NULL) {
		printf("Could not allocate an FSK_T struct");
		exit(0);
	}
	mixer->data = (float *)malloc(sizeof(float)*bs/decimation);
	if(mixer->data == NULL) {
		printf("Could not allocate a data array");
		exit(0);
	}
	mixer->blocksize = bs;
	mixer->Fs = Fs;
	mixer->nco_data = init_nco(center_freq/(Fs/decimation),theta);
	mixer->decimation = decimation;
	mixer->z = (float *)malloc(sizeof(float) * 2);
	if(mixer->z == NULL) {
		printf("Could not allocate a z array");
		exit(0);
	}
	(mixer->z)[0] = 0;
	(mixer->z)[1] = 0;


	return mixer;
}

void destroy_mixer(FSK_T *mixer){
	destroy_nco(mixer->nco_data);
	free(mixer->z);
	mixer->z = NULL;
	free(mixer->data);
	mixer->data = NULL;
	free(mixer);
	mixer = NULL;
}

void differentiator(FSK_T *real, FSK_T *imaginary, float *output, float *sq_data){
	int i;

	/*for (i = 0 ; i < (mixer1->blocksize/mixer1->decimation); i++) {
		if (i < 2) output[i] = (mixer1->data[i] - mixer1->z[i]);// * mixer2->data[i];
		else output[i] = (mixer1->data[i] - mixer1->data[i-2]);// * mixer2->data[i];
	}

	(mixer1->z)[0] = mixer1->data[i-2];
	(mixer1->z)[1] = mixer1->data[i-1];
	*/
	for ( i = 0; i < ((real->blocksize)/(real->decimation)); i++){

		if( i == 0){
			output[i] = ((imaginary->data[i] - imaginary->z[0]) * real->z[1]) -
						((real->data[i] - real->z[0]) * imaginary->z[1]);
			sq_data[i] = (real->z[1] * real->z[1]) + (imaginary->z[1]* imaginary->z[1]);

		}

		else if(i == 1){
			output[i] = ((imaginary->data[i] - imaginary->z[1]) * real->data[i-1]) -
						((real->data[i] - real->z[1]) * imaginary->data[i-1]);
			sq_data[i] = (real->data[i-1] * real->data[i-1]) + (imaginary->data[i-1] * imaginary->data[i-1]);

		}

		else{
			output[i] = ((imaginary->data[i] - imaginary->data[i-2]) * real->data[i-1]) -
						((real->data[i] - real->data[i-2]) * imaginary->data[i-1]);
			sq_data[i] = (real->data[i-1] * real->data[i-1]) + (imaginary->data[i-1] * imaginary->data[i-1]);
		}
	}

	(real->z)[0] = real->data[i-2];
	(real->z)[1] = real->data[i-1];
	(imaginary->z)[0] = imaginary->data[i-2];
	(imaginary->z)[1] = imaginary->data[i-2];

	//testing
	//for ( i = 0; i < ((real->blocksize)/(real->decimation)); i++){
	//	output[i] = output[i]/sq_data[i];
	//}

}

/*
void data_squared(FSK_T *mixer1, FSK_T *mixer2, float *output){
	int i;


	for (i = 0 ; i < (mixer1->blocksize/mixer1->decimation); i++) {
		output[i] = (mixer1->data[i] * mixer1->data[i]) +
					(mixer2->data[i] * mixer2->data[i]);
	}
}
*/

void output_stage(float *x, float *y, int bs_nco, float gain, float *output_stage_output){
	int i;

	for (i = 0; i < bs_nco ; i++){
		output_stage_output[i] = x[i]/y[i];
		output_stage_output[i] *= gain;
		}
}

float gain_calc(float fs){
	return (fs/(4*PI*1000));
}

void demod(float *input, FSK_T *real, FSK_T *imaginary, BIQUAD_T *filter1, BIQUAD_T *filter2, BIQUAD_T *filter3, float *demod_output){
	int bs_nco = real->blocksize / real->decimation ;
	float sq_data[bs_nco];
	float output1[bs_nco];
	float output2[bs_nco];
	float output3[bs_nco];

	// First LP filter
	calc_biquad(filter1, input, output1);

	//"Decimating" the data
	decimate(real, output1);
	decimate(imaginary, output1);

	//Separating real and imaginary signals
	sinusoidal_mult(real);
	sinusoidal_mult(imaginary);

	//Filter each signal separately
	calc_biquad(filter2, real->data, real->data);
	calc_biquad(filter3, imaginary->data, imaginary->data);

	//Differentation of the signals
	differentiator(real, imaginary, output1, sq_data);

	//Add real and imaginary signals and divide by sq data and apply gain
	output_stage(output1,sq_data,bs_nco,gain_calc(real->Fs/real->decimation),output3);

	//Antidecimates the signal in prep to go to the DAC
	antidecimate(output3, real->blocksize, real->decimation, demod_output);
}

void antidecimate(float *demod_data, int blocksize, int decimation, float *output){
	int i;

	for (i = 0; i < blocksize; i++){
		output[i] = demod_data[i/decimation];
	}
}
