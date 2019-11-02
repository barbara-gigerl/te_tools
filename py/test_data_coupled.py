"""Module test_data_coupled
   Generates and plots test data for TE estimations
   Users can influence each other.
"""





import numpy as np
import test_data_utils



def __lam(t, mu, gamma, St):
    if gamma == 0:
        return mu
    g_sum = sum([test_data_utils.g(t-ti) for ti in St if ti < t])
    return mu + gamma * g_sum


def __sample(T, S_own, S_other, t, mu, gamma): 
    lam_upper = max([__lam(x, mu, gamma, S_other) for x in np.linspace(0, t, num=100)])
    u = np.random.uniform()
    t = t - 1 / lam_upper * np.log(u)
    u2 = np.random.uniform()
    add_t = ((u2 <= (__lam(t, mu, gamma, S_other) / lam_upper)) and (t < T))
    return add_t, t



def get_test_data(T, mu, gamma_x, gamma_y):
    """Creates test data for users X and Y
    
    Arguments:
        T {int} -- time boundary in hours
        mu {float} -- background noise rate
        gamma_x {float} -- influence rate (How much does X influence Y?)
        gamma_y {float} -- influence rate (How much does Y influence X?)
        
    Returns:
        list -- timestamps Sx of activity of user X
        list -- timestamps Sy of activity of user Y
    """

    ty = tx = t_next = 0
    Sx = []
    Sy = []
    get_X = get_Y = True
    add_tx = add_ty = False
 
    while t_next < T:
               
        if get_X:
            if add_tx:
                Sx.append(tx)
            add_tx, tx = __sample(T, Sx, Sy, tx, mu, gamma_y)

        if get_Y:
            if add_ty:
                Sy.append(ty)
            add_ty, ty = __sample(T, Sy, Sx, ty, mu, gamma_x)

        if tx < ty:
            get_X = True
            get_Y = False
            t_next = tx
        elif ty < tx:
            get_X = False
            get_Y = True
            t_next = ty
        else:
            assert(False)

        print(t_next)

    return Sx, Sy




    

    
    

