/*!
 * @file
 * @brief ECE 486 Lab 2 IIR Filter
 *
 * @author ECE486 Lab Group 9
 * @author Colin Leary, Forrest Smith, Sean Turner
 *
 * @date Feb 25 2016
 *
 * This file contains the functions needed to perform a discrete time convolution.
 * Init biquad initializes any needed information, and calc_biquad calculates the transposed
 * Direct form 2 filter.
 */

#ifndef ECE486_BIQUAD_H
#define ECE486_BIQUAD_H

/*!
 * @brief A structure for holding BIQUAD_T components
 *
 * The BIQUAD_T structure is used to hold all of the
 * values needed to execute calc_biquad
 *
 */
typedef struct{
  int sections; //!< How many 2nd order filters to cascade
  int blocksize; //!< How many data values are passed at once
  float *u; //!< Holds two values needed to calculate the transposed direct form II
  float *v;
  float *all_coefs; //!< Holds all of the difference equation coefficients
}BIQUAD_T;

/*!
  * @brief A function for initializing the BIQUAD_T structure
  *
  * This function takes several parameters and dynamically allocates the required
  * memory. Once initialized, it contains everything to call calc_biquad
  *
  * @returns On return, the allocated and filled in struct is returned
*/
BIQUAD_T * init_biquad (
  int sections, //!< How many 2nd order filters to cascade
  float g, //!< The gain value
  float *biquad_coefs, //!< A pointer to the array of in the form [b10, b11, b12
                       //!< a11, a12, b20, ...]
  int blocksize //!< How many data values are passed at once
 );

 /*!
  * @brief    A function to perform a an IIR filter on a stream of data
  *
  * This function performs the transposed direct form II version of an IIR filter
  * on a stream of data.
  *
  * @returns  On return, all elements in the y pointer are a filtered version of x.
  *           The struct BIQUAD_T still holds all of the necessary information
  */
 void 	calc_biquad (
   BIQUAD_T *s, //!< [in,out] Pointer to the struct that holds all the needed information
   float *x, //!< [in] The data stream to filter, in size of blocksize
   float *y //!< [out] The filter data, after being filtered through the
            //!< transposed direct form II structure
 );

 /*!
  * @brief    A function to cleanly deallocate memory from the struct
  *
  * The function first frees the memory from the dynamically allocated array in
  * the struct, and then frees the memory for the struct itself.
  */
void 	destroy_biquad (
  BIQUAD_T *s //!< This is struct that has all the pointers to memory to be freed
);

/*!
 * @brief A function to update one data point through all filters
 *
 * The function takes 1 data point and puts it through all filters, storing the
 * intermediate values from call to call, based on the current filter
 *
 * @returns On return, the updated intermediate values stored in u and v are returned,
 * along with a float value that is the filtered point
 */
float update(
  float *u, //!< [in, out] Pointer to array that holds needed transposed direct form II
            //!< intermediate values
  float *v, //!< [in, out] Pointer to array that holds the other transposed direct form II
            //!< intermediate values
  float *coefs, //!< [in, out] Pointer to array that holds all of the biquad coefficients in
                //!< in the form [b00, b01, b02, a01, a02, b10, b11, ...]
  float x, //!< [in] The current data point to go through all of the filters
  int j //!< [in] The current filter being used, used to choose the appropriate u,v and coef
        //!< values
);


#endif
