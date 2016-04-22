#include "arm_math.h"
#include "arm_const_structs.h"

int peak_detect(float *data, int size, float thresh, int *peaks, int farthest_peak_index)
{
	int i, count, index = 0;

	for (i = 1; i < size-1; i++) {
		if (data[i] >= thresh && data[i-1] < data[i] && data[i+1] < data[i])
			peaks[count++] = i+1;
	}


	for(i = 1; i < count; i++){
		if( peaks[i] > index) peaks[i] = index;
	}

	farthest_peak_index = index;

	return count;

}


void fft(float *input_real, float *input_complex, float thresh, int peak_index)
{
	int i;
	static float tmp[1024];
	static float output[512];
	static int peaks[10];
	int ifftFlag = 0;
	int doBitReverse = 1;
	int count;


	for(i = 0; i < 512; i++){
		tmp[i] = input_real[i];
	}

	for(i = 0; i < 512; i++){
		tmp[i + 512] = input_complex[i];
	}


	//set up for a 512 blocksize and fft of 1024
	arm_cfft_f32(&arm_cfft_sR_f32_len1024, tmp, ifftFlag, doBitReverse);
	arm_cmplx_mag_f32(tmp, output, 1024);
	count = peak_detect(output, 512, thresh, peaks, peak_index);


}

void window(float *input, int length)
{


}
