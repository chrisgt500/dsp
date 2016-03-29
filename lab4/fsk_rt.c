
#define D1 5

int main(void){

	int i;

	float *input, *output1, *output2;

	initialize(FS_50k, MONO_IN, STEREO_OUT)

	fs = getsamplingfrequency();
	blocksize = getblocksize();


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
