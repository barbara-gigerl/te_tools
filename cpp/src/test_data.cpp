#include "test_data.h"
#include "test_data_utils.h"

#include <iostream>

void TestData::get_test_data(int T, double lam_x, double mu, double gamma, double** Sx, int* len_Sx, double** Sy, int* len_Sy)
{

    if(!*Sx) 
        Hppp(T, lam_x, Sx, len_Sx);
        
    Sx_heap = *Sx;

    double lam_upper = 0;
    for(double x = 0; x < T; x+=(((double)T)/10000.0))
    {
        double lam_val = lam(x, mu, gamma, *Sx, *len_Sx);

        if(lam_val > lam_upper)
            lam_upper = lam_val;
    }


    NHppp(T, lam_upper, mu, gamma, *Sx, *len_Sx, Sy, len_Sy);

}

double TestData::lam(double t, double mu, double gamma, double* Sx, int len_Sx)
{
    double g_sum = 0;
    for(int i = 0; i < len_Sx; i++)
    {   
        double ti = Sx[i];
        if(ti < t) {
            g_sum += g(t-ti);
        }
    }

    return mu + gamma * g_sum;
}

void TestData::NHppp(int T, double lam_upper, double mu, double gamma, double* Sx, int len_Sx, double** Sy, int* len_Sy)
{
    double t = 0;

    std::random_device rd;
    std::mt19937_64 mt(rd());
    std::uniform_real_distribution<double> uniform_d(0,1);

    std::vector<double>* Sy_vec = new vector<double>();
    
    while(t < T)
    {
        double u = uniform_d(mt);
        t = t - 1.0 / lam_upper * log(u);
        double u2 = uniform_d(mt);
        if(u2 < (lam(t, mu, gamma, Sx, len_Sx) / lam_upper))
        {
            if(t < (double)T)
                (*Sy_vec).emplace_back(t);
        }

    }


    *Sy = &(*Sy_vec)[0];
    *len_Sy = (*Sy_vec).size();

    Sy_vec_heap = Sy_vec;
}

TestData::~TestData()
{
    delete Sy_vec_heap;
    delete [] Sx_heap;
}