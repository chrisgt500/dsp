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
	FSK_T *mixer,   //!< [in,out] pointer to an FSK_T structure
	float *input   //!< [in] input data stream to be decimated
);

/*!
 *@Brief A function for multiplying decimated data by e^(j*2*pi*f0*n).
 *
 * This function takes an FSK_T pointer.  It then creates a local array that is
 * the size of the decimated data; the NCO_T data is then passed to nco_get_samples.
 * and get samples is stored in y.  The mixer->data array is then multiplied by the
 * data that was retrieved from the NCO.
 *
 *@returns On return, the modified decimated data is stored in the FSK_T structure.
 */

void sinusoidal_mult(
	FSK_T *mixer	//! [in,out] pointer to an FSK_T structure
);

/*!
 *@Brief A function for initializing FSK_T structures.
 *
 * This function dynamically allocates the memory need for FSK_T structures. It then
 * assigns the passed paramters to the proper structure elements.
 *
 *@returns On return, an allocated FSK_T structure is returned according to the parameters
 *that the function was passed.
 */

FSK_T * init_mixer(
	int bs,		//!< [in] blocksize
	float Fs,	//!< [in] sample rate
	int center_freq,	//!< [in] center frequency for the NCO
	float theta,	//!< [in] initial phase of the output samples
	int decimation	//!< [in] rate of decimation
);

/*!
 *@Brief A function to destroy an FSK_T structure.
 *
 * This function frees the memory allocated to the FSK_T structure by the
 * init_mixer function and sets all associated pointers to NULL.
 *
 *@returns Any resources associated with the FSK_T structure are released.
 */
void destroy_mixer(
	FSK_T *mixer	//!< [in,out] pointer to an FSK_T structure
);

/*!
 *@Brief A function for diffentiating and squaring data.
 *
 * The function takes pointers to two FSK_T structures; it then takes the structures
 * and calculates the derivative for each one and subtracts the derivative of the imaginary
 * data from the derivative of the real data.  In addition, it calculates the the addition of
 * the last sample's real data, squared, with the last sample's imaginary data, squared. This
 * yields the array called sq_data.
 *
 *@returns On return, the squared data is strored in sq_data, and the subtraction of
 *the differentiated data is stored in output.
 */

void differentiator(
	FSK_T *real,	//!< [in] a pointer to an FSK_T structure holding the real data
	FSK_T *imaginary,		//!< [in] a pointer to an FSK_T structure holding the imaginary data
	float *output,	//!< [in, out] a pointer to the array where derivative subtraction is stored
  float *sq_data	//!< [in,out] a pointer to the array where the real data is stored
);

/*!
 *@Brief A function that calculates the output data to pass to antidecimate.
 *
 * The function takes the input arrays x and y and divides them.  It stores them in
 * the array output_stage_output, and then applies the overall gain of the system to each
 * element.
 *
 *@returns On return, the demodulated data is stored in output_stage_output.
 */

void output_stage(
	float *x,		//!< [in] a pointer to the subtraction of the differentiated data
	float *y,		//!< [in] a pointer to the squared data
	int bs_nco,		//!< [in] the size of the array to iterate over
	float gain,		//!< [in] the gain term to apply to each element
	float *output_stage_output		//!< [in,out] a pointer to the demondulated data
																//!< which will be passed to antidecimate
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
