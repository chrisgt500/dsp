/*!
 * @file fsk_rt.c
 *
 * @brief
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary
 * @author Forrest Smith
 * @author Sean Turner
 *
 * @date April 23, 2016
 *
 */
#include <math.h>
#include "arm_math.h"
#include "arm_const_structs.h"
#include "ece486_fft.h"
#include "ece486.h"

void peak_detect(float *data, float thresh, int farthest_peak_index)
{
	int i, index;
	int count = 0;
	int peaks[10] = {0};//detects 10 peaks


	for (i = 1; i < FFTSAMPLES-1; i++) {
		if ((data[i] >= thresh) && (data[i-1] < data[i]) && (data[i+1] < data[i])){
			peaks[count++] = i+1; //can probably simplify this
		}

	}

	for(i = 1; i < count; i++){
		if( peaks[i] > index) index = peaks[i];
	}

	farthest_peak_index = index;
}


void fft(float *input_real, float *input_complex, float thresh, int *peak_index)
{
	int i;
	static float tmp[FFTSAMPLES*2];
	static float output[FFTSAMPLES];
	int ifftFlag = 0;
	int doBitReverse = 1;


	for(i = 0; i < FFTSAMPLES; i++){
		tmp[i] = input_real[i];
	}

	for(i = 0; i < FFTSAMPLES; i++){
		tmp[i + FFTSAMPLES] = input_complex[i];
	}


	//set up for a 512 blocksize and fft of 1024
	arm_cfft_f32(&arm_cfft_sR_f32_len1024, tmp, ifftFlag, doBitReverse);
	arm_cmplx_mag_f32(tmp, output, FFTSAMPLES*2);
	peak_detect(output, thresh, *peak_index);



}

//multiply by 512 samples of a half period of sine, as a window function
void window(float *input)
{
	int i;

	static float lookup_table[512] = {0.000000, 0.006148, 0.012296, 0.018443, 0.024589, 0.030735, 0.036879, 0.043022, 0.049164, 0.055303,
0.061441, 0.067576, 0.073708, 0.079838, 0.085965, 0.092088, 0.098208, 0.104325, 0.110437, 0.116545,
0.122649, 0.128748, 0.134842, 0.140932, 0.147016, 0.153094, 0.159166, 0.165233, 0.171293, 0.177347,
0.183394, 0.189434, 0.195467, 0.201493, 0.207511, 0.213521, 0.219523, 0.225517, 0.231502, 0.237479,
0.243446, 0.249404, 0.255353, 0.261293, 0.267222, 0.273141, 0.279050, 0.284949, 0.290836, 0.296713,
0.302578, 0.308432, 0.314275, 0.320105, 0.325923, 0.331729, 0.337523, 0.343304, 0.349071, 0.354826,
0.360567, 0.366295, 0.372008, 0.377708, 0.383393, 0.389064, 0.394720, 0.400362, 0.405988, 0.411598,
0.417194, 0.422773, 0.428336, 0.433884, 0.439415, 0.444929, 0.450426, 0.455907, 0.461370, 0.466816,
0.472244, 0.477654, 0.483046, 0.488420, 0.493776, 0.499112, 0.504430, 0.509729, 0.515009, 0.520269,
0.525509, 0.530730, 0.535931, 0.541111, 0.546271, 0.551410, 0.556528, 0.561626, 0.566702, 0.571756,
0.576790, 0.581801, 0.586790, 0.591757, 0.596702, 0.601624, 0.606524, 0.611400, 0.616253, 0.621084,
0.625890, 0.630673, 0.635432, 0.640167, 0.644878, 0.649565, 0.654227, 0.658864, 0.663477, 0.668064,
0.672626, 0.677163, 0.681674, 0.686159, 0.690618, 0.695051, 0.699458, 0.703839, 0.708193, 0.712520,
0.716820, 0.721093, 0.725339, 0.729558, 0.733748, 0.737912, 0.742047, 0.746154, 0.750233, 0.754284,
0.758306, 0.762299, 0.766264, 0.770200, 0.774106, 0.777984, 0.781831, 0.785650, 0.789439, 0.793197,
0.796926, 0.800625, 0.804293, 0.807932, 0.811539, 0.815116, 0.818662, 0.822177, 0.825661, 0.829114,
0.832535, 0.835925, 0.839284, 0.842611, 0.845905, 0.849168, 0.852399, 0.855598, 0.858764, 0.861898,
0.864999, 0.868067, 0.871103, 0.874106, 0.877076, 0.880012, 0.882916, 0.885785, 0.888622, 0.891425,
0.894194, 0.896929, 0.899631, 0.902298, 0.904932, 0.907531, 0.910096, 0.912626, 0.915122, 0.917584,
0.920010, 0.922402, 0.924759, 0.927081, 0.929369, 0.931620, 0.933837, 0.936019, 0.938165, 0.940275,
0.942350, 0.944390, 0.946394, 0.948362, 0.950294, 0.952190, 0.954050, 0.955874, 0.957662, 0.959414,
0.961130, 0.962809, 0.964452, 0.966058, 0.967628, 0.969162, 0.970658, 0.972118, 0.973541, 0.974928,
0.976278, 0.977590, 0.978866, 0.980105, 0.981306, 0.982471, 0.983599, 0.984689, 0.985742, 0.986758,
0.987736, 0.988678, 0.989581, 0.990448, 0.991277, 0.992068, 0.992822, 0.993539, 0.994218, 0.994859,
0.995463, 0.996029, 0.996558, 0.997049, 0.997502, 0.997917, 0.998295, 0.998635, 0.998937, 0.999202,
0.999428, 0.999617, 0.999769, 0.999882, 0.999957, 0.999995, 0.999995, 0.999957, 0.999882, 0.999769,
0.999617, 0.999428, 0.999202, 0.998937, 0.998635, 0.998295, 0.997917, 0.997502, 0.997049, 0.996558,
0.996029, 0.995463, 0.994859, 0.994218, 0.993539, 0.992822, 0.992068, 0.991277, 0.990448, 0.989581,
0.988678, 0.987736, 0.986758, 0.985742, 0.984689, 0.983599, 0.982471, 0.981306, 0.980105, 0.978866,
0.977590, 0.976278, 0.974928, 0.973541, 0.972118, 0.970658, 0.969162, 0.967628, 0.966058, 0.964452,
0.962809, 0.961130, 0.959414, 0.957662, 0.955874, 0.954050, 0.952190, 0.950294, 0.948362, 0.946394,
0.944390, 0.942350, 0.940275, 0.938165, 0.936019, 0.933837, 0.931620, 0.929369, 0.927081, 0.924759,
0.922402, 0.920010, 0.917584, 0.915122, 0.912626, 0.910096, 0.907531, 0.904932, 0.902298, 0.899631,
0.896929, 0.894194, 0.891425, 0.888622, 0.885785, 0.882916, 0.880012, 0.877076, 0.874106, 0.871103,
0.868067, 0.864999, 0.861898, 0.858764, 0.855598, 0.852399, 0.849168, 0.845905, 0.842611, 0.839284,
0.835925, 0.832535, 0.829114, 0.825661, 0.822177, 0.818662, 0.815116, 0.811539, 0.807932, 0.804293,
0.800625, 0.796926, 0.793197, 0.789439, 0.785650, 0.781831, 0.777984, 0.774106, 0.770200, 0.766264,
0.762299, 0.758306, 0.754284, 0.750233, 0.746154, 0.742047, 0.737912, 0.733748, 0.729558, 0.725339,
0.721093, 0.716820, 0.712520, 0.708193, 0.703839, 0.699458, 0.695051, 0.690618, 0.686159, 0.681674,
0.677163, 0.672626, 0.668064, 0.663477, 0.658864, 0.654227, 0.649565, 0.644878, 0.640167, 0.635432,
0.630673, 0.625890, 0.621084, 0.616253, 0.611400, 0.606524, 0.601624, 0.596702, 0.591757, 0.586790,
0.581801, 0.576790, 0.571756, 0.566702, 0.561626, 0.556528, 0.551410, 0.546271, 0.541111, 0.535931,
0.530730, 0.525509, 0.520269, 0.515009, 0.509729, 0.504430, 0.499112, 0.493776, 0.488420, 0.483046,
0.477654, 0.472244, 0.466816, 0.461370, 0.455907, 0.450426, 0.444929, 0.439415, 0.433884, 0.428336,
0.422773, 0.417194, 0.411598, 0.405988, 0.400362, 0.394720, 0.389064, 0.383393, 0.377708, 0.372008,
0.366295, 0.360567, 0.354826, 0.349071, 0.343304, 0.337523, 0.331729, 0.325923, 0.320105, 0.314275,
0.308432, 0.302578, 0.296713, 0.290836, 0.284949, 0.279050, 0.273141, 0.267222, 0.261293, 0.255353,
0.249404, 0.243446, 0.237479, 0.231502, 0.225517, 0.219523, 0.213521, 0.207511, 0.201493, 0.195467,
0.189434, 0.183394, 0.177347, 0.171293, 0.165233, 0.159166, 0.153094, 0.147016, 0.140932, 0.134842,
0.128748, 0.122649, 0.116545, 0.110437, 0.104325, 0.098208, 0.092088, 0.085965, 0.079838, 0.073708,
0.067576, 0.061441, 0.055303, 0.049164, 0.043022, 0.036879, 0.030735, 0.024589, 0.018443, 0.012296
};

	for(i = 0; i < FFTSAMPLES; i++){
		input[i] *= lookup_table[i];
	}
}

void velocity_conversion_display(int peak_index)
{
	char lcd_str[8];
	float scale = 1241.379;
	float normalized_freq = peak_index/(FFTSAMPLES*2);

	sprintf(lcd_str, "%.3f", scale * normalized_freq);
	BSP_LCD_GLASS_DisplayString((uint8_t *)lcd_str);


}
