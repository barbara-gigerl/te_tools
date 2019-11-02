#ifndef TEST_DATA_UTILS_H
#define TEST_DATA_UTILS_H


#include <algorithm>
#include <math.h>
#include <random>
#include <iostream>

using namespace std;


inline double g(double delta_t)
{
  return std::min(1.0, pow((1.0 / delta_t), 3));
}


/**
 * @brief Hppp - Homogeneous poisson point process
          Generates data according to HPPP 
 * 
 * @param T -- time boundary
 * @param lam -- rate/intensity to be used in the process (λ)
 * @param Hppp_points -- list of timestamps of activities generated in the HPPP
 * @param len_Hppp_points --- length of list of timestamps of activities generated in the HPPP
 */
inline void Hppp(int T, double lam, double** Hppp_points, int* len_Hppp_points)
{

  std::random_device rd;
  std::mt19937_64 mt(rd());

  std::poisson_distribution<int> poisson_d(lam * T);

  int num_points = poisson_d(mt);  

  std::uniform_real_distribution<double> uniform_d(0,1);

  *Hppp_points = new double[num_points];
  *len_Hppp_points = num_points;

  for(int i = 0; i < num_points; i++)
  {
    (*Hppp_points)[i] = uniform_d(mt) * T;
  }
}


#endif /* TEST_DATA_UTILS_H */