int peak_detect(float *data, int size, float thresh, int *peaks)
{
	int i, count = 0;
	float r = thresh;
	for (i = 0; i < size; i++) {
		if (data[i] >= thresh) {
			if (data[i] <= r) {
				r = data[i];
			}
			else {
				r = thresh;
				peaks[count++] = i-1;
			}
		}
	}
}
