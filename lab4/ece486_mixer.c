#include "ece486_nco.h"
#include "ece486_mixer.h"
#include "ece486_biquad.h"
#include <stdio.h>
#include <stdlib.h>


void decimate(*s, *input){
	int i;

	for (i = 0; i < s->blocksize/5; i++){
		s->data = input[i*5];
	}
}

void sinusoidal_mult(*s, *nco){
	int i;
	float y[s->blocksize/5];

	nco_get_samples(nco, y, s->blocksize/5);

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
	mixer->data_squared = (float *)malloc(sizeof(float)*bs/5);
	if(mixer->data_squared == NULL) {
		printf("Could not allocate an data squared array");
		exit(0);
	}
	mixer->blocksize = bs;
	mixer->Fs = Fs;
	mixer->nco_data = init_nco(center_freq/(Fs/decimation),theta);

	return mixer;
}

void destroy_mixer(FSK_T *mixer){
	destroy_nco(mixer->nco_data);
	free(mixer->data_squared);
	free(mixer->data);
	mixer->data_squared = NULL;
	mixer->data = NULL;
	free(mixer);
	mixer = NULL;
}
