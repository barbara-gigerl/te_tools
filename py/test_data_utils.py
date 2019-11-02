import numpy as np

def g(delta_t):
    return np.min([1.0, (1.0 / delta_t) ** 3])


def Hppp(T, lam):

    """Hppp - Homogeneous poisson point process
    Generates data according to HPPP 
    
    Arguments:
        T {int} -- time boundary
        lam {float} -- rate/intensity to be used in the process (λ)
    
    Returns:
        list -- List of timestamps of activities generated in the HPPP
    """
    num_points = np.random.poisson(lam=lam * T)
    return np.random.uniform(size=num_points) * T