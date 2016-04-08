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
#define PI 3.14159265359  //!< PI
#endif

/*!
 * @brief A structure for holding FSK_T components
 *
 * The FSK_T structure is used to hold all of the values needed to execute
 * the sinusoidal_mult and FM demodulation.
 *
 */

typedef struct{
	float *data;   //!< data arrays for real and imaginary decimated data
	int blocksize;   //!< blocksize of the data
	int Fs;   //!< sampling frequncy
	NCO_T *nco_data;   //!< NCO_T structure
	int decimation;  //!< rate of decimation
	float *z;  //!< array to store previous two values
} FSK_T;

/*!
 *@Brief A function for decimating data.
 *
 * This function takes an FSK_T pointer and a pointer to a float array.  It then
 * takes the in the float array and decimates it by the factor stored in the FSK_T
 * structure.  The decimated data is then stored in the FSK_T structure.
 *
 *@returns On return, the decimated data is stored in the FSK_T structure.
 */

void decimate(
	FSK_T *mixer,   //!< [in,out] pointer to FSK_T
	float *input   //!< [in] input data stream to be decimated
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

/*!
 *@Brief A function for calculating the gain.
 *
 * The function takes a sample rate and divides by 4*pi*10^3 in order to produce
 * a change of 1.0 for every 1kHz deviation.
 *
 *@returns On return, the calculated gain is returned..
 */

float gain_calc(
	float fs   //!< [in] sampling frequency used for gain calculation
);


/*!
 *@Brief A function for antidecimating data.
 *
 * This function takes a float pointer to the demodulated data, two integers for blocksize
 * and decimation, and a float point to the output. It then takes the demodulated data and
 * antidecimates it by the decimation factor. The decimated data is then stored in the
 * output array.
 *
 *@returns On return, the antidecimated data is stored in the in the output array.
 */

void antidecimate(
	float *demod_data, //!< [in] point to demodulated data
	int decimation,  //!< [in] decimation factor
	int blocksize,   //!< [in] blocksize before decimation
	float *output  //!< [out] pointer to float array for antidecimated data
);

#endif
