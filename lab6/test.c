#include <stdio.h>
#include <stdlib.h>


#include "ece486_fft.h"

int main(char argc, char *argv[])
{
	float data[] = {1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,9.,8.,7.,6.,5.,4.,3.,2.,4.,5.,6.,7.,6.,5.,4.};
	int size = 25;
	float thresh = 3.;
	int peaks[] = {0,0,0,0,0,0};

	int ret;
	ret = peak_detect(data, size, thresh, peaks);

	printf("%d peaks found.\n", ret);
	printf("Peaks found at: ");
	for (ret = 0; ret < 6; ret++) {
		if (peaks[ret])
			printf("%d", peaks[ret]);
	}



	return 0;
}
