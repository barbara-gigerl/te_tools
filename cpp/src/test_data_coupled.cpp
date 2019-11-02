#include "test_data_coupled.h"
#include "test_data_utils.h"


TestDataCoupled::TestDataCoupled()
{
    std::random_device rd;
    mt = std::mt19937_64(rd());
    uniform_d = std::uniform_real_distribution<double>(0,1);

}
double TestDataCoupled::lam(double t, double mu, double gamma, std::vector<double>& St)
{
    if(gamma == 0)
        return mu;
    
    double g_sum = 0;

    for (double ti: St)
    {  
        if(ti < t)
          g_sum += g(t-ti);
    }    
    return mu + gamma * g_sum;
}

double TestDataCoupled::sample(int T, std::vector<double>& S_own, std::vector<double>& S_other, double t, double mu, double gamma, bool* add_t)
{
    double lam_upper = 0;
    for(double x = 0; x < T; x+=(((double)T)/10000.0))
    {
        double lam_val = lam(x, mu, gamma, S_other);

        if(lam_val > lam_upper)
            lam_upper = lam_val;
    }

    double u = uniform_d(mt);
    double t_new = t - 1.0 / lam_upper * log(u);
    double u2 = uniform_d(mt);
    *add_t = ((u2 <= (lam(t_new, mu, gamma, S_other) / lam_upper)) && (t_new < T));
    return t_new;
}


void TestDataCoupled::get_test_data(int T, double mu, double gamma_x, double gamma_y, double** Sx, int* len_Sx, double** Sy, int* len_Sy)
{
    double ty = 0.0, tx = 0.0, t_next = 0.0;
    std::vector<double>* Sy_vec = new vector<double>();
    std::vector<double>* Sx_vec = new vector<double>();
    bool get_X = true, get_Y = true;
    bool add_tx = false, add_ty = false;

    while(t_next < T)
    {
       
        if(get_X)
        {
            if(add_tx)
              Sx_vec->emplace_back(tx);
            tx = sample(T, *Sx_vec, *Sy_vec, tx, mu, gamma_y, &add_tx);
        }
        


        if(get_Y)
        {
            if(add_ty)
              Sy_vec->emplace_back(ty);
            ty = sample(T, *Sy_vec, *Sx_vec, ty, mu, gamma_x, &add_ty);
        }

        if(tx < ty)
        {
            get_X = true;
            get_Y = false;
            t_next = tx;
        }
        else if (ty < tx)
        {
            get_X = false;
            get_Y = true;
            t_next = ty;
        }
        else{
            cout << "ABORT: ty == tx" << endl;
            exit(-1);
        }
        t_next = double(int(t_next*3600) / 3600.0);
    }

    *Sy = &(*Sy_vec)[0];
    *len_Sy = (*Sy_vec).size();
    *Sx = &(*Sx_vec)[0];
    *len_Sx = (*Sx_vec).size();

    Sy_vec_heap = Sy_vec;
    Sx_vec_heap = Sx_vec;
}


TestDataCoupled::~TestDataCoupled()
{
    delete Sy_vec_heap;
    delete Sx_vec_heap;
}