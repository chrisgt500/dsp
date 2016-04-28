#ifndef ECE486_FFT_H
#define ECE486_FFT_H

#ifndef FFTSAMPLES
#define FFTSAMPLES 1024
#endif

//probably could take just a struct to make this better
int peak_detect(float *data, float thresh, int button_flag);

void fft(float *buffer, float thresh, float *peak_index, int button_flag);

void window(float *input);

void velocity_conversion_display(float *peak_index, int button_flag);

void clear_screen(void);


#endif
