#ifndef TEST_DATA_NETWORK_H
#define TEST_DATA_NETWORK_H

#include <random>
#include <vector>
using namespace std;

class TestDataNetwork {

    public:

      /**
       * @brief Creates test data for a network of users
       * 
       * @param T --  time boundary in hours
       * @param lam_Sx -- activity rates of influencers
       * @param mu -- background noise rate
       * @param gammas -- influence rates of influencers
       * @param influencer -- adjacency matrix of network
       * @param N_influencer -- total number of influencer in network 
       * @param N_follower -- total number of follower in network
       * @param Sx_list -- list of generated test data for influencers
       * @param len_Sx_list  -- length of influencer test data lists
       * @param Sy_list -- list of generated test data for followers
       * @param len_Sy_list  -- length of follower test data lists
       */
      void get_test_data(int T, double* lam_Sx, double mu, double* gammas, int* influencer, int N_influencer, int N_follower, double*** Sx_list, int** len_Sx_list, double*** Sy_list, int** len_Sy_list);
      
      
      ~TestDataNetwork();
      
      
      TestDataNetwork();

    private:
      std::mt19937_64 mt;
      std::uniform_real_distribution<double> uniform_d;

      double** Sx_list_heap;
      int* len_Sx_list_heap;
      int N_influencer_heap;
      std::vector<double>* Sy_list_vec_heap;
      double** Sy_list_heap;
      int* len_Sy_list_heap;

      /**
       * @brief Evaluates λ_Y(t | S_(N(Y)^t)) 
       * 
       * @param t   -- current time in hours
       * @param mu  -- background noise rate
       * @param gammas   -- influence rates 
       * @param my_influencer  -- nodes who influence current user, eg [0,1,1,0] means that nodes 1 and 2 influence current node
       * @param Sx_list --  list of influencer test data
       * @param len_Sx_list  --  length of list of influencer test data
       * @param N_influencer -- total number of influencers
       * @return double -- function value
       */
      double lam(double t, double mu, double* gammas, int* my_influencer, double** Sx_list, int* len_Sx_list, int N_influencer);
      
      
      /**
       * @brief Non-homogeneous poisson point process
                Generates data according to NPPP 
       * 
       * @param T -- time boundary in hours
       * @param lam_upper -- maximum value of λ_Y(t | S_(N(Y)^t)) 
       * @param mu -- background noise rate
       * @param gammas -- influence rates
       * @param my_influencer -- nodes who influence current user, eg [0,1,1,0] means that nodes 1 and 2 influence current node 
       * @param Sx_list  --  list of influencer test data
       * @param len_Sx_list  --  length of list of influencer test data
       * @param Sy_list -- list of follower test data
       * @param len_Sy_list -- length of list of follower test data
       * @param Sy_vec -- list of follower test data to be generated
       */
      void NHppp(int T, double lam_upper, double mu, double* gammas, int* my_influencer, double** Sx_list, int* len_Sx_list, double**Sy_list, int* len_Sy_list, std::vector<double>* Sy_vec);

};

#endif /* TEST_DATA_NETWORK_H */