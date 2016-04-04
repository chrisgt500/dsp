#ifndef ECE486_MIXER_H
#define ECE486_MIXER_H

#ifndef PI
#define PI 3.14159265359
#endif


typedef struct{
	float *data;
	int blocksize;
	int Fs;
	NCO_T *nco_data;
	int decimation;
	float *z;
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
	int decimation
);

void destroy_mixer(
	FSK_T *mixer
);

void differential(
	FSK_T *re_mix,
	FSK_T *im_mix,
	float *output
);

void data_squared(
	FSK_T *mixer1,
	FSK_T *mixer2,
	float *output
);

void output_stage(
	float *real,
	float *im,
	float *data_sq,
	int bs_nco,
	float gain,
	float *output_stage_output
);

float gain_calc(
	float fs
);

void demod(
	float *input,
	FSK_T *real,
	FSK_T *imag,
	BIQUAD_T *filter1,
	BIQUAD_T *filter2,
	float *demod_output
);

void antidecimate(
	float *demod_data,
	int decimation,
	int blocksize,
	float *output
);

#endif
