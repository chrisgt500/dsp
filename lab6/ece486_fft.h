/*!
 * @file ece486_fft.h
 *
 * @brief Gives function prototypes for ece486_fft.h
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary
 * @author Forrest Smith
 * @author Sean Turner
 *
 * @date April 27, 2016
 *
 * This file contains the functions needed to implement a peak detection
 * function, a fft function, a velocity conversion function and a clear screen
 * function. The peak detect function steps through a passed fft and detects the
 * first peak. The fft function is a wrapper around the arm_cfft_f32() function,
 * which performs the fft and then detects the peak. The velocity converstion
 * function converts the freqency of a detected peal to a velocity and then
 * displays that velocity on the screen. The clear screen function is
 * self-explanatory.
 *
 */

#ifndef ECE486_FFT_H
#define ECE486_FFT_H

#ifndef FFTSAMPLES
#define FFTSAMPLES 1024		//set the number of  samples in the fft
#endif

/*!
 *@Brief A function for detecting the peak of a passed fft.
 *
 * This function checks for peaks based on the state of button_flag. If button
 * flag is 1, then freqencies greater than the center freqency
 *
 *@return The index of the detected peak is returned.
 */

int peak_detect(float *data, float thresh, int button_flag);

int fft(float *buffer, float thresh, int button_flag);

void velocity_conversion_display(float *peak_index, int button_flag);

void clear_screen(void);


#endif
