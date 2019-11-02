#ifndef TE_H
#define TE_H

using namespace std;

#include <map>
#include <vector>


class TransferEntropy {
    private:
        double* Sy;
        double* Sx;

        int len_Sy;
        int len_Sx;

    public:
        double HY;
        double HYX;
        
        /**
         * @brief Construct a new Transfer Entropy object
         * 
         * @param Sy -- timestamps of user Y
         * @param len_Sy -- number of timestamps of user Y
         * @param Sx -- timestamps of user X
         * @param len_Sx -- number of timestamps of user X
         */
        TransferEntropy(double* Sy, int len_Sy, double* Sx, int len_Sx);


        /**
         * @brief Computes the PT bias correction
         * 
         * @param prob_map -- probability map
         * @param denom -- total sum of all events 
         * @param k -- number of bins
         * @param pY_t_tmk --  P(Y_t, Y_(t-1), Y_(t-2), ..., Y_(t-k))
         * @return double -- PT bias
         */
        double panzeri_treves_bias(double* prob_map, double total, int k, double* pY_t_tmk);
        
        
        /**
         * @brief Computes transfer entropy from X to Y based on given probabilities
         * 
         * @param pY_t_tmk -- P(Y_t, Y_(t-1), Y_(t-2), ..., Y_(t-k))
         * @param pY_tm1_tmk -- P(Y_(t-1), Y_(t-2), ..., Y_(t-(k+1)))
         * @param pY_tm1_tmk_X_tm1_tml -- P(Y_(t-1), Y_(t-2), ..., Y_(t-k), X_(t-1), ... X_(t-l))
         * @param pY_t_tmk_X_tm1_tml -- P(Y_t, Y_(t-1), ..., Y_(t-k), X_(t-1), ... X_(t-l))
         * @param k -- number of bins for user Y
         * @return double -- transfer entropy from X to Y
         */
        double T1(double* pY_t_tmk, double* pY_tm1_tmk, double* pY_tm1_tmk_X_tm1_tml, double* pY_t_tmk_X_tm1_tml, int k);
        
        
        /**
         * @brief Computes transfer entropy from X to Y based on given probabilities
         * 
         * @param pY_t_tmk -- P(Y_t, Y_(t-1), Y_(t-2), ..., Y_(t-k))
         * @param pY_tm1_tmk -- P(Y_(t-1), Y_(t-2), ..., Y_(t-(k+1)))
         * @param pY_tm1_tmk_X_tm1_tml -- P(Y_(t-1), Y_(t-2), ..., Y_(t-k), X_(t-1), ... X_(t-l))
         * @param pY_t_tmk_X_tm1_tml -- P(Y_t, Y_(t-1), ..., Y_(t-k), X_(t-1), ... X_(t-l))
         * @param k -- number of bins 
         * @return double -- transfer entropy from X to Y
         */
        double T2(double* pY_t_tmk, double* pY_tm1_tmk, double* pY_tm1_tmk_X_tm1_tml, double* pY_t_tmk_X_tm1_tml, int k);
        
        
        /**
         * @brief Computes transfer entropy from X to Y (TE_XY)
         * 
         * @param bins --  bin widths in seconds, bin[0] = bin width at time t0, bin[1] = bin width at time t-1, bin[2] = bin width at time t-2, ...
         * @param k  -- number of bins
         * @param T --  time boundary in hours
         * @param T_func -- which function to use for TE computation
         * @param pt_bias -- Panzeri-Treves bias estimate
         * @return double -- transfer entropy from X to Y
         */
        double TE(int* binsY, int k, int T, double (TransferEntropy::*T_func)(double*, double*, double*, double*, int), double* pt_bias);

};

#endif /* TE_H */