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
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "arm_math.h"
#include "arm_const_structs.h"
#include "ece486_fft.h"
#include "ece486.h"
#include "init486.h"

int peak_detect(float *data, float thresh, int button_flag)
{
	int i;


	// This assumes that 0-.5 is positive freqs and .5 - 1 is negative freqs
	if(button_flag == 1){
		for (i = (FFTSAMPLES/3)-1; i > 2 ; i--) {
			if ((data[i] >= thresh) && (data[i-1] < data[i]) && (data[i+1] < data[i])){
				return i;
			}
		}
	}

	if(button_flag == -1){
		for (i = FFTSAMPLES/3 + 1; i < (FFTSAMPLES)-1; i++) {
			if ((data[i] >= thresh) && (data[i-1] < data[i]) && (data[i+1] < data[i])){
				return i;
			}
		}
	}

	return -1;
}


void fft(float *buffer, float thresh, float *peak_index, int button_flag)
{
	int i;
	static float output[FFTSAMPLES*2] = {0};
	int ifftFlag = 0;
	int doBitReverse = 1;
	float maxvalue = 0 ;
	uint32_t index = 0;

	window(buffer);
	arm_cfft_f32(&arm_cfft_sR_f32_len2048, buffer, ifftFlag, doBitReverse);

	arm_cmplx_mag_f32(buffer, output, FFTSAMPLES*2);


	for ( i = 0 ; i < FFTSAMPLES*2; i++){
		printf("%f,",output[i]);
	}

	arm_max_f32(output, FFTSAMPLES, &maxvalue, &index );

	*peak_index = peak_detect(output, thresh, button_flag);
}

//multiply by 1024 samples of a half period of sine, as a window function
void window(float *input)
{
	int i;

	float lookup_table[1024] =
	{
		0.002339, 0.002487, 0.002640, 0.002797, 0.002959, 0.003126, 0.003296, 0.003472, 0.003653, 0.003838,
		0.004028, 0.004223, 0.004424, 0.004629, 0.004840, 0.005056, 0.005277, 0.005504, 0.005736, 0.005974,
		0.006218, 0.006467, 0.006722, 0.006983, 0.007250, 0.007523, 0.007802, 0.008087, 0.008379, 0.008677,
		0.008981, 0.009292, 0.009610, 0.009934, 0.010265, 0.010603, 0.010947, 0.011299, 0.011658, 0.012024,
		0.012397, 0.012777, 0.013165, 0.013560, 0.013963, 0.014373, 0.014792, 0.015218, 0.015651, 0.016093,
		0.016543, 0.017001, 0.017467, 0.017942, 0.018425, 0.018916, 0.019416, 0.019924, 0.020441, 0.020967,
		0.021502, 0.022045, 0.022598, 0.023160, 0.023731, 0.024311, 0.024901, 0.025500, 0.026108, 0.026726,
		0.027354, 0.027991, 0.028639, 0.029296, 0.029963, 0.030640, 0.031328, 0.032025, 0.032733, 0.033452,
		0.034181, 0.034920, 0.035670, 0.036430, 0.037202, 0.037984, 0.038777, 0.039581, 0.040397, 0.041223,
		0.042061, 0.042910, 0.043770, 0.044642, 0.045525, 0.046420, 0.047326, 0.048245, 0.049175, 0.050117,
		0.051071, 0.052037, 0.053015, 0.054005, 0.055007, 0.056022, 0.057049, 0.058089, 0.059141, 0.060206,
		0.061283, 0.062373, 0.063476, 0.064591, 0.065720, 0.066861, 0.068016, 0.069183, 0.070364, 0.071558,
		0.072765, 0.073985, 0.075219, 0.076466, 0.077727, 0.079001, 0.080288, 0.081590, 0.082905, 0.084234,
		0.085576, 0.086933, 0.088303, 0.089687, 0.091086, 0.092498, 0.093924, 0.095365, 0.096819, 0.098288,
		0.099771, 0.101268, 0.102780, 0.104306, 0.105846, 0.107401, 0.108970, 0.110554, 0.112153, 0.113765,
		0.115393, 0.117035, 0.118692, 0.120363, 0.122049, 0.123750, 0.125466, 0.127196, 0.128941, 0.130701,
		0.132476, 0.134266, 0.136070, 0.137889, 0.139724, 0.141573, 0.143437, 0.145316, 0.147210, 0.149119,
		0.151043, 0.152982, 0.154936, 0.156905, 0.158888, 0.160887, 0.162901, 0.164930, 0.166973, 0.169032,
		0.171106, 0.173194, 0.175297, 0.177416, 0.179549, 0.181697, 0.183860, 0.186038, 0.188231, 0.190439,
		0.192661, 0.194898, 0.197150, 0.199417, 0.201698, 0.203994, 0.206305, 0.208630, 0.210970, 0.213325,
		0.215694, 0.218077, 0.220475, 0.222887, 0.225314, 0.227755, 0.230210, 0.232680, 0.235163, 0.237661,
		0.240173, 0.242699, 0.245239, 0.247793, 0.250360, 0.252942, 0.255537, 0.258146, 0.260769, 0.263405,
		0.266054, 0.268717, 0.271394, 0.274083, 0.276786, 0.279502, 0.282231, 0.284973, 0.287728, 0.290496,
		0.293277, 0.296070, 0.298876, 0.301694, 0.304525, 0.307368, 0.310223, 0.313090, 0.315970, 0.318861,
		0.321765, 0.324680, 0.327606, 0.330544, 0.333494, 0.336455, 0.339427, 0.342411, 0.345405, 0.348410,
		0.351426, 0.354453, 0.357490, 0.360538, 0.363596, 0.366665, 0.369743, 0.372832, 0.375930, 0.379038,
		0.382156, 0.385283, 0.388419, 0.391565, 0.394720, 0.397883, 0.401056, 0.404237, 0.407427, 0.410625,
		0.413831, 0.417046, 0.420268, 0.423499, 0.426737, 0.429982, 0.433235, 0.436495, 0.439762, 0.443037,
		0.446318, 0.449605, 0.452899, 0.456200, 0.459506, 0.462819, 0.466137, 0.469461, 0.472791, 0.476126,
		0.479466, 0.482811, 0.486161, 0.489515, 0.492874, 0.496238, 0.499606, 0.502977, 0.506353, 0.509732,
		0.513114, 0.516500, 0.519889, 0.523281, 0.526675, 0.530072, 0.533472, 0.536874, 0.540277, 0.543683,
		0.547090, 0.550499, 0.553909, 0.557320, 0.560732, 0.564145, 0.567558, 0.570971, 0.574385, 0.577798,
		0.581211, 0.584624, 0.588036, 0.591448, 0.594858, 0.598267, 0.601674, 0.605080, 0.608484, 0.611887,
		0.615286, 0.618684, 0.622078, 0.625470, 0.628859, 0.632245, 0.635627, 0.639005, 0.642380, 0.645751,
		0.649117, 0.652479, 0.655836, 0.659188, 0.662535, 0.665877, 0.669213, 0.672544, 0.675869, 0.679188,
		0.682500, 0.685806, 0.689105, 0.692397, 0.695681, 0.698959, 0.702229, 0.705491, 0.708745, 0.711991,
		0.715229, 0.718457, 0.721677, 0.724889, 0.728090, 0.731283, 0.734465, 0.737638, 0.740801, 0.743953,
		0.747095, 0.750226, 0.753347, 0.756456, 0.759554, 0.762640, 0.765715, 0.768778, 0.771828, 0.774867,
		0.777892, 0.780905, 0.783906, 0.786892, 0.789866, 0.792826, 0.795772, 0.798704, 0.801623, 0.804526,
		0.807416, 0.810290, 0.813150, 0.815994, 0.818823, 0.821637, 0.824435, 0.827217, 0.829982, 0.832732,
		0.835465, 0.838181, 0.840881, 0.843563, 0.846228, 0.848876, 0.851506, 0.854119, 0.856713, 0.859289,
		0.861847, 0.864386, 0.866907, 0.869409, 0.871891, 0.874355, 0.876799, 0.879223, 0.881628, 0.884013,
		0.886377, 0.888722, 0.891045, 0.893349, 0.895631, 0.897893, 0.900134, 0.902353, 0.904551, 0.906727,
		0.908882, 0.911015, 0.913125, 0.915214, 0.917280, 0.919324, 0.921345, 0.923343, 0.925318, 0.927270,
		0.929200, 0.931105, 0.932987, 0.934846, 0.936681, 0.938492, 0.940278, 0.942041, 0.943780, 0.945494,
		0.947183, 0.948848, 0.950488, 0.952103, 0.953693, 0.955258, 0.956797, 0.958311, 0.959800, 0.961263,
		0.962701, 0.964112, 0.965498, 0.966858, 0.968191, 0.969498, 0.970779, 0.972034, 0.973262, 0.974464,
		0.975638, 0.976786, 0.977908, 0.979002, 0.980069, 0.981109, 0.982122, 0.983108, 0.984066, 0.984997,
		0.985900, 0.986776, 0.987624, 0.988445, 0.989238, 0.990003, 0.990740, 0.991450, 0.992131, 0.992784,
		0.993410, 0.994007, 0.994576, 0.995117, 0.995629, 0.996114, 0.996570, 0.996998, 0.997397, 0.997768,
		0.998111, 0.998425, 0.998710, 0.998967, 0.999196, 0.999396, 0.999568, 0.999710, 0.999825, 0.999911,
		0.999968, 0.999996, 0.999996, 0.999968, 0.999911, 0.999825, 0.999710, 0.999568, 0.999396, 0.999196,
		0.998967, 0.998710, 0.998425, 0.998111, 0.997768, 0.997397, 0.996998, 0.996570, 0.996114, 0.995629,
		0.995117, 0.994576, 0.994007, 0.993410, 0.992784, 0.992131, 0.991450, 0.990740, 0.990003, 0.989238,
		0.988445, 0.987624, 0.986776, 0.985900, 0.984997, 0.984066, 0.983108, 0.982122, 0.981109, 0.980069,
		0.979002, 0.977908, 0.976786, 0.975638, 0.974464, 0.973262, 0.972034, 0.970779, 0.969498, 0.968191,
		0.966858, 0.965498, 0.964112, 0.962701, 0.961263, 0.959800, 0.958311, 0.956797, 0.955258, 0.953693,
		0.952103, 0.950488, 0.948848, 0.947183, 0.945494, 0.943780, 0.942041, 0.940278, 0.938492, 0.936681,
		0.934846, 0.932987, 0.931105, 0.929200, 0.927270, 0.925318, 0.923343, 0.921345, 0.919324, 0.917280,
		0.915214, 0.913125, 0.911015, 0.908882, 0.906727, 0.904551, 0.902353, 0.900134, 0.897893, 0.895631,
		0.893349, 0.891045, 0.888722, 0.886377, 0.884013, 0.881628, 0.879223, 0.876799, 0.874355, 0.871891,
		0.869409, 0.866907, 0.864386, 0.861847, 0.859289, 0.856713, 0.854119, 0.851506, 0.848876, 0.846228,
		0.843563, 0.840881, 0.838181, 0.835465, 0.832732, 0.829982, 0.827217, 0.824435, 0.821637, 0.818823,
		0.815994, 0.813150, 0.810290, 0.807416, 0.804526, 0.801623, 0.798704, 0.795772, 0.792826, 0.789866,
		0.786892, 0.783906, 0.780905, 0.777892, 0.774867, 0.771828, 0.768778, 0.765715, 0.762640, 0.759554,
		0.756456, 0.753347, 0.750226, 0.747095, 0.743953, 0.740801, 0.737638, 0.734465, 0.731283, 0.728090,
		0.724889, 0.721677, 0.718457, 0.715229, 0.711991, 0.708745, 0.705491, 0.702229, 0.698959, 0.695681,
		0.692397, 0.689105, 0.685806, 0.682500, 0.679188, 0.675869, 0.672544, 0.669213, 0.665877, 0.662535,
		0.659188, 0.655836, 0.652479, 0.649117, 0.645751, 0.642380, 0.639005, 0.635627, 0.632245, 0.628859,
		0.625470, 0.622078, 0.618684, 0.615286, 0.611887, 0.608484, 0.605080, 0.601674, 0.598267, 0.594858,
		0.591448, 0.588036, 0.584624, 0.581211, 0.577798, 0.574385, 0.570971, 0.567558, 0.564145, 0.560732,
		0.557320, 0.553909, 0.550499, 0.547090, 0.543683, 0.540277, 0.536874, 0.533472, 0.530072, 0.526675,
		0.523281, 0.519889, 0.516500, 0.513114, 0.509732, 0.506353, 0.502977, 0.499606, 0.496238, 0.492874,
		0.489515, 0.486161, 0.482811, 0.479466, 0.476126, 0.472791, 0.469461, 0.466137, 0.462819, 0.459506,
		0.456200, 0.452899, 0.449605, 0.446318, 0.443037, 0.439762, 0.436495, 0.433235, 0.429982, 0.426737,
		0.423499, 0.420268, 0.417046, 0.413831, 0.410625, 0.407427, 0.404237, 0.401056, 0.397883, 0.394720,
		0.391565, 0.388419, 0.385283, 0.382156, 0.379038, 0.375930, 0.372832, 0.369743, 0.366665, 0.363596,
		0.360538, 0.357490, 0.354453, 0.351426, 0.348410, 0.345405, 0.342411, 0.339427, 0.336455, 0.333494,
		0.330544, 0.327606, 0.324680, 0.321765, 0.318861, 0.315970, 0.313090, 0.310223, 0.307368, 0.304525,
		0.301694, 0.298876, 0.296070, 0.293277, 0.290496, 0.287728, 0.284973, 0.282231, 0.279502, 0.276786,
		0.274083, 0.271394, 0.268717, 0.266054, 0.263405, 0.260769, 0.258146, 0.255537, 0.252942, 0.250360,
		0.247793, 0.245239, 0.242699, 0.240173, 0.237661, 0.235163, 0.232680, 0.230210, 0.227755, 0.225314,
		0.222887, 0.220475, 0.218077, 0.215694, 0.213325, 0.210970, 0.208630, 0.206305, 0.203994, 0.201698,
		0.199417, 0.197150, 0.194898, 0.192661, 0.190439, 0.188231, 0.186038, 0.183860, 0.181697, 0.179549,
		0.177416, 0.175297, 0.173194, 0.171106, 0.169032, 0.166973, 0.164930, 0.162901, 0.160887, 0.158888,
		0.156905, 0.154936, 0.152982, 0.151043, 0.149119, 0.147210, 0.145316, 0.143437, 0.141573, 0.139724,
		0.137889, 0.136070, 0.134266, 0.132476, 0.130701, 0.128941, 0.127196, 0.125466, 0.123750, 0.122049,
		0.120363, 0.118692, 0.117035, 0.115393, 0.113765, 0.112153, 0.110554, 0.108970, 0.107401, 0.105846,
		0.104306, 0.102780, 0.101268, 0.099771, 0.098288, 0.096819, 0.095365, 0.093924, 0.092498, 0.091086,
		0.089687, 0.088303, 0.086933, 0.085576, 0.084234, 0.082905, 0.081590, 0.080288, 0.079001, 0.077727,
		0.076466, 0.075219, 0.073985, 0.072765, 0.071558, 0.070364, 0.069183, 0.068016, 0.066861, 0.065720,
		0.064591, 0.063476, 0.062373, 0.061283, 0.060206, 0.059141, 0.058089, 0.057049, 0.056022, 0.055007,
		0.054005, 0.053015, 0.052037, 0.051071, 0.050117, 0.049175, 0.048245, 0.047326, 0.046420, 0.045525,
		0.044642, 0.043770, 0.042910, 0.042061, 0.041223, 0.040397, 0.039581, 0.038777, 0.037984, 0.037202,
		0.036430, 0.035670, 0.034920, 0.034181, 0.033452, 0.032733, 0.032025, 0.031328, 0.030640, 0.029963,
		0.029296, 0.028639, 0.027991, 0.027354, 0.026726, 0.026108, 0.025500, 0.024901, 0.024311, 0.023731,
		0.023160, 0.022598, 0.022045, 0.021502, 0.020967, 0.020441, 0.019924, 0.019416, 0.018916, 0.018425,
		0.017942, 0.017467, 0.017001, 0.016543, 0.016093, 0.015651, 0.015218, 0.014792, 0.014373, 0.013963,
		0.013560, 0.013165, 0.012777, 0.012397, 0.012024, 0.011658, 0.011299, 0.010947, 0.010603, 0.010265,
		0.009934, 0.009610, 0.009292, 0.008981, 0.008677, 0.008379, 0.008087, 0.007802, 0.007523, 0.007250,
		0.006983, 0.006722, 0.006467, 0.006218, 0.005974, 0.005736, 0.005504, 0.005277, 0.005056, 0.004840,
		0.004629, 0.004424, 0.004223, 0.004028, 0.003838, 0.003653, 0.003472, 0.003296, 0.003126, 0.002959
		};

	for(i = 0; i < FFTSAMPLES; i++){
		input[2*i] *= lookup_table[i];
		input[2*i+1] *= lookup_table[i];
	}
}

void velocity_conversion_display(float *peak_index, int button_flag)
{
	clear_screen();
	if( *peak_index == -1){
		BSP_LCD_GLASS_DisplayString((uint8_t *)"No");
		return;
	}
	char lcd_str[8] = {0};
	float scale = .0758;
	//float normalized_freq = (*peak_index)/(FFTSAMPLES*2);
	if( button_flag == 1) sprintf(lcd_str, "-%.1f", *peak_index*scale);
	if( button_flag == -1) sprintf(lcd_str, "%.1f", *peak_index/1024*150/2);
	BSP_LCD_GLASS_DisplayString((uint8_t *)lcd_str);

}

void clear_screen(void)
{
	BSP_LCD_GLASS_DisplayString((uint8_t *)"        ");
}
