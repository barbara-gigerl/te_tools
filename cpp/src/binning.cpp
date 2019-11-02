using namespace std;

#include <iostream>
#include <numeric>
#include <cmath>
#include <cstring> 
#include <vector>
#include <bitset>
#include <sstream>
#include <assert.h>
#include <algorithm>


#include "binning.h"


void Binning::get_logarithmic_bins(int start, int divisor, int n, int* bins)
{
  float bin_width = start;
  for(int i = n-1; i >= 0; i--)
  {
      bins[i] = int(round(bin_width));
      bin_width /= divisor;
  }
}


void Binning::get_equal_bins(int width, int n, int* bins)
{
    std::fill(bins, bins+n, width);
}


void Binning::get_linear_bins(int start, int stop, int step, int* bins)
{
    int i = 0;
    int bin_with = start;
    while(bin_with < stop)
    {
        bins[i] = bin_with;
        bin_with += step;
        i++;
    }
}


long Binning::compute_binning(double* Sy, int len_Sy, double* Sx, int len_Sx, int* bins, int len_bins, int T)
{
    k = len_bins;

    prob_map = new double[(1 << (k + k)) * sizeof(double)];
    memset(prob_map, 0, (1 << (k + k)) * sizeof(double)); 
    
    sort(Sy, Sy + len_Sy);
    sort(Sx, Sx + len_Sx);


    double* S_total = new double[(len_Sy+len_Sx)*sizeof(double)];
    memcpy(S_total, Sy, len_Sy*sizeof(double));
    memcpy(S_total+len_Sy, Sx, len_Sx*sizeof(double));
    sort(S_total, S_total + len_Sy + len_Sx);


    int idxY = 0;
    int idxX = 0;
    long w = accumulate(bins, bins + k, 0); 

    for(int idx = 0; idx < (len_Sy+len_Sx); idx++)
    {
        double val = S_total[idx];
        for(int i = (val-w+1); i < (val+1); i++)
        {
            if((i+w) == T+2) 
                break;
            
            if(i < 0) 
                continue;
            
            if(idx > 0 && ((i <= S_total[idx-1]) && (S_total[idx-1] < (i+w))))
                continue;
            
            int comb = 0;

            int idxY_tmp = idxY;
            while((idxY_tmp < len_Sy) && (Sy[idxY_tmp] < (i+w)))
            {
                int sumbins = 0;
                for(int bin_idx = len_bins-1; bin_idx > -1; bin_idx--)
                {
                    if(((i+sumbins) <= Sy[idxY_tmp]) && (Sy[idxY_tmp] < (i+sumbins+bins[bin_idx])))
                       comb |= (1 << (2 * len_bins - bin_idx - 1)); 
                    sumbins += bins[bin_idx];
                }
                idxY_tmp++;
            }

            int idxX_tmp = idxX;
            while((idxX_tmp < len_Sx) && (Sx[idxX_tmp] < (i+w)))
            {
                int sumbins = 0;
                for(int bin_idx = len_bins-1; bin_idx > -1; bin_idx--)
                {
                    if(((i+sumbins) <= Sx[idxX_tmp]) && (Sx[idxX_tmp] < (i+sumbins+bins[bin_idx])))
                        comb |= (1 << (len_bins - bin_idx - 1));
                    sumbins += bins[bin_idx];
                }
                idxX_tmp++;
            } 
            prob_map[comb]++;
        }

        if((idxY < len_Sy) && S_total[idx] == Sy[idxY])
            idxY++;
        else
            idxX++;
    }

    int p_sum =  accumulate(prob_map, prob_map + (1 << (k + k)), 0);
    prob_map[0] = T - w - p_sum + 2;
    for(int i = 0; i < (1 << (k + k)); i++)
        prob_map[i] /= (T-w+2);
    
    delete [] S_total;

    return T - w + 2;
}


void Binning::eliminate_bin(int eliminate_bins, double* reduced_prob_map)
{   
    for(int prob_idx = 0; prob_idx < (1 << (k + k)); prob_idx++) //iterate over probability map
    {
        int idx = 0;
        for(int bin_idx = 0; bin_idx < k + k; bin_idx++) //iterate over all bins
        {
            if((eliminate_bins >> (k + k - 1 - bin_idx) & 1))
            {
                int b = prob_idx >> (k+k-(bin_idx+1)) & 1;
                idx = idx << 1;
                idx |= b;
            }
        }
        reduced_prob_map[idx] += prob_map[prob_idx];
    }
}

void Binning::eliminate_bin(int eliminate_bins, double* reduced_prob_map, double* prob_map)
{   
    for(int prob_idx = 0; prob_idx < (1 << (k + k)); prob_idx++) //iterate over probability map
    {
        int idx = 0;
        for(int bin_idx = 0; bin_idx < k + k; bin_idx++) //iterate over all bins
        {
            if((eliminate_bins >> (k + k - 1 - bin_idx) & 1))
            {
                int b = prob_idx >> (k+k-(bin_idx+1)) & 1;
                idx = idx << 1;
                idx |= b;
            }
        }
        reduced_prob_map[idx] += prob_map[prob_idx];
    }
}


Binning::~Binning()
{
    delete[] prob_map;
}