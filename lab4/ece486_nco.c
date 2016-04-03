
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "ece486_nco.h"


NCO_T * init_nco(float f0, float theta){
	NCO_T *s = (NCO_T *)malloc(sizeof(NCO_T));
	if(s == NULL) {
		printf("Could not allocate NCO_T struct");
		exit(0);
	}
	s->f0 = f0;
	s->theta_const = theta;
	s->theta_temp = 0.0;
	return s;
}

void nco_get_samples(NCO_T *s, float *y, int n_samples){
	float index = 0.0;
	int round_index = 0;
	int i;


	for (i = 0; i < n_samples; i ++){
		s->theta_temp += 2*M_PI*(s->f0);
		index = (s->theta_temp)+(s->theta_const);
		index = index*(512/(2*PI));
		round_index = (int)(index);
		round_index = round_index%512;
		y[i] = cosine_lookup(round_index);
	}
}

void nco_set_frequency(NCO_T *s, float f_new){
	s->f0 = f_new;
}

void nco_set_phase(NCO_T *s, float theta){
  s->theta_const = theta;
}

void destroy_nco(NCO_T *s){
  free(s);
	s = NULL;
}

float cosine_lookup(int index){
	static const float lookup[512] =
	{
	1.000000, 0.999925, 0.999699, 0.999322, 0.998795, 0.998118, 0.997290, 0.996313,
	0.995185, 0.993907, 0.992480, 0.990903, 0.989177, 0.987301, 0.985278, 0.983105,
	0.980785, 0.978317, 0.975702, 0.972940, 0.970031, 0.966976, 0.963776, 0.960431,
	0.956940, 0.953306, 0.949528, 0.945607, 0.941544, 0.937339, 0.932993, 0.928506,
	0.923880, 0.919114, 0.914210, 0.909168, 0.903989, 0.898674, 0.893224, 0.887640,
	0.881921, 0.876070, 0.870087, 0.863973, 0.857729, 0.851355, 0.844854, 0.838225,
	0.831470, 0.824589, 0.817585, 0.810457, 0.803208, 0.795837, 0.788346, 0.780737,
	0.773010, 0.765167, 0.757209, 0.749136, 0.740951, 0.732654, 0.724247, 0.715731,
	0.707107, 0.698376, 0.689541, 0.680601, 0.671559, 0.662416, 0.653173, 0.643832,
	0.634393, 0.624859, 0.615232, 0.605511, 0.595699, 0.585798, 0.575808, 0.565732,
	0.555570, 0.545325, 0.534998, 0.524590, 0.514103, 0.503538, 0.492898, 0.482184,
	0.471397, 0.460539, 0.449611, 0.438616, 0.427555, 0.416430, 0.405241, 0.393992,
	0.382683, 0.371317, 0.359895, 0.348419, 0.336890, 0.325310, 0.313682, 0.302006,
	0.290285, 0.278520, 0.266713, 0.254866, 0.242980, 0.231058, 0.219101, 0.207111,
	0.195090, 0.183040, 0.170962, 0.158858, 0.146730, 0.134581, 0.122411, 0.110222,
	0.098017, 0.085797, 0.073565, 0.061321, 0.049068, 0.036807, 0.024541, 0.012272,
	0.000000, -0.012272, -0.024541, -0.036807, -0.049068, -0.061321, -0.073565, -0.085797,
	-0.098017, -0.110222, -0.122411, -0.134581, -0.146730, -0.158858, -0.170962, -0.183040,
	-0.195090, -0.207111, -0.219101, -0.231058, -0.242980, -0.254866, -0.266713, -0.278520,
	-0.290285, -0.302006, -0.313682, -0.325310, -0.336890, -0.348419, -0.359895, -0.371317,
	-0.382683, -0.393992, -0.405241, -0.416430, -0.427555, -0.438616, -0.449611, -0.460539,
	-0.471397, -0.482184, -0.492898, -0.503538, -0.514103, -0.524590, -0.534998, -0.545325,
	-0.555570, -0.565732, -0.575808, -0.585798, -0.595699, -0.605511, -0.615232, -0.624859,
	-0.634393, -0.643832, -0.653173, -0.662416, -0.671559, -0.680601, -0.689541, -0.698376,
	-0.707107, -0.715731, -0.724247, -0.732654, -0.740951, -0.749136, -0.757209, -0.765167,
	-0.773010, -0.780737, -0.788346, -0.795837, -0.803208, -0.810457, -0.817585, -0.824589,
	-0.831470, -0.838225, -0.844854, -0.851355, -0.857729, -0.863973, -0.870087, -0.876070,
	-0.881921, -0.887640, -0.893224, -0.898674, -0.903989, -0.909168, -0.914210, -0.919114,
	-0.923880, -0.928506, -0.932993, -0.937339, -0.941544, -0.945607, -0.949528, -0.953306,
	-0.956940, -0.960431, -0.963776, -0.966976, -0.970031, -0.972940, -0.975702, -0.978317,
	-0.980785, -0.983105, -0.985278, -0.987301, -0.989177, -0.990903, -0.992480, -0.993907,
	-0.995185, -0.996313, -0.997290, -0.998118, -0.998795, -0.999322, -0.999699, -0.999925,
	-1.000000, -0.999925, -0.999699, -0.999322, -0.998795, -0.998118, -0.997290, -0.996313,
	-0.995185, -0.993907, -0.992480, -0.990903, -0.989177, -0.987301, -0.985278, -0.983105,
	-0.980785, -0.978317, -0.975702, -0.972940, -0.970031, -0.966976, -0.963776, -0.960431,
	-0.956940, -0.953306, -0.949528, -0.945607, -0.941544, -0.937339, -0.932993, -0.928506,
	-0.923880, -0.919114, -0.914210, -0.909168, -0.903989, -0.898674, -0.893224, -0.887640,
	-0.881921, -0.876070, -0.870087, -0.863973, -0.857729, -0.851355, -0.844854, -0.838225,
	-0.831470, -0.824589, -0.817585, -0.810457, -0.803208, -0.795837, -0.788346, -0.780737,
	-0.773010, -0.765167, -0.757209, -0.749136, -0.740951, -0.732654, -0.724247, -0.715731,
	-0.707107, -0.698376, -0.689541, -0.680601, -0.671559, -0.662416, -0.653173, -0.643832,
	-0.634393, -0.624859, -0.615232, -0.605511, -0.595699, -0.585798, -0.575808, -0.565732,
	-0.555570, -0.545325, -0.534998, -0.524590, -0.514103, -0.503538, -0.492898, -0.482184,
	-0.471397, -0.460539, -0.449611, -0.438616, -0.427555, -0.416430, -0.405241, -0.393992,
	-0.382683, -0.371317, -0.359895, -0.348419, -0.336890, -0.325310, -0.313682, -0.302006,
	-0.290285, -0.278520, -0.266713, -0.254866, -0.242980, -0.231058, -0.219101, -0.207111,
	-0.195090, -0.183040, -0.170962, -0.158858, -0.146730, -0.134581, -0.122411, -0.110222,
	-0.098017, -0.085797, -0.073565, -0.061321, -0.049068, -0.036807, -0.024541, -0.012272,
	-0.000000, 0.012272, 0.024541, 0.036807, 0.049068, 0.061321, 0.073565, 0.085797,
	0.098017, 0.110222, 0.122411, 0.134581, 0.146730, 0.158858, 0.170962, 0.183040,
	0.195090, 0.207111, 0.219101, 0.231058, 0.242980, 0.254866, 0.266713, 0.278520,
	0.290285, 0.302006, 0.313682, 0.325310, 0.336890, 0.348419, 0.359895, 0.371317,
	0.382683, 0.393992, 0.405241, 0.416430, 0.427555, 0.438616, 0.449611, 0.460539,
	0.471397, 0.482184, 0.492898, 0.503538, 0.514103, 0.524590, 0.534998, 0.545325,
	0.555570, 0.565732, 0.575808, 0.585798, 0.595699, 0.605511, 0.615232, 0.624859,
	0.634393, 0.643832, 0.653173, 0.662416, 0.671559, 0.680601, 0.689541, 0.698376,
	0.707107, 0.715731, 0.724247, 0.732654, 0.740951, 0.749136, 0.757209, 0.765167,
	0.773010, 0.780737, 0.788346, 0.795837, 0.803208, 0.810457, 0.817585, 0.824589,
	0.831470, 0.838225, 0.844854, 0.851355, 0.857729, 0.863973, 0.870087, 0.876070,
	0.881921, 0.887640, 0.893224, 0.898674, 0.903989, 0.909168, 0.914210, 0.919114,
	0.923880, 0.928506, 0.932993, 0.937339, 0.941544, 0.945607, 0.949528, 0.953306,
	0.956940, 0.960431, 0.963776, 0.966976, 0.970031, 0.972940, 0.975702, 0.978317,
	0.980785, 0.983105, 0.985278, 0.987301, 0.989177, 0.990903, 0.992480, 0.993907,
	0.995185, 0.996313, 0.997290, 0.998118, 0.998795, 0.999322, 0.999699, 0.999925
	};

	return .99*lookup[index];
}
