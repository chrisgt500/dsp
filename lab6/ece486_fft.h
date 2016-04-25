#ifndef ECE486_FFT_H
#define ECE486_FFT_H

#ifndef FFTSAMPLES
#define FFTSAMPLES 512
#endif

//probably could take just a struct to make this better
void peak_detect(float *data, float thresh, int farthest_peak_index);

void fft(float *input_real, float *input_complex, float thresh, int *peak_index);

void window(float *input);


#endif
