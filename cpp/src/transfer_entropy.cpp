#include "transfer_entropy.h"
#include "binning.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cstring>
#include <math.h>
#include <bitset>
#include <chrono>
#include <assert.h>
#include <iterator>
#include <iomanip>
using namespace std;



TransferEntropy::TransferEntropy(double* Sy, int len_Sy, double* Sx, int len_Sx) : Sy(Sy), len_Sy(len_Sy), Sx(Sx), len_Sx(len_Sx) {
  
  
}

double TransferEntropy::panzeri_treves_bias(double* pY_t_tmk_X_tm1_tml, double total, int k, double* pY_t_tmk)
{
  int len_pY_t_tmk_X_tm1_tml =  (1 << (k + k - 1));
  int len_pY_t_tmk = (1 << k);
  double N = 0;
  for(int i = 0; i < len_pY_t_tmk_X_tm1_tml; i++)
    N += pY_t_tmk_X_tm1_tml[i] * total;

  double Nb_sum1 = 0;
  for(int i = 0; i < len_pY_t_tmk; i++) 
    if(pY_t_tmk[i]) 
      Nb_sum1 += ((i & (1 << (k-1))) >> (k-1));
  

  double Nb_sum2 = 0;
  for(int i = 0; i < len_pY_t_tmk_X_tm1_tml; i++)
    if(pY_t_tmk_X_tm1_tml[i])
      Nb_sum2 += ((i & (1 << (k+k-2))) >> (k+k-2));


  return (-1 / (2 * N * log(2))) * (Nb_sum1 - Nb_sum2);    
}

void print_prob(double* p, int len)
{
  for(int i = 0; i < len; i++)
    cout << "  " << p[i] << "  " << endl;
  cout << endl;
}

double TransferEntropy::T1(double* pY_t_tmk, double* pY_tm1_tmk, double* pY_tm1_tmk_X_tm1_tml, double* pY_t_tmk_X_tm1_tml, int k)
{

  int len_pY_t_tmk = (1 << k);
  int len_pY_t_tmk_X_tm1_tml = (1 << (k + k - 1));

  double H1 = 0.0;

  for(int i = 0; i < len_pY_t_tmk; i++)
  {
    double val = pY_t_tmk[i];
    double pY_tm1_tmk_val = pY_tm1_tmk[i & ((1 << (k-1)) - 1)];
   
    if(val == 0 || pY_tm1_tmk_val == 0)
      continue;

    
    
    double pcond = val / pY_tm1_tmk_val;
    H1 += val * log2(pcond);
  }
  H1 = -H1;
  HY = H1;

  double H2 = 0;

   for(int i = 0; i < len_pY_t_tmk_X_tm1_tml; i++)
  {
    double val = pY_t_tmk_X_tm1_tml[i];
    double pY_tm1_tmk_X_tm1_tml_val = pY_tm1_tmk_X_tm1_tml[i & ((1 << (k+k-2)) - 1)];
    if(val == 0 || pY_tm1_tmk_X_tm1_tml_val == 0)
      continue;
    


    double pcond = val / pY_tm1_tmk_X_tm1_tml_val;
    H2 += val * log2(pcond);

  }

  H2 = -H2;
  HYX = H2;
  return max(H1 - H2, 0.0);  
}

double TransferEntropy::T2(double* pY_t_tmk, double* pY_tm1_tmk, double* pY_tm1_tmk_X_tm1_tml, double* pY_t_tmk_X_tm1_tml, int k)
{
  double te = 0;
  int len_pY_t_tmk_X_tm1_tml = (1 << (k + k - 1));
  int len_pY_t_tmk = 1 << (k-1);


  for(int i = 0; i < len_pY_t_tmk_X_tm1_tml; i++)
  {
    double val = pY_t_tmk_X_tm1_tml[i]; //ok
    double pY_tm1_tmk_val = pY_tm1_tmk[(i >> (k-1)) & ((1 << (k-1))-1)];
    double pY_tm1_tmk_X_tm1_tml_val = pY_tm1_tmk_X_tm1_tml[i & (~(1 << (k+k-2)))]; //ok
    double pY_t_tmk_val = pY_t_tmk[(i / len_pY_t_tmk)]; //ok

    double logval1 = val * pY_tm1_tmk_val;
    double logval2 = pY_tm1_tmk_X_tm1_tml_val * pY_t_tmk_val;
    if(logval1 == 0 || logval2 == 0)
      continue;
    te += val * log2(logval1 / logval2);
  }


  return max(0.0, te);

}


double TransferEntropy::TE(int* bins, int k, int T, double (TransferEntropy::*T_func)(double*, double*, double*, double*, int), double* pt_bias)
{
    Binning binning;
    vector<double> Sy_filtered;
    vector<double> Sx_filtered;
    for(int i = 0; i < len_Sx; i++)
      if(Sx[i] <= T)
        Sx_filtered.emplace_back(Sx[i]);
    for(int i = 0; i < len_Sy; i++)
      if(Sy[i] <= T)
        Sy_filtered.emplace_back(Sy[i]);
      
    int total = binning.compute_binning(Sy_filtered.data(), Sy_filtered.size(), Sx_filtered.data(), Sx_filtered.size(), bins, k, T);

    int eliminate_bins = (~((1 << k) - 1));
    double* pY_t_tmk = new double[(1 << k)];
    memset(pY_t_tmk, 0, ((1 << k)) * sizeof(double));
    binning.eliminate_bin(eliminate_bins, pY_t_tmk);

    
    
    eliminate_bins = (~((1 << k) - 1)) & (~ (1 << (k+k)-1));
    double* pY_tm1_tmk = new double[1 << (k-1)];
    memset(pY_tm1_tmk, 0, (1 << (k-1)) * sizeof(double));
    binning.eliminate_bin(eliminate_bins, pY_tm1_tmk);
    
    eliminate_bins = (~((1 << k) - 1)) & (~ (1 << (k+k)-1)) | ((1<<(k-1))-1);
    double* pY_tm1_tmk_X_tm1_tml = new double[(1 << (k + k - 2))];
    memset(pY_tm1_tmk_X_tm1_tml, 0, (1 << (k + k - 2)) * sizeof(double));
    binning.eliminate_bin(eliminate_bins, pY_tm1_tmk_X_tm1_tml);



    eliminate_bins = (~((1 << k) - 1)) | ((1<<(k-1))-1);
    double* pY_t_tmk_X_tm1_tml = new double[(1 << (k + k - 1))];
    memset(pY_t_tmk_X_tm1_tml, 0,(1 << (k + k - 1)) * sizeof(double));
    binning.eliminate_bin(eliminate_bins, pY_t_tmk_X_tm1_tml);
  

    double te = (this->*T_func)(pY_t_tmk, pY_tm1_tmk, pY_tm1_tmk_X_tm1_tml, pY_t_tmk_X_tm1_tml, k);

    if(pt_bias)
      *pt_bias = panzeri_treves_bias(pY_t_tmk_X_tm1_tml, total, k, pY_t_tmk);

    delete[] pY_t_tmk;
    delete[] pY_tm1_tmk;
    delete[] pY_tm1_tmk_X_tm1_tml;
    delete[] pY_t_tmk_X_tm1_tml;

    return te;
}