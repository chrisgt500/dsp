/*!
 * @file
 * @brief ECE 486 Lab 2 FIR  Test
 a*
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @date Feb 9 2016
 *
 */

#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include "ece486_fir.h"

#include "ece486.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int main(void)
{
  float *input, *output;
  int blocksize;
  FIR_T *data;
  float h[10] ={2.2044, 1.3420, .8827, -.7646,-1.3219,-.0629,1.2442,.8185,-.7088,-1.2257};
  int n_coefs;


  initialize(FS_50K, MONO_IN, MONO_OUT);
  blocksize = getblocksize();

  input = (float *)malloc(sizeof(float)*blocksize);
  output = (float *)malloc(sizeof(float)*blocksize);

  data = init_fir(h,n_coefs,blocksize);

  while(1){
    getblock(input);
    DIGITAL_IO_SET();
    calc_fir(data,input,output);
    DIGITAL_IO_RESET();
    putblock(output);
  }
  destroy_fir(data);
  return 0;
}
