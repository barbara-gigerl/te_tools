"""Module test_data_network
   Generates and plots test data for TE estimations for multiple users
"""

import numpy as np
import test_data_utils



def __lamY(t, mu, gammas, Sx_list, influencer_ids):
    """Evaluates λ_Y(t | S_(N(Y)^t))
    
    Arguments:
        t {float} -- time boundary in hours
        mu {float} -- background noise rate
        gammas {list of float} -- list of influence rates (How much does each X influence Y?)
        Sx_list {dict of int: list of float} -- timestamps Sx of activity of users X (influencers)
        influencer_ids {list of int} --- list of ids of neighbors of Y
    Returns:
        float -- value of function λ_Y
    """
    NY_sum = 0

    for i in influencer_ids:
        Sx_t = [tx for tx in Sx_list[i] if tx < t]
        g_sum = sum([test_data_utils.g(t - ti) for ti in Sx_t if ti < t])
        NY_sum += (gammas[i] * g_sum)
    
    return mu + NY_sum


def NHppp(T, lam_upper, mu, gammas, Sx_list, influencer_ids):
    """NPPP - Non-homogeneous poisson point process
    Generates data according to NPPP 

    Arguments:
        T {int} -- time boundary
        lam_upper {float} -- maximum of function lamY
        mu {float} -- background noise rate
        gammas {dict of int: float} -- list of influence rates (How much does each X influence Y?)
        Sx_list {list of list of float} -- timestamps Sx of activity of users X (influencers)
        influencer_ids {list of int} -- ids of influencers/neighbors of Y
    
    Returns:
        list -- timestamps of activity of user Y
    """
    
    t = 0
    ts = []
    while t < T:
        u = np.random.uniform()
        t = t - 1 / lam_upper * np.log(u)
        u2 = np.random.uniform()
        
        if u2 <= (__lamY(t, mu, gammas, Sx_list, influencer_ids) / lam_upper):
            if t < T:
                ts.append(t)
    return ts



def get_test_data(T, lam_Sx, mu, gammas, influencer):
    """Creates test data for a network of users
    
    Arguments:
        T {int} -- time boundary in hours
        lam_Sx {dict of int: float} -- λ used for generating data for users X (influencers) 
        mu {float} -- background noise rate
        gammas {dict of int: float} -- list of influence rates (How much does each X influence Y?)
        influencer {dict of int: list of int} -- neighbor map for the whole network mapping Y user ids (follower) to X user ids (influencer)

    Returns:
        list of list of float -- timestamps Sx of activity of users X (influencers)
        list of list of float -- timestamps Sy of activity of users Y (followers)
    """
    influencer_ids = gammas.keys()
    follower_ids = influencer.keys()

    Sx_list = {}
    for i in influencer_ids:
        Sx_list[i] = test_data_utils.Hppp(T, lam_Sx[i])

    Sy_list = {}
    for i in follower_ids:
        lam_upper = max([__lamY(x, mu, gammas, Sx_list, influencer[i]) for x in np.linspace(0, T, num=1000)])
        Sy_list[i] = NHppp(T, lam_upper, mu, gammas, Sx_list, influencer[i])

    return Sx_list, Sy_list







