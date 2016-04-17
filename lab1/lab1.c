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

#include <stdio.h>
#include <stdlib.h>
#include "running_mean.h"

int main(void){
  int M, blocksize, iterations;  //!<initialize variables
  
  
  /*! There are 3 scenarios: M > blocksize, M < blocksize, and M = blocksize */
  //! M < blocksize:
  M = 3;
  blocksize = 5;
  iterations = 5;

	testfunction(M, blocksize, iterations);
	
	//! M > blocksize
	M = 4;
	blocksize = 2;
	iterations = 5;
	
	testfunction(M, blocksize, iterations);
	//! M = blocksize
	M=6;
	blocksize=6;
	iterations=5;

	testfunction(M, blocksize, iterations); 
  return 0;
}
