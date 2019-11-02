
#include "test_data_utils.h"
#include "test_data_network.h"

double TestDataNetwork::lam(double t, double mu, double* gammas, int* my_influencer, double** Sx_list, int* len_Sx_list, int N_influencer)
{
    double NY_sum = 0;

    for(int i = 0; i < N_influencer; i++)
    {
        if(my_influencer[i])
        {

            double g_sum = 0;
            for(int j = 0; j < len_Sx_list[i]; j++)
            {
                double ti = Sx_list[i][j];
                if(ti < t)
                    g_sum += g(t-Sx_list[i][j]);
            }
            NY_sum += g_sum * gammas[i];
        }

        
    }
    return mu + NY_sum;
}

void TestDataNetwork::NHppp(int T, double lam_upper, double mu, double* gammas, int* my_influencer, double** Sx_list, int* len_Sx_list, double**Sy_list, int* len_Sy_list, std::vector<double>* Sy_vec)
{
    double t = 0;
    
    while(t < T)
    {
        double u = uniform_d(mt);
        t = t - 1.0 / lam_upper * log(u);
        double u2 = uniform_d(mt);

        if(u2 < (lam(t, mu, gammas, my_influencer, Sx_list, len_Sx_list, N_influencer_heap) / lam_upper))
        {
            if(t < (double)T)
            {
                Sy_vec->emplace_back(t);
            }
        }
    }

    *Sy_list =  &(*Sy_vec)[0];
    *len_Sy_list = Sy_vec->size();

}

void TestDataNetwork::get_test_data(int T, double* lam_Sx, double mu, double* gammas, int* influencer, int N_influencer, int N_follower, double*** Sx_list, int** len_Sx_list, double*** Sy_list, int** len_Sy_list)
{
    Sx_list_heap = new double*[N_influencer];
    len_Sx_list_heap = new int[N_influencer];
    N_influencer_heap = N_influencer;
    *Sx_list = Sx_list_heap;
    *len_Sx_list = len_Sx_list_heap;

    for(int i = 0; i < N_influencer; i++){
        Hppp(T, lam_Sx[i], *Sx_list+i, *len_Sx_list+i);
    }

    Sy_list_vec_heap = new std::vector<double>[N_follower]();
    Sy_list_heap = new double*[N_follower];
    *Sy_list = Sy_list_heap;
    len_Sy_list_heap = new int[N_follower];
    *len_Sy_list = len_Sy_list_heap;

    for(int i = 0; i < N_follower; i++)
    {
        double lam_upper = 0;
        for(double x = 0; x < T; x+=(((double)T)/10000.0))
        {
            double lam_val = lam(x, mu, gammas, influencer+i*N_influencer, *Sx_list, *len_Sx_list, N_influencer);

            if(lam_val > lam_upper)
                lam_upper = lam_val;
        }
        
        NHppp(T, lam_upper, mu, gammas, influencer+i*N_influencer, *Sx_list, *len_Sx_list, *Sy_list+i, *len_Sy_list+i, Sy_list_vec_heap+i);
    }

}


TestDataNetwork::~TestDataNetwork()
{
    for(int i = 0; i < N_influencer_heap; i++)
      delete[] Sx_list_heap[i];
    delete[] Sx_list_heap;
    delete[] len_Sx_list_heap;

    
    delete[] Sy_list_vec_heap;
    delete[] len_Sy_list_heap;
    delete[] Sy_list_heap;
}


TestDataNetwork::TestDataNetwork()
{
    std::random_device rd;
    mt = std::mt19937_64(rd());
    uniform_d = std::uniform_real_distribution<double>(0,1);
}