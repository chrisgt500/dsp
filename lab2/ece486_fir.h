/*!
 * @file
 * @brief ECE 486 Lab 2 FIR Filter header file
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @date Feb 9 2016
 *
 * The file contains the necessary functions to perform a discrete time convolution 
 *
 *
 */

#ifndef ECE486_FIR_H
#define ECE486_FIR_H

/*!
  * @brief A structure for holding FIR_T components
  *
  * This structure holds everything needed to use calc_fir
*/
typedef struct {
  int M; //!< This is number of coefficients of h
  int blocksize; //!< This is the number of data values passed in at once
  float *h; //!< This is a vector containing the coefficients of an impulse response
  int index; //!< This is the index of stored_data that points to the oldest value
  float *stored_data; //!< The array that hold the last M values
}FIR_T;


/*!
  * @brief The function initializes and returns a structure of type FIR_T.
  *
  * This function takes several parameters and declares a struct containing the
  * parameters.  The function dynamically allocates the memory for the structure.
  *
  * @returns On return, an allocated and filled structure of type FIR_T is returned.
*/
FIR_T * init_fir (
  float *fir_coefs, //!< [in] A pointer to the array of filter coefficients
  int n_coef, //!< [in] The number of coefficients in the filter
  int blocksize //!< [in] How many data values are passed
 );

/*!
 * @brief The function performs a discrete time convolution.
 *
 * The function performs a discrete time convolution of the input data with the
 * impulse reponse found in the FIR_T structure.  The program stores the convoluted
 * filter data in y.
 *
 * @returns The struct and output data are both returned
*/
void calc_fir (
  FIR_T *s, //!< [in,out] The structure that holds all data needed to calculate y
  float *x, //!< [in] The data stream to filter, in size of blocksize
  float *y //!< [out]  The filter data after the discrete time convolution
);

/*!
  * @brief The function frees allocated memory.
  *
  * The function frees the allocated FIR_T structure.
  *
 */
void destroy_fir (
  FIR_T *s //!< This is the structure that needs to be freed
);

#endif
