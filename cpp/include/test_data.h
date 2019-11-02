#ifndef TEST_DATA_H
#define TEST_DATA_H

using namespace std;

#include <map>
#include <vector>


class TestData {
    public:
        /**
         * @brief Creates test data for users X and Y
         * 
         * @param T -- time boundary in hours
         * @param lam_x -- activity rate of user X
         * @param mu  -- background noise rate
         * @param gamma -- influence rate of user X
         * @param Sx-- timestamps Sx of activity of user X
         * @param len_Sx  -- length of Sx
         * @param Sy  -- timestamps Sy of activity of user Y
         * @param len_Sy  -- length of Sy
         */
        void get_test_data(int T, double lam_x, double mu, double gamma, double** Sx, int* len_Sx, double** Sy, int* len_Sy);
        
        
        ~TestData();

    private:
        std::vector<double>* Sy_vec_heap;
        double* Sx_heap;


        /**
         * @brief  Evaluates λ_Y(t | S_(N(Y)^t))
         * 
         * @param t -- current time in hours
         * @param mu -- background noise rate
         * @param gamma -- influence rate 
         * @param Sx --  timestamps oof user X
         * @param len_Sx -- length of timestamps of user X
         * @return double -- function value
         */
        double lam(double t, double mu, double gamma, double* Sx, int len_Sx);
        
        
        /**
         * @brief Non-homogeneous poisson point process
                  Generates data according to NPPP
         * 
         * @param T  -- time boundary in hours
         * @param lam_upper -- maximum value of λ_Y(t | S_(N(Y)^t)) 
         * @param mu -- background noise rate
         * @param gamma  -- influence rates
         * @param Sx   --  list of timestamps of user X
         * @param len_Sx  -- length of timestamp list of user X
         * @param Sy   --  list of timestamps of user X
         * @param len_Sy  -- length of timestamp list of user X
         */
        void NHppp(int T, double lam_upper, double mu, double gamma, double* Sx, int len_Sx, double** Sy, int* len_Sy);

};

#endif /* TEST_DATA_H */