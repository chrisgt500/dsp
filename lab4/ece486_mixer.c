#include "ece486_nco.h"
#include "ece486_mixer.h"
#include "ece486_biquad.h"
#include <stdio.h>
#include <stdlib.h>


void decimate(FSK_T *s, float *input){
	int i;

	for (i = 0; i < s->blocksize/5; i++){
		s->data = input[i*5];
	}
}

void sinusoidal_mult(FSK_T *s){
	int i;
	float y[s->blocksize/5];

	nco_get_samples(s->nco_data, y, s->blocksize/5);

	for(i = 0; i < s->blocksize/5; i++){
		s->data[i] = s->data[i] * y[i];
	}
}

FSK_T * init_mixer(int bs, float Fs, int center_freq, float theta, int decimation){
	FSK_T *mixer = (FSK_T *)malloc(sizeof(FSK_T));
	if(mixer == NULL) {
		printf("Could not allocate an FSK_T struct");
		exit(0);
	}
	mixer->data = (float *)malloc(sizeof(float)*bs/5);
	if(mixer->data == NULL) {
		printf("Could not allocate an data array");
		exit(0);
	}
	mixer->blocksize = bs;
	mixer->Fs = Fs;
	mixer->nco_data = init_nco(center_freq/(Fs/decimation),theta);
	mixer->decimation;
	mixer->z[] = {0.0, 0.0};

	return mixer;
}

void destroy_mixer(FSK_T *mixer){
	destroy_nco(mixer->nco_data);
	mixer->z = NULL;
	free(mixer->data);
	mixer->data = NULL;
	free(mixer);
	mixer = NULL;
}

float * differentiator(FSK_T *mixer1, FSK_T *mixer2){
	int i;
	float output[mixer1->blocksize/mixer1->decimation];

	for (i = 0 ; i < (mixer1->blocksize/mixer1->decimation); i++) {
		if (i < 2) output[i] = (mixer1->data[i] - mixer1->z[i]) * mixer2->data[i];
		else output[i] = (mixer1->data[i] - mixer1->data[i-2]) * mixer2->data[i];
		}
	}

	mixer1->z[0] = mixer1->data[i-2];
	mixer1->z[1] = mixer1->data[i-1];

	return output;
}

float * data_squared(FSK_T *mixer1, FSK_T *mixer2){
	int i;
	float output[mixer1->blocksize/mixer1->decimation];

	for (i = 0 ; i < (mixer1->blocksize/mixer1->decimation); i++) {
		output[i] = mixer1->data[i] * mixer1->data[i] +
					mixer2->data[i] * mixer2->data[i];
	}

	return output;
}

float * output_stage(float *re, float *im, float *data_sq, int bs_nco, float gain){
	int i;
	float output[bs_nco];

	for (i = 0; i < bs_nco ; i++){
		output[i] = (im[i] - re[i]) / data_sq[i];
		output[i] *= gain;
		}

	return output;
}

float gain_calc(float fs){
	return (fs/(4*PI*1000));
}

float * demod(float *input, FSK_T *real, FSK_T *imaginary, BIQUAD_T *filter1, BIQUAD_T *filter2){
	float *output1, *output2;
	float *sq_data;
	float bs_nco;

	bs_nco = real->blocksize / real->decimation ;

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
	calc_biquad(filter2, imaginary->data, imaginary->data);

	//Differentation of the signals
	output1 = differentiator(real, imaginary);
	output2 = differentiator(imaginary, real);

	//Square the data
	sq_data = data_squared(real,imaginary);

	//Add real and imaginary signals and divide by sq data and apply gain
	return output_stage(output1,output2,sq_data,bs_nco,gain_calc(real->fs));
}

float * antidecimate(float *demod_data, int blocksize, int decimation){
	int i;
	float output[blocksize];

	for (i = 0; i < blocksize; i++){
		output[i] = demod_data[i/decimation];
	}
	return output;
}
