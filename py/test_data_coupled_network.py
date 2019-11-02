"""Module test_data_network
   Generates and plots test data for TE estimations for multiple users
"""



import numpy as np
import test_data_utils



def __lam(t, whoami, mu, gammas, S, neighbors ):
    """Evaluates λ_Y(t | S_(N(Y)^t))
    
    Arguments:
        t {float} -- time boundary in hours
        whoami {int} -- id of node Y
        mu {float} -- background noise rate
        gammas {dict of int: float} -- influence rates (How much does each X influence Y?)
        S {dict of int: list of float} -- timestamps of other users
        neighbors {dict of int: list of int} -- map of which node has which other nodes as neighbors
    
    Returns:
        float -- value of function λ_Y
    """
    N_sum = 0
    for neighbor_id in range(0, len(neighbors[whoami])):
        if gammas[neighbor_id] == 0:
            continue
            
        Sx_t = S[neighbor_id]
        g_sum = sum([test_data_utils.g(t - ti) for ti in Sx_t])
        N_sum += (gammas[neighbor_id] * g_sum)
    return mu + N_sum


def __sample(T, whoami, S, neighbors, t, mu, gammas):
    """Generate a timestamp for a specific user
    
    Arguments:
        T {int} -- time boundary in hours
        whoami {int} -- id of node Y
        S {dict of int: list of float} -- timestamps of other users
        neighbors {dict of int: list of int} -- map of which node has which other nodes as neighbors
        t {float} -- time boundary in hours
        mu {float} -- background noise rate
        gammas {dict of int: float} -- influence rates (How much does each X influence Y?)
    
    Returns:
        float -- value of function λ_Y
    """
    lam_upper = max([__lam(x, whoami, mu, gammas, S, neighbors) for x in np.linspace(0, t, num=100)])
    
    u = np.random.uniform()
    t = t - 1 / lam_upper * np.log(u)
    u2 = np.random.uniform()
    
    add_t = ((u2 <= (__lam(t, whoami, mu, gammas, S, neighbors) / lam_upper)) and (t < T))
    return add_t, t




def get_test_data(T, N, mu, gammas, neighbors):
    """Creates test data for a network of N users
    
    Arguments:
        T {int} -- time boundary in hours
\_        mu {float} -- background noise rate
        gammas {dict of int: float} -- list of influence rates (How much does each X influence Y?)
        neighbors {dict of int: list of int} -- neighbor map
    
    Returns:
        dict of int: list of float -- timestamps of activities of users
    """

    t_next = 0
    t = dict.fromkeys(range(0, N), 0)
    S = {}
    for node_id in range(0, N):
        S[node_id] = []
    get_id = -1
    add_t = dict.fromkeys(range(0,N), False)
    while t_next < T:
        if get_id == -1:
            for node_id in range(0, N):
                add_t[node_id], t[node_id] =  __sample(T, node_id, S, neighbors, t[node_id], mu, gammas)
        else:
            if add_t[get_id]:
                S[get_id].append(t[get_id])
            add_t[get_id], t[get_id] = __sample(T, get_id, S, neighbors, t[get_id], mu, gammas)
        
        get_id = min(t, key=t.get)
        t_next = t[get_id]
        print(t_next)
    return S





