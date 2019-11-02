#ifndef TEST_DATA_NETWORK_COUPLED_H
#define TEST_DATA_NETWORK_COUPLED_H

#include <random>
#include <vector>
using namespace std;

class TestDataNetworkCoupled {

    public:
      /**
       * @brief Creates test data for a network of users
       * 
       * @param T -- time boundary in hours
       * @param mu -- background noise rate
       * @param gammas  -- influence rates of all users
       * @param influencer -- adjacency matrix of network
       * @param N -- total number of nodes in network
       * @param St_list -- list of generated test data
       * @param len_St_list -- length of test data lists
       */
      void get_test_data(int T, double mu, double* gammas, int* influencer, int N, double*** St_list, int** len_St_list);
      
      
      ~TestDataNetworkCoupled();
      
      
      TestDataNetworkCoupled();

    private:
      std::mt19937_64 mt;
      std::uniform_real_distribution<double> uniform_d;

      std::vector<double>* St_vec_heap;
      double** St_list_heap;
      int* len_St_list_heap;


      /**
       * @brief Evaluates λ_Y(t | S_(N(Y)^t))
       * 
       * @param t  -- current time in hours
       * @param mu  -- background noise rate
       * @param gammas  -- influence rates 
       * @param my_influencer -- nodes who influence current user, eg [0,1,1,0] means that nodes 1 and 2 influence current node
       * @param N -- total number of nodes in network
       * @return double -- function value
       */
      double lam(double t, double mu, double* gammas, int* my_influencer, int N);
      
      
      /**
       * @brief Generate a timestamp for a specific user
       * 
       * @param T  -- time boundary in hours
       * @param mu -- background noise rate
       * @param gammas  -- influence rates
       * @param t  -- current time in hours
       * @param my_influencer -- nodes who influence current user, eg [0,1,1,0] means that nodes 1 and 2 influence current node
       * @param N -- total number of nodes in network
       * @param add_t  -- tells if t should be added to list afterwards
       * @return double -- the newly generated timestamp t
       */
      double sample(int T, double mu, double* gammas, double t, int* my_influencer, int N, bool* add_t);


};


#endif /* TEST_DATA_NETWORK_COUPLED_H */