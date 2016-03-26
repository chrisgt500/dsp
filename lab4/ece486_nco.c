#include "ece486_nco.h"
#include "math.h"


NCO_T *init_nco(float f0, float theta){
	NCO_T *s = malloc(sizeof(NCO_T));
	s->f0 = f0;
	s->theta_const = theta;
	s->theta_temp = 0.0;
	return s;
}

void nco_get_samples(NCO_T *s, float *y, int n_samples){
	float index;
	int i;

	for ( i = 0; i < n_samples; i ++){
		s->theta_temp = s->theta_temp + 2*pi*(s->f0);
		index = [(s->theta_temp)+(s->theta_const)]*[512/(2*pi)];
		index = rint(index)%512;
		y[i] = cos(index);
	}
}

void nco_set_frequency(NCO_T *s, float f_new){
    s->f0 = f_new;
}

void nco_set_phase(NCO_T *s, float theta){
    s->theta = theta;
}

void destroy_nco(NCO_T *s){
    free(s);
	s = NULL;
}

float cosine(int index){
	static const float lookup[128] =
	{
		1.000000, 0.999924, 0.999694, 0.999312, 0.998776, 0.998088, 0.997248, 0.996254,
		0.995109, 0.993811, 0.992361, 0.990759, 0.989006, 0.987101, 0.985045, 0.982839,
		0.980482, 0.977976, 0.975320, 0.972514, 0.969560, 0.966457, 0.963207, 0.959809,
		0.956265, 0.952574, 0.948737, 0.944755, 0.940629, 0.936359, 0.931946, 0.927390,
		0.922692, 0.917853, 0.912873, 0.907754, 0.902497, 0.897101, 0.891567, 0.885898,
		0.880093, 0.874153, 0.868079, 0.861873, 0.855535, 0.849066, 0.842467, 0.835739,
		0.828884, 0.821901, 0.814793, 0.807561, 0.800204, 0.792725, 0.785125, 0.777405,
		0.769566, 0.761610, 0.753536, 0.745348, 0.737045, 0.728630, 0.720103, 0.711466,
		0.702720, 0.693867, 0.684908, 0.675843, 0.666676, 0.657406, 0.648036, 0.638567,
		0.629000, 0.619337, 0.609579, 0.599728, 0.589785, 0.579752, 0.569630, 0.559421,
		0.549126, 0.538748, 0.528287, 0.517745, 0.507124, 0.496425, 0.485651, 0.474802,
		0.463881, 0.452888, 0.441826, 0.430697, 0.419502, 0.408243, 0.396921, 0.385538,
		0.374097, 0.362598, 0.351044, 0.339436, 0.327776, 0.316066, 0.304308, 0.292503,
		0.280654, 0.268761, 0.256827, 0.244854, 0.232844, 0.220798, 0.208718, 0.196606,
		0.184465, 0.172295, 0.160098, 0.147877, 0.135634, 0.123370, 0.111087, 0.098786,
		0.086471, 0.074143, 0.061803, 0.049454, 0.037097, 0.024734, 0.012368, 0.000000
	};
	if (value < 127) return lookup[value];
	else if (value >= 127 && value < 255) return -lookup[254-value];
	else if (value >= 255 && value < 382) return -lookup[value-254];
	else if (value >= 384) return lookup[511-value];
}
