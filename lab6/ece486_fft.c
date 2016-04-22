int peak_detect(float *data, int size, float thresh, int *peaks)
{
	int i, count = 0;

	for (i = 1; i < size-1; i++) {
		if (data[i] >= thresh && data[i-1] < data[i] && data[i+1] < data[i])
			peaks[count++] = i+1;
	}
	return count;
}
