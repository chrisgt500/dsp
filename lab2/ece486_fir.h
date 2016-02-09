/*!
 * @file
 * @brief ECE 486 Lab 2 FIR Filter
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @date Feb 9 2016
 *
 */

#ifndef ECE486_FIR_H
#define ECE486_FIR_H

/*!
  * @brief A structure for holding FIR_T components
  *
  * This structure holds everything needed to use calc_fir
*/
struct FIR_T{
  int M; //!< This is number of coefficients of h
  int blocksize; //!< This is the number of data values passed in at once
  float *h; //!< This is a vector containing the coefficients of an impulse response
};

/*!
  * @brief The function
  *
  * @returns
*/
FIR_T * 	init_fir (
  float *fir_coefs, //!<
  int n_coef, //!<
  int blocksize //!<
 );

/*!
 * @brief
 *
 * @returns
*/
void 	calc_fir (
  FIR_T *s, //!<
  float *x, //!<
  float *y //!<
);

/*!
  * @brief
  *
  * @returns
*/
void 	destroy_fir (
  FIR_T *s //!<
);


#endif
