#ifndef ECE486_FFT_H
#define ECE486_FFT_H

#ifndef FFTSAMPLES
#define FFTSAMPLES 1024
#endif

//probably could take just a struct to make this better
void peak_detect(float *data, float thresh, float *farthest_peak_index, int button_flag);

void fft(float *buffer, float thresh, float *peak_index, int button_flag);

void window(float *input);

void velocity_conversion_display(float *peak_index);

void clear_screen(void);

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
	int blocksize,   //!< [in,out] pointer to an FSK_T structure
  int decimation,
	float *input,   //!< [in] input data stream to be decimated
  float *output
);

#endif
