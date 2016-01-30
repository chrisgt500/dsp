/*!
 * @file
 * @brief ECE 486 Lab 1 running_mean
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @date Jan 27 2016
 *
 */


#include <stdlib.h>
#include "running_mean.h"

int main(void){
  int M, blocksize, i, j, k;
  float x[10][10];
  float y[10][10];
  //struct data;
  M = 2;
  blocksize = 10;
  k = 1;
  
  *data = memalloc(M, blocksize);
  
  for (i=0; i <10; i++) {
    for (j=0; j<10; j++) {
      x[i][j] = k;
      k++;
    }
  }
  
  
  for (i=0; i < 10; i++) {
  	y[i] = calc_running_mean(x[i], data); 
  }
  	  
  memclean(data);


}