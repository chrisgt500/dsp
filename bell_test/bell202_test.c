/*!
 * @file
 * @brief Create Bell 202 modulated test signal
 * @author Don Hummels
 * @date March 17, 2016
 *
 *
 * Modulate a fixed bit sequence using and audio FSK modulation format
 *    1200 bits/second
 *    "1": 1200 Hz
 *    "0": 2200 Hz
 *
 * Bit sequence is hard-coded, and is output on PC5
 * Each time the bit sequence repeats, PC4 is set high for one bit period.
 *
 * Note that there's a one-bit delay between the digital outputs PC4 and PC5
 * and the actual analog modulated DAC output due to buffering of the DAC
 * output samples.
 *
 * @addtogroup ece486_fir
 */


#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"

#include "ece486.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NBITS 20
#define NSAMP 80

int main (void) {
  float *input, *output;

  static int bit_sequence[NBITS] = {1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
  static int bit_index=0;

  static float lo_re = 1.0, lo_im = 0.0; // "Local Oscillator" LO: 1700 Hz
  static float lo_step_re = 0.993816462056378, lo_step_im = 0.111035308554278;

  static float y_re=1.0, y_im=0.0;	// Complex rep of output

  static float df_re=0.999464587476366, df_im;
  static float df_im_save=0.032719082821776;

  static float output_amp = 0.9;

  float temp;	// Temp variable for complex multiplies
  int i;

  setblocksize( NSAMP );

  initialize(FS_96K, MONO_IN, MONO_OUT);

  input = (float *)malloc(sizeof(float)*NSAMP);		// Unused input array
  output = (float *)malloc(sizeof(float)*NSAMP);	// AFSK Output

  while (1) {
    getblock(input);	//ask for a block of (unused) ADC samples

    /*
     * Note that the DAC is currently streaming out the PREVIOUS modulated
     * bit (from the last data block).  Here, we set the digital io bits
     * to indicate what is being streamed out.  PD0 should indicate the start
     * of the bit sequence. (When bit_index==1 here we know the DAC is streaming
     * out our bit_index==0 modulated result, and we need to set PD0.)
     */
    if (bit_index==1) {
      DIGITAL_IO_SET(); 	// PD0 indicates start of the bit sequence
    } else {
      DIGITAL_IO_RESET();
    }

    /*
     * Set the frequency offset depending on the modulated bit
     */
    if (bit_sequence[bit_index]==0) {
      df_im = df_im_save;	// df = +500 Hz offset
    } else {
      df_im = -df_im_save;	// df = -500 Hz offset
    }

    for (i=0; i<NSAMP; i++) {
      temp = y_re*df_re - y_im*df_im;
      y_im = y_re*df_im + y_im*df_re;	// Complex rep of output
      y_re = temp;			// exp(j*2*pi*df*n)

      temp = lo_re*lo_step_re - lo_im*lo_step_im;
      lo_im = lo_re*lo_step_im + lo_im*lo_step_re;
      lo_re = temp;			// LO: exp(j*2*pi*f0*n)

      output[i] = output_amp*(y_re*lo_re - y_im*lo_im);
    }

    bit_index += 1;
    if (bit_index==NBITS) bit_index = 0;




    putblock(output);
  }
  free(input);
  free(output);
}
