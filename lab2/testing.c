#include <stdio.h>
#include <stdlib.h>
#include "ece486_iir.h"


int main(void){

  int i,blocksize;
  BIQUAD_T *data;


  float coefs[10] = {2.2044, 0.0, 2.2044, -.6088, .9702, 2.9658,-3.4865,2.9658,-.350,-.4250};
  float g = 1;//.0173;
  int sections = 2;
  blocksize = 10;
  float input[10] = {1, 2, 3, 4, 5,6,7,8,9,10};
  float output[10] = {0};


  data = init_biquad(sections,g,coefs,blocksize);


  calc_biquad(data,input,output);

  printf("Output1\n");
  for(i = 0; i < blocksize; i++){
    printf("%f ",output[i]);
  }

  for( i = 0; i < blocksize ; i ++){
    input[i] = i + 1;
  }

  calc_biquad(data,input,output);
  printf("\n");

  printf("Output2\n");
  for(i = 0; i < blocksize; i++){
    printf("%f ",output[i]);
  }



  return 0;

}
