#include <stdio.h>
#include <stdlib.h>

#include "ece486_fft.h"

int main(int argc, char *argv[])
{
	float data[] = {1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,9.,8.,9.,6.,5.,4.,3.,2.,4.,5.,6.,7.,6.,5.,4.};
	int size = 25;
	float thresh = 3.;
	int max_peak;
	int peaks[] = {0,0,0,0,0,0,0,0,0,0};

	int ret;
	ret = peak_detect(data, size, thresh, peaks, max_peak);

	printf("%d peaks found.\n", ret);
	printf("Peaks found at: ");
	for (ret = 0; ret < 10; ret++) {
		if (peaks[ret]) printf("%d\n", peaks[ret]);
	}

	return 0;
}
