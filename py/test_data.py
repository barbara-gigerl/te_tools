"""Module test_data
   Generates and plots test data for TE estimations
"""




import numpy as np
import test_data_utils




def __lam(t, mu, gamma, Sx):
    g_sum = sum([test_data_utils.g(t-ti) for ti in Sx if ti < t])
    return mu + gamma * g_sum


def NHppp(T, lam_upper, mu, gamma, Sx):
    """NPPP - Non-homogeneous poisson point process
    Generates data according to NPPP 

    Arguments:
        T {int} -- time boundary
        lam_upper {float} -- maximum of function lamY
        mu {float} -- background noise rate
        gamma {float} -- influence rate (How much does X influence Y?)
        Sx {list} -- timestamps of activity of user X
    
    Returns:
        list -- timestamps of activity of user Y
    """
    
    assert(lam_upper > 0)
    t = 0
    ts = []
    

    ulist1 = []
    ulist2 = []

    while t < T:
        u = np.random.uniform()
        ulist1.append(u)
        t = t - 1 / lam_upper * np.log(u)
        u2 = np.random.uniform()
        ulist2.append(u2)
        
        if u2 <= (__lam(t, mu, gamma, Sx) / lam_upper):
            if t < T:
                ts.append(t)


    return ts




def get_test_data(T, lam_x, mu, gamma, f=1.0, Sx=None):
    """Creates test data for users X and Y
    
    Arguments:
        T {int} -- time boundary in hours
        lam_x {float} -- λ used for generating X data 
        mu {float} -- background noise rate
        gamma {float} -- influence rate (How much does X influence Y?)
    
    Keyword Arguments:
        f {float} -- sampling parameter (How much of X data should be kept?) (default: {1.0}, means "all")
        Sx {list} -- timestamps of activity of user X, if not given it is generated
    
    Returns:
        list -- timestamps Sx of activity of user X in hours
        list -- timestamps Sy of activity of user Y in hours
    """
    if Sx == None:
        Sx = test_data_utils.Hppp(T, lam_x)
    
    if f!= 1.0:
        Sx_n = int(np.round(len(Sx) * f))
        Sx = np.random.choice(Sx, Sx_n)

    lam_upper = max([__lam(x, mu, gamma, Sx) for x in np.linspace(0, T, num=1000)])
    Sy = NHppp(T, lam_upper, mu, gamma, Sx)
    return Sx, Sy


