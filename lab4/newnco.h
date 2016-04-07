#ifndef ECE486_NCO
#define ECE486_NCO

#ifndef PI
#define PI 3.14159265359
#endif
#ifndef i32
#define  i32 4294967296
#endif
typedef struct{
  uint32_t f0; //!<
  uint32_t theta_temp; //!<
  uint32_t theta_const; //!
}NCO_T;

/*!
 *@Brief
 *
 *THIS FUNCTION DOES A THING
 *
 *@returns The function returns a pointer to a "NCO_T" data type
 *(which is defined in "nco.h").
 */

NCO_T *init_nco(
  float f0, //!< Initial NCO discrete-time frequency for the output sample
            //!<sequence (in cycles/sample)
  float theta //!<Inital Phase of the output sample sequence (radians)
);

/*!
 *@Brief
 *
 *THIS FUNCTION DOES A THING
 *
 *@returns On return, y[i] (for i=0,1,...n_samples-1) contains the the next
 *n_samples values of the NCO output sequence.  Subsequent calls to
 *nco_get_samples() continues to return NCO output samples with no
 *phase discontinuities from one call to the next.
 */

void nco_get_samples(
  NCO_T *s, //!<pointer to initialized NCO_T
  float *y, //!<Caller-supplied array to be replaced by NCO output samples
  int n_samples //!<Number of NCO output samples to generate
);

/*!
 *@Brief
 *
 *THIS FUNCTION DOES A THING
 *
 *@returns The NCO_T structure s is modified so that subsequent calls to nco_get_samples()
 *will operate at frequency f_new (without loss of phase continuity).
 */

void nco_set_frequency(
  NCO_T *s, //!< pointer to NCO_T
  float f_new  //!<New NCO frequency (in cycles/sample)
);

/*!
 *@Brief
 *
 *THIS FUNCTION DOES A THING
 *
 *@returns The NCO_T structure s is modified so that subsequent calls to nco_get_samples()
 *will operate with the phase shift given by theta (in radians).
 */

void nco_set_phase(
  NCO_T *s, //!< pointer to NCO_T
  float theta //!< New NCO phase
);

/*!
 *@Brief
 *
 *THIS FUNCTION DOES A THING
 *
 *@returns Any resources associated with the nco "s" are released.
 */

 void destroy_nco(
   NCO_T *s //!<pointer to NCO_T, as provided by init_nco()
 );

 /*!
  *@Brief
  *
  *THIS FUNCTION DOES A THING
  *
  *@returns The function returns a value from the cosine lookup table
  */

  float cosine_lookup(
    uint32_t index //!<index to return a value from the look up table
  );



#endif