#ifndef BINNING_H
#define BINNING_H

using namespace std;

#include <map>
#include <vector>


class Binning {
    private: 

        double* prob_map;
        int k;
        
    public:
    
        /**
         * @brief Returns a list of logarithmically distributed bin widths
                  Example: start=20, divisor=2, n=3 returns [5,10,20]
         * 
         * @param start -- width of largest bin
         * @param divisor -- bin width decrement
         * @param n -- number of bins
         * @param bins -- array of size n to store the bins
         */
        static void get_logarithmic_bins(int start, int divisor, int n, int* bins);
        
        
        /**
         * @brief Returns a list of equally sized bins with a constant width
                  Example: width=4, n=3 returns [4,4,4,4]
         * 
         * @param width -- width of bin
         * @param n -- number of bins to generate
         * @param bins -- array of size n to store the bins
         */
        static void get_equal_bins(int width, int n, int* bins);


        /**
         * @brief Returns a list bins with a change in size step.
                  The smallest bin has size start, the largest bin has size stop.
         * 
         * @param start -- size of largest bin
         * @param stop -- size of smallest bin
         * @param step  -- size difference between each two bins
         * @param bins  -- array of size n to store the bins
         */
        static void get_linear_bins(int start, int stop, int step, int* bins);
        

        /**
         * @brief Computes probability P(Yt, Yt-1, ... Yt-k, Xt-1, ... Xt-l)
         * 
         * @param Sy -- timestamps of user Y, S[0] = timestamp at time t0, S[1] = timestamp at time t1, ...
         * @param len_Sy -- length of Sy
         * @param Sx -- timestamp list of user X, S[0] = timestamp at time t0, S[1] = timestamp at time t1, ...
         * @param len_Sx -- length of Sx
         * @param bins -- bin widths in seconds, bin[0] = bin width at time t0, bin[1] = bin width at time t-1, bin[2] = bin width at time t-2, ...
         * @param k -- number of bins (length of bins)
         * @param T -- upper time boundary
         * @return int -- total sum of all events (used to normalize probability map)
         */
        long compute_binning(double* Sy, int len_Sy, double* Sx, int len_Sx, int* bins, int k, int T);
        

        /**
         * @brief Marginalizes probability distribution by eliminating bins with indices in eliminate_bins
         * 
         * @param eliminate_bins -- indices of bins to be eliminated in form of a bit mask, for example: bins = [1,2,3], eliminate_bins = 0 gives new bins = [2,3]
         * @param reduced_prob_map -- reduced probability map
         * @param prob_map [optional] -- probability map used for computations. if unused, the member variable is considered
         */
        void eliminate_bin(int eliminate_bins, double* reduced_prob_map);
        void eliminate_bin(int eliminate_bins, double* reduced_prob_map, double* prob_map);


        /**
         * @brief Get the prob map object
         * 
         * @return double* 
         */
        double* get_prob_map() {return prob_map; }

        ~Binning();
};

#endif /* BINNING_H */
