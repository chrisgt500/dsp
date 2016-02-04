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

	M = 4;
	blocksize = 2;
	iterations = 5;
	
	testfunction(M, blocksize, iterations);

	M=6;
	blocksize=6;
	iterations=5;

	testfunction(M, blocksize, iterations); 
/* 
  float x[iterations][blocksize];
  float *y[blocksize];

  
  k = 1;                   
 //!initialize testing vectors (iteration number of blocks, of size 10, containing numbers 1:iterations*blocksize)
  for (i=0; i <iterations; i++) {
    for (j=0; j<blocksize; j++) {
      x[i][j] = k;
      k++;
    }
  }
  
    data = memalloc(blocksize, M);    //!<dynamically allocates memory for a struct that holds blocksize, M, and current data array
  
  
  for (i=0; i < iterations; i++) {          //!<performs the running mean routine, iterations number of times
  	y[i] = calc_running_mean(x[i], data);
  }
 
for (i=0; i <iterations; i++) {             //!<prints the result and frees the result memory
    for (j=0; j<blocksize; j++) {
        printf("%f ",y[i][j]);
    }
    free(y[i]);
    printf("\n");
  }

 memclean(data);    //!<free the memory from the struct
 
//! M > blocksize
printf("\n\n"); 
   M = 10;
  blocksize = 5;
  iterations = 5;
  

  
  k = 1;  
//! initialize testing vectors (iteration number of blocks, of size 10, containing numbers 1:iterations*blocksize)
  for (i=0; i <iterations; i++) {
    for (j=0; j<blocksize; j++) {
      x[i][j] = k;
      k++;
    }
  }
  
    data = memalloc(blocksize, M);    //dynamically allocates memory for a struct that holds blocksize, M, and current data array
  
  
  for (i=0; i < iterations; i++) {          //performs the running mean routine, iterations number of times
  	y[i] = calc_running_mean(x[i], data);
  }
 
for (i=0; i <iterations; i++) {             //prints the result and frees the result memory
    for (j=0; j<blocksize; j++) {
        printf("%f ",y[i][j]);
    }
    free(y[i]);
    printf("\n");
  }

 memclean(data);        //free the memory from the struct
    
    
// M = blocksize
printf("\n\n"); 
   M = 5;
  blocksize = 5;
  iterations = 5;

  
  k = 1;                    //initialize testing vectors (iteration number of blocks, of size 10, containing numbers 1:iterations*blocksize)
  for (i=0; i <iterations; i++) {
    for (j=0; j<blocksize; j++) {
      x[i][j] = k;
      k++;
    }
  }
  
    data = memalloc(blocksize, M);    //dynamically allocates memory for a struct that holds blocksize, M, and current data array
  
  
  for (i=0; i < iterations; i++) {          //performs the running mean routine, iterations number of times
  	y[i] = calc_running_mean(x[i], data);
  }
 
for (i=0; i <iterations; i++) {             //prints the result and frees the result memory
    for (j=0; j<blocksize; j++) {
        printf("%f ",y[i][j]);
    }
    free(y[i]);
    printf("\n");
  }

 memclean(data);        //free the memory from the struct
	*/
    return 0;
}
