/*!
 * @file
 * @brief ECE 486 Lab 2 IIR  Test
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @date Feb 9 2016
 *
 */

#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"

#include "ece486.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
  float *input, *output;

  initialize(FS_50K, MONO_IN, MONO_OUT);

  //init_biquad
  while(1){
    getblock(input);
    DIGITAL_IO_SET();
    //calc_biquad
    DIGITAL_IO_RESET();
    putblock(output);
  }
  //destroy_biquad
  return 0;
}
