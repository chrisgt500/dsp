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

 #ifndef ECE486_IIR_H
 #define ECE486_IIR_H

 struct s{
     int M;
     int blocksize;
     float *data_array;
 };

 /*!
  * @brief
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
