#include "test_data_utils.h"
#include "test_data_network_coupled.h"

TestDataNetworkCoupled::~TestDataNetworkCoupled()
{
    delete[] St_vec_heap;
    delete[] St_list_heap;
    delete[] len_St_list_heap;
}


TestDataNetworkCoupled::TestDataNetworkCoupled()
{
    std::random_device rd;
    mt = std::mt19937_64(rd());
    uniform_d = std::uniform_real_distribution<double>(0,1);
}

double TestDataNetworkCoupled::lam(double t, double mu, double* gammas, int* my_influencer, int N)
{
    double NY_sum = 0;

    for(int i = 0; i < N; i++)
    {
        if(my_influencer[i])
        {

            double g_sum = 0;
            std::vector<double>& St_vec = St_vec_heap[i];

            for(double ti: St_vec)
            {
                if(ti < t)
                    g_sum += g(t-ti);
            }
                        
            NY_sum += g_sum * gammas[i];
        }        
    }
    return mu + NY_sum;
}

double TestDataNetworkCoupled::sample(int T, double mu, double* gammas, double t, int* my_influencer, int N, bool* add_t)
{
    double lam_upper = 0;
    for(double x = 0; x < T; x+=(((double)T)/10000.0))
    {
        double lam_val = lam(x, mu, gammas, my_influencer, N);

        if(lam_val > lam_upper)
            lam_upper = lam_val;
    }


    double u = uniform_d(mt);
    double t_new = t - 1.0 / lam_upper * log(u);
    double u2 = uniform_d(mt);

    *add_t = ((u2 <= (lam(t_new, mu, gammas, my_influencer, N) / lam_upper)) && (t_new < T));
    return t_new;
}

void TestDataNetworkCoupled::get_test_data(int T, double mu, double* gammas, int* influencer, int N, double*** St_list, int** len_St_list)
{
    double t_next = 0;
    int get_id = -1;

    double* t = new double[N];
    std::fill_n(t, N, 0.0); 

    bool* add_t = new bool[N];
    std::fill_n(add_t, N, false);

    St_vec_heap = new std::vector<double>[N];
    for(int i = 0; i < N; i++)
    {
        St_vec_heap[i] = std::vector<double>();
    }
    
    while(t_next < T)
    {
        if(get_id == -1)
        {
            for(int node_id = 0; node_id < N; node_id++)
            {
                t[node_id] = sample(T, mu, gammas, t[node_id], influencer+node_id*N, N, add_t+node_id);
            }   
        }
        else{
            if(add_t[get_id])
            {
                St_vec_heap[get_id].emplace_back(t[get_id]);
            }
            t[get_id] = sample(T, mu, gammas, t[get_id], influencer+get_id*N, N, add_t+get_id);
        }
        get_id = std::distance(t, std::min_element(t, t+N));
        t_next = t[get_id];
        t_next = double(int(t_next*3600) / 3600.0);

    }

    St_list_heap = new double*[N];
    len_St_list_heap = new int[N];

    for(int i = 0; i < N; i++)
    {
        St_list_heap[i] = &(St_vec_heap[i])[0];
        len_St_list_heap[i] = (St_vec_heap[i]).size();
    }
    *St_list = St_list_heap;
    *len_St_list = len_St_list_heap;

    delete[] t;
    delete[] add_t;
}