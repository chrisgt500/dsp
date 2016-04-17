/*!
 * @file ece486_nco.h
 * 
 * @brief Gives function prototypes for ece486_nco.c
 * 
 * @author ECE486 Lab Group 9
 * @author Colin Leary
 * @author Forrest Smith
 * @author Sean Turner
 * 
 * @date April 7, 2016
 * 
 * This file contains the functions needed to implement a numerically controlled 
 * oscillator. The struct definition declares the values needed and places them
 * within a typedeffed struct. The init_nco function sets the initial values of
 * of the struct. nco_get_samples will calculate and return the values of the
 * NCO. The nco_set_frequency and nco_set_phase functions alter the value for
 * the frequency and phase, respectively, on subsequent calls to nco_get_samples
 * destroy_nco destroys the structure and cleans up pointers.
 * 
 */
 
 #ifndef ECE486_NCO
#define ECE486_NCO

#ifndef PI
#define PI 3.14159265359		//!< Pi
#endif
#ifndef i32
#define  i32 4294967296			//!< 2^32
#endif

/*!
 * @brief A structure for holding NCO_T components
 *
 * The NCO_T structure is used to hold all of the values needed to execute 
 * nco_get_samples.
 *
 */
typedef struct{
  uint32_t f0; //!< Frequecy of NCO
  uint32_t theta_temp; //!< Previous phase angle, used to calculate next value
  uint32_t theta_const; //!< Phase cosine must be to obtain desired sinusoid
}NCO_T;



/*!
 *@Brief A function for initializing the NCO_T structure.
 *
 * This function dynamically allocates the memory needed for the struct. It then
 * assigns the passed parameters to the proper structure elements.
 *
 *@returns The function returns a pointer to a "NCO_T" data type
 *(which is defined in "nco.h").
 */
NCO_T *init_nco(
  float f0, //!< [in] Initial NCO discrete-time frequency for the output sample
            //!< sequence (in cycles/sample)
  float theta //!< [in] Inital Phase of the output sample sequence (radians)
);



/*!
 *@Brief A function for calculating the values of an NCO.
 *
 * This function calculates the index of a cosine lookup table and then uses
 * that index to obtain a value from the lookup table. The value is written to 
 * an output buffer.
 *
 *@returns On return, y[i] (for i=0,1,...n_samples-1) contains the the next
 *n_samples values of the NCO output sequence.  Subsequent calls to
 *nco_get_samples() continues to return NCO output samples with no
 *phase discontinuities from one call to the next.
 */
void nco_get_samples(
  NCO_T *s, //!< [in, out] pointer to initialized NCO_T
  float *y, //!< [in] Caller-supplied array to be replaced by NCO output samples
  int n_samples //!< [in] Number of NCO output samples to generate
);



/*!
 *@Brief A function to set the frequency of the NCO.
 *
 * This function modifies the value f0 in the struct to modify the frequency of
 * the output.
 *
 *@returns The NCO_T structure s is modified so that subsequent calls to nco_get_samples()
 *will operate at frequency f_new (without loss of phase continuity).
 */
void nco_set_frequency(
  NCO_T *s, //!< [in, out] pointer to NCO_T
  float f_new  //!< [in] New NCO frequency (in cycles/sample)
);





/*!
 *@Brief A function to set the phase of the NCO.
 *
 * This function modifies the value theta in the struct to modify the phase of
 * the output.
 *
 *@returns The NCO_T structure s is modified so that subsequent calls to nco_get_samples()
 *will operate with the phase shift given by theta (in radians).
 */
void nco_set_phase(
  NCO_T *s, //!< [in, out] pointer to NCO_T
  float theta //!< [in] New NCO phase
);




/*!
 *@Brief A function to destroy the NCO struct.
 *
 * This function frees the memory allocated to NCO_T by the init function and
 * sets the pointers to NULL.
 *
 *@returns Any resources associated with the nco "s" are released.
 */
 void destroy_nco(
   NCO_T *s //!< [in, out] pointer to NCO_T, as provided by init_nco()
 );

 

 /*!
  *@Brief A function to return the value of a cosine lookup table.
  *
  * This function takes the input parameter and returns the value of a cosine
  * lookup table at the given index.
  *
  *@returns The function returns a value from the cosine lookup table
  */
  float cosine_lookup(
    uint32_t index //!< [in] index to return a value from the look up table
  );



#endif
