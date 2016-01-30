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

struct s {
    int M;
    int blocksize;
    float *data_array;
}
  
void memalloc(int bs, int n);
void shift(struct s *data_props, float start);
float mean(struct s *data_props);
float * calc_running_mean(float *x, struct s *data_props);
  
#endif
