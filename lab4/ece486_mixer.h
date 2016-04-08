/*!
 * @file ece486_mixer.h
 *
 * @brief Gives function prototypes for ece486_mixer.h
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
 * initial values of of the struct.  Decimate and antidecimate reduce the sample rate by five
 * and increase the sample rate by five, respectively.  sinusoidal_mult takes a decimated signal
 * and multiplies it by e^(-j2*pi*f0*n).  The differentior function takes the derivative of the
 * inputs, and also produces squared data of the last values (n-1) of the inputs.  gain_calc
 * calculates the gain of the system.  The output_stage calculates the division of the imaginary
 * derivative minus the real derivative over the squared data, and then applies the gain.
 * destroy_mixer destroys the structure and cleans up the memory.
 *
 */


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

void differentiator(
	FSK_T *real,
	FSK_T *imaginary,
	float *output,
  float *sq_data
);
/*
void data_squared(
	FSK_T *mixer1,
	FSK_T *mixer2,
	float *output
);
*/

void output_stage(
	float *x,
	float *y,
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
	BIQUAD_T *filter3,
	float *demod_output
);

void antidecimate(
	float *demod_data,
	int decimation,
	int blocksize,
	float *output
);

#endif
