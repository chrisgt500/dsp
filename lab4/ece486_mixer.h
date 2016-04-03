



#ifndef ECE486_MIXER_H
#define ECE486_MIXER_H



typedef struct{
	float *data;
	int blocksize;
	int Fs;
	NCO_T *nco_data;
} FSK_T;

void decimate(
	FSK_T *mixer,
	float *input
);

void sinusoidal_mult(
	FSK_T *mixer
);

FSK_T * init_mixer(
	int bs,
	float Fs,
	int center_freq,
	float theta,
	int decimation,
	float *z
);

void * destroy_mixer(
	FSK_T *mixer
);

float * differential(
	FSK_T *re_mix,
	FSK_T *im_mix
);

float * data_squared(
	FSK_T *mixer1,
	FSK_T *mixer2
);

float * output_stage(
	float *real,
	float *im,
	float *data_sq,
	int bs_nco,
	float gain
);

float gain_calc(
	float fs
);

float * demod(
	float *input,
	FSK_T *real,
	FSK_T *imag,
	BIQUAD_T *filter1,
	BIQUAD_T *filter2
);

float * antidecimate(
	float *demod_data,
	int decimation,
	int blocksize
);

#endif
