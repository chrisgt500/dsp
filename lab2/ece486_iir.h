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

struct BIQUAD_T{
  float g;
  int sections;
  int blocksize;
  float stored_data[2];
  float current_coefs[5];
  float *all_coefs;
};

/*!
  * @brief
  *
  * @returns
*/

BIQUAD_T *init_biquad (
  int sections, //!<
  float g, //!<
  float *biquad_coefs, //!<
  int blocksize //!<
 );

 /*!
  * @brief
  *
  * @returns
  */

 void 	calc_biquad (
   BIQUAD_T *s, //!<
   float *x, //!<
   float *y //!<
 );

 /*!
  * @brief
  *
  * @returns
  */

void 	destroy_biquad (
  BIQUAD_T *s //!<
);


#endif
