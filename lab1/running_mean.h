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

 #ifndef RUNNING_MEAN_H
 #define RUNNING_MEAN_H

/*!
 * @brief
 *
 * @returns
 *
 */

struct s{
    int M;
    int blocksize;
    float *data_array;
};


/*!
 * @brief Set number of elements to average over, the blocksize and initialize
 * the data array.
 *
 * @returns 	On return, the data_props struct elements are initialized and
				the struct is returned.
 */
struct s * memalloc(
	int block,		//!< [in] The blocksize of the data to be averaged over.
	int n		//!< [in] The number of elements to be averaged over.
);

/*!
 * @brief Create test cases based on the M, blocksize, and number of iterations
 * passed to the function.
 * 
 * Data is generated and inserted into an array of size iterations x blocksize.
 * The data is then processed through calc_running_mean, and the running averages
 * are printed.
 * 
 * @returns		All memory that was allocated is freed.  The function's return type is void;
 * therefore, it does not return anything.
 */

void testfunction(
	int M,	//!< [in] Integer which holds the value of M
	int bsize,	//!< [in] Integer which holds the blocksize for testing
	int iters	 //!< [in] Integer which holds the the number of test iterations to perform
);
/*!git 
 * @brief Shift each element in data_props->data_array to the right by one.
 *
 * The last element of the array is destroyed by the shifting process and a new			
 * element is placed at the beginning of the array
 *
 * @returns		On return, all elements of the array @a data_props->data_array
 *				have their indeces increased by 1. The last element is lost and 
 *				the first element is replaced by @a start.
 */
void shift(
	struct s *data_props,	//!< [in,out] Pointer to a struct which holds 
							//!< blocksize and the array to be shifted.
	float start				//!< [in] Value to be placed into first element in
							//!< the array.
);

float mean(struct s *data_props);
float * calc_running_mean(float *x, struct s *data_props);
void memclean(struct s *data_props);

#endif
