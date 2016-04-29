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
 * function, a fft function, a velocity conversion function
 *
 */

#ifndef ECE486_FFT_H
#define ECE486_FFT_H

#ifndef FFTSAMPLES
#define FFTSAMPLES 1024
#endif

//probably could take just a struct to make this better
int peak_detect(float *data, float thresh, int button_flag);

void fft(float *buffer, float thresh, float *peak_index, int button_flag);

void velocity_conversion_display(float *peak_index, int button_flag);

void clear_screen(void);


#endif
