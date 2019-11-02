#ifndef TEST_DATA_COUPLED_H
#define TEST_DATA_COUPLED_H

using namespace std;

#include <vector>
#include <random>

class TestDataCoupled {
    public:
        /**
         * @brief Creates test data for users X and Y
         * 
         * @param T -- time boundary in hours
         * @param mu -- background noise rate
         * @param gamma_x -- influence rate (How much does X influence Y?)
         * @param gamma_y -- influence rate (How much does Y influence X?)
         * @param Sx -- timestamps Sx of activity of user X
         * @param len_Sx  -- length of Sx
         * @param Sy -- timestamps Sy of activity of user Y
         * @param len_Sy -- length of Sy
         */
        void get_test_data(int T, double mu, double gamma_x, double gamma_y, double** Sx, int* len_Sx, double** Sy, int* len_Sy);


        ~TestDataCoupled();


        TestDataCoupled();


    private:
        std::vector<double>* Sy_vec_heap;
        std::vector<double>* Sx_vec_heap;
        std::mt19937_64 mt;
        std::uniform_real_distribution<double> uniform_d;

        /**
         * @brief Generate a timestamp for a specific user
         * 
         * @param T -- time boundary in hours
         * @param S_own -- timestamps of own user
         * @param S_other -- timestamps of other user
         * @param t -- current time in hours
         * @param mu -- background noise rate
         * @param gamma -- influence rate (How much does other user influence own user?)
         * @param add_t -- tells if t should be added to list afterwards
         * @return double -- the newly generated timestamp t
         */
        double sample(int T, std::vector<double>& S_own, std::vector<double>& S_other, double t, double mu, double gamma, bool* add_t);
        

        /**
         * @brief Evaluates λ_Y(t | S_(N(Y)^t))
         * 
         * @param t -- current time in hours
         * @param mu -- background noise rate
         * @param gamma -- influence rate 
         * @param St --  timestamps
         * @return double -- function value
         */
        double lam(double t, double mu, double gamma, std::vector<double>& St);


};

#endif /* TEST_DATA_COUPLED_H */