/*!
 * @file
 * @brief ECE 486 Lab 2 IIR Test Code
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @date Feb 18 2016
 *
 *
 *
 *
 *
 *
 */

#include "ece486_iir.h"
#include "ece486.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void){

  int i,blocksize;
  BIQUAD_T *data;


  float coefs[10] = {2.2044, 0.0, 2.2044, -.6088, .9702, 2.9658,-3.4865,2.9658,-.350,-.4250};
  float g = 1;
  int sections = 2;
  blocksize = 100;
  float input[blocksize];
  float output[blocksize] = {0};

  for( i = 0 ; i < blocksize; i++){
    input[i] =
  }



}
