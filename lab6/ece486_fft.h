#ifndef ECE486_FFT_H
#define ECE486_FFT_H

//probably could take just a struct to make this better
int peak_detect(float *data, int size, float thresh, int *peaks, int farthest_peak_index);

void fft(float *input_real, float *input_complex, int fftsize, int peak_index);

void window(void *input, int length);


#endif
