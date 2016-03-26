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
		y[i] = cosine_lookup(index);
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

float cosine_lookup(int index){
	static const float lookup[512] =
	{
	1.000000, 0.999924, 0.999698, 0.999320, 0.998791, 0.998111, 0.997280, 0.996298,
	0.995166, 0.993883, 0.992450, 0.990867, 0.989134, 0.987252, 0.985220, 0.983039,
	0.980710, 0.978233, 0.975607, 0.972834, 0.969914, 0.966848, 0.963635, 0.960277,
	0.956773, 0.953125, 0.949332, 0.945396, 0.941317, 0.937096, 0.932733, 0.928229,
	0.923585, 0.918801, 0.913879, 0.908818, 0.903619, 0.898284, 0.892814, 0.887208,
	0.881468, 0.875595, 0.869589, 0.863452, 0.857185, 0.850788, 0.844262, 0.837609,
	0.830829, 0.823923, 0.816893, 0.809739, 0.802463, 0.795066, 0.787548, 0.779911,
	0.772157, 0.764285, 0.756298, 0.748197, 0.739983, 0.731656, 0.723220, 0.714673,
	0.706019, 0.697258, 0.688392, 0.679421, 0.670348, 0.661174, 0.651899, 0.642526,
	0.633056, 0.623490, 0.613830, 0.604077, 0.594232, 0.584298, 0.574276, 0.564166,
	0.553972, 0.543693, 0.533333, 0.522892, 0.512371, 0.501774, 0.491100, 0.480352,
	0.469532, 0.458640, 0.447680, 0.436651, 0.425557, 0.414398, 0.403177, 0.391894,
	0.380552, 0.369153, 0.357698, 0.346189, 0.334628, 0.323016, 0.311355, 0.299647,
	0.287894, 0.276097, 0.264258, 0.252380, 0.240463, 0.228510, 0.216523, 0.204503,
	0.192452, 0.180371, 0.168264, 0.156131, 0.143974, 0.131796, 0.119598, 0.107381,
	0.095149, 0.082902, 0.070642, 0.058372, 0.046093, 0.033807, 0.021516, 0.009222,
	-0.003074, -0.015369, -0.027662, -0.039951, -0.052234, -0.064508, -0.076774, -0.089027,
	-0.101267, -0.113492, -0.125699, -0.137888, -0.150055, -0.162200, -0.174321, -0.186415,
	-0.198481, -0.210517, -0.222521, -0.234491, -0.246426, -0.258324, -0.270183, -0.282001,
	-0.293776, -0.305507, -0.317191, -0.328828, -0.340415, -0.351950, -0.363433, -0.374860,
	-0.386231, -0.397543, -0.408795, -0.419985, -0.431112, -0.442174, -0.453169, -0.464095,
	-0.474951, -0.485735, -0.496446, -0.507082, -0.517641, -0.528122, -0.538523, -0.548843,
	-0.559080, -0.569232, -0.579298, -0.589276, -0.599166, -0.608965, -0.618671, -0.628285,
	-0.637803, -0.647225, -0.656549, -0.665773, -0.674897, -0.683919, -0.692838, -0.701652,
	-0.710360, -0.718960, -0.727452, -0.735833, -0.744104, -0.752262, -0.760306, -0.768235,
	-0.776049, -0.783744, -0.791322, -0.798779, -0.806116, -0.813331, -0.820423, -0.827391,
	-0.834234, -0.840951, -0.847541, -0.854002, -0.860335, -0.866537, -0.872609, -0.878548,
	-0.884355, -0.890028, -0.895566, -0.900969, -0.906236, -0.911365, -0.916357, -0.921211,
	-0.925925, -0.930499, -0.934932, -0.939224, -0.943375, -0.947382, -0.951246, -0.954967,
	-0.958543, -0.961974, -0.965260, -0.968399, -0.971393, -0.974239, -0.976938, -0.979490,
	-0.981893, -0.984148, -0.986255, -0.988212, -0.990019, -0.991677, -0.993185, -0.994543,
	-0.995751, -0.996808, -0.997714, -0.998470, -0.999074, -0.999528, -0.999830, -0.999981,
	-0.999981, -0.999830, -0.999528, -0.999074, -0.998470, -0.997714, -0.996808, -0.995751,
	-0.994543, -0.993185, -0.991677, -0.990019, -0.988212, -0.986255, -0.984148, -0.981893,
	-0.979490, -0.976938, -0.974239, -0.971393, -0.968399, -0.965260, -0.961974, -0.958543,
	-0.954967, -0.951246, -0.947382, -0.943375, -0.939224, -0.934932, -0.930499, -0.925925,
	-0.921211, -0.916357, -0.911365, -0.906236, -0.900969, -0.895566, -0.890028, -0.884355,
	-0.878548, -0.872609, -0.866537, -0.860335, -0.854002, -0.847541, -0.840951, -0.834234,
	-0.827391, -0.820423, -0.813331, -0.806116, -0.798779, -0.791322, -0.783744, -0.776049,
	-0.768235, -0.760306, -0.752262, -0.744104, -0.735833, -0.727452, -0.718960, -0.710360,
	-0.701652, -0.692838, -0.683919, -0.674897, -0.665773, -0.656549, -0.647225, -0.637803,
	-0.628285, -0.618671, -0.608965, -0.599166, -0.589276, -0.579298, -0.569232, -0.559080,
	-0.548843, -0.538523, -0.528122, -0.517641, -0.507082, -0.496446, -0.485735, -0.474951,
	-0.464095, -0.453169, -0.442174, -0.431112, -0.419985, -0.408795, -0.397543, -0.386231,
	-0.374860, -0.363433, -0.351950, -0.340415, -0.328828, -0.317191, -0.305507, -0.293776,
	-0.282001, -0.270183, -0.258324, -0.246426, -0.234491, -0.222521, -0.210517, -0.198481,
	-0.186415, -0.174321, -0.162200, -0.150055, -0.137888, -0.125699, -0.113492, -0.101267,
	-0.089027, -0.076774, -0.064508, -0.052234, -0.039951, -0.027662, -0.015369, -0.003074,
	0.009222, 0.021516, 0.033807, 0.046093, 0.058372, 0.070642, 0.082902, 0.095149,
	0.107381, 0.119598, 0.131796, 0.143974, 0.156131, 0.168264, 0.180371, 0.192452,
	0.204503, 0.216523, 0.228510, 0.240463, 0.252380, 0.264258, 0.276097, 0.287894,
	0.299647, 0.311355, 0.323016, 0.334628, 0.346189, 0.357698, 0.369153, 0.380552,
	0.391894, 0.403177, 0.414398, 0.425557, 0.436651, 0.447680, 0.458640, 0.469532,
	0.480352, 0.491100, 0.501774, 0.512371, 0.522892, 0.533333, 0.543693, 0.553972,
	0.564166, 0.574276, 0.584298, 0.594232, 0.604077, 0.613830, 0.623490, 0.633056,
	0.642526, 0.651899, 0.661174, 0.670348, 0.679421, 0.688392, 0.697258, 0.706019,
	0.714673, 0.723220, 0.731656, 0.739983, 0.748197, 0.756298, 0.764285, 0.772157,
	0.779911, 0.787548, 0.795066, 0.802463, 0.809739, 0.816893, 0.823923, 0.830829,
	0.837609, 0.844262, 0.850788, 0.857185, 0.863452, 0.869589, 0.875595, 0.881468,
	0.887208, 0.892814, 0.898284, 0.903619, 0.908818, 0.913879, 0.918801, 0.923585,
	0.928229, 0.932733, 0.937096, 0.941317, 0.945396, 0.949332, 0.953125, 0.956773,
	0.960277, 0.963635, 0.966848, 0.969914, 0.972834, 0.975607, 0.978233, 0.980710,
	0.983039, 0.985220, 0.987252, 0.989134, 0.990867, 0.992450, 0.993883, 0.995166,
	0.996298, 0.997280, 0.998111, 0.998791, 0.999320, 0.999698, 0.999924, 1.000000
	};

	return lookup[index]
}
