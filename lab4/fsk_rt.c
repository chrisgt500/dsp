
#define D1 5

int main(void){

	int i;

	float *input, *output1, *output2;

	initialize(FS_50k, MONO_IN, STEREO_OUT)

	fs = getsamplingfrequency();
	blocksize = getblocksize();

	float lpf1[35] = {
	1.000000, -1.818543, 1.000000, -1.819877, 0.999565,
	1.000000, -1.817198, 1.000000, -1.819724, 0.998058,
	1.000000, -1.812439, 1.000000, -1.819981, 0.993753,
	1.000000, -1.796425, 1.000000, -1.820970, 0.980982,
	1.000000, -1.736438, 1.000000, -1.823665, 0.946998,
	1.000000, -1.404771, 1.000000, -1.828775, 0.882739,
	1.000000, 1.000000, 0.000000, -0.916116, 0.000000
	};


	while(1){
		getblock(input);

		//STAGE 1 processing with sample at fs
		//array size blocksize

		//Decimation:
		for(i = 0; i < blocksize/D1; i++)
		stage2_input[i] = stage1_output[i*D1];


		//Stage 2 processing with sample fs/D1
		//array size blocksize/D1


		//output values to the dac (Might need other stuff)
		for (i=0; i<MY_NSAMP/D1; i++) {
			// Every stage-3 output should be written to D1 output samples!
			for (j=0; j<D1; j++) {
  				output1[i*D1+j] = stage2_output_re[i];
  				output2[i*D1+j] = stage2_output_im[i];
			}
  		}

		putblockstereo(output1, output2);

	}


}
