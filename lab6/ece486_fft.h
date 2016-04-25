#ifndef ECE486_FFT_H
#define ECE486_FFT_H

#ifndef FFTSAMPLES
#define FFTSAMPLES 512
#endif

//probably could take just a struct to make this better
void peak_detect(float *data, float thresh, float *farthest_peak_index);

void fft(float *input_real, float *input_complex, float thresh, float *peak_index);

void window(float *input);

void velocity_conversion_display(float *peak_index);

#endif
