/*!
 * @file
 * @brief ECE 486 Lab 2 Real Time IIR implementation
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @date Feb 9 2016
 *
 *
 *
 */

#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"

#include "ece486_iir.h"
#include "ece486.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
  float *input, *output;  //initialization
  int i,blocksize;
  BIQUAD_T *data;

  initialize(FS_50K, MONO_IN, MONO_OUT);
  float coefs[10] = {2.2044, 0.0, 2.2044, -.6088, .9702, 2.9658,-3.4865,2.9658,-.350,-.4250};
  					/* coefficients from Homework 2*/
  float g = .0173; // gain
  int sections = 2; // number of filters

  blocksize = getblocksize();

  input = (float *)malloc(sizeof(float)*blocksize);
  output = (float *)malloc(sizeof(float)*blocksize);

  if (input==NULL || output==NULL) {  //error checking
    flagerror(MEMORY_ALLOCATION_ERROR);
    while(1);
  }

  data = init_biquad(sections,g,coefs,blocksize);  //one initialization

  while(1){  //waits for ADC to fill, filters data, outputs to DAC
    getblock(input);
    DIGITAL_IO_SET();
    calc_biquad(data,input,output);
    DIGITAL_IO_RESET();
    putblock(output);
  }
  destroy_biquad(data);  //frees any allocated memory
  return 0;
}
