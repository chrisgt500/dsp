



#ifndef ECE486_MIXER_H
#define ECE486_MIXER_H



typedef struct{
	float *data;
	int blocksize;
	int Fs;
	NCO_T *nco_data;
} FSK_T;

void decimate(
	FSK_T *,
	float *
);

void sinusoidal_mult(
	FSK_T *,
	NCO_T *
);

FSK_T * init_mixer(
	int bs,
	float Fs,
	int center_freq,
	float theta,
	int decimation,
	float * z
);

void * destroy_mixer(
	FSK_T * mixer
);

float * differential(
	FSK_T * re_mix,
	FSK_T * im_mix
);

float * data_squared(
	FSK_T * mixer1,
	FSK_T * mixer2
);

float * output_stage(
	float * real,
	float * im,
	float * data_sq,
	int bs_nco,
	float gain
);

float gain_calc(

);

float * demod(

);

float * antidecimate(

);

#endif
