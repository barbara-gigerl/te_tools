"""Module transfer_entropy
   Provides means to compute and plot transfer entropy
"""

import numpy as np
import binning
import matplotlib.pyplot as plt
import time


def panzeri_treves_bias(prob_map, denom, k, l):
    """Computes the PT bias correction
    
    Arguments:

    Returns:
        float -- PT bias correction
    """
    freq_map = { comb: prob_map[comb] * denom for comb in prob_map.keys() if prob_map[comb] != 0}
    freq_map = binning.eliminate_bin(freq_map, range(k, k+1))
    freq_map_Y = binning.eliminate_bin(freq_map, range(k, k+l))
    N = sum(freq_map.values())
    Nb_sum1 = sum([f[0] for f in freq_map_Y.keys()])
    
    Nb_sum1_1 = 0
    for f in freq_map_Y.keys():
        Nb_sum1_1 += f[0]
    
    Nb_sum2 = sum([f[0] for f in freq_map.keys()])

    return (-1 / (2 * N * np.log(2))) * (Nb_sum1 - Nb_sum2)
            


def T1(pY_t_tmk, pY_tm1_tmk, pY_tm1_tmk_X_tm1_tml, pY_t_tmk_X_tm1_tml, k):
    """Computes transfer entropy from X to Y based on given probabilities
    
    Arguments:
        pY_t_tmk {dict of tuple: float} -- P(Y_t, Y_(t-1), Y_(t-2), ..., Y_(t-k))
        pY_tm1_tmk {dict of tuple: float} -- P(Y_(t-1), Y_(t-2), ..., Y_(t-(k+1)))
        pY_tm1_tmk_X_tm1_tml {dict of tuple: float} -- P(Y_(t-1), Y_(t-2), ..., Y_(t-k), X_(t-1), ... X_(t-l))
        pY_t_tmk_X_tm1_tml {dict of tuple: float} --  P(Y_t, Y_(t-1), ..., Y_(t-k), X_(t-1), ... X_(t-l))
    
    Returns:
        float -- transfer entropy from X to Y
    """
    H1 = 0
    for (Yt_list, val) in pY_t_tmk.items(): #p_list: Yt, Yt-1, Yt-2, ... Yt-k

        if val == 0 or pY_tm1_tmk[Yt_list[1:]] == 0:
            continue

        pcond = val / pY_tm1_tmk[Yt_list[1:]]
        if pcond > 0:
            H1 += val * np.log(pcond)/np.log(2)
    H1 = -H1
    H2 = 0
    for (YtXt_list, val) in pY_t_tmk_X_tm1_tml.items():

        if val == 0 or pY_tm1_tmk_X_tm1_tml[YtXt_list[1:]] == 0:
            continue

        pcond = val / pY_tm1_tmk_X_tm1_tml[YtXt_list[1:]]

        if pcond > 0:
            H2 += val * ((np.log(pcond)/np.log(2)) if pcond else 0)
    H2 = -H2

    res = H1 - H2
    return res if res > 0 else 0 

   
def T2(pY_t_tmk, pY_tm1_tmk, pY_tm1_tmk_X_tm1_tml, pY_t_tmk_X_tm1_tml, k):
    """Computes transfer entropy from X to Y based on given probabilities
    
    Arguments:
        pY_t_tmk {dict of tuple: float} -- P(Y_t, Y_(t-1), Y_(t-2), ..., Y_(t-k))
        pY_tm1_tmk {dict of tuple: float} -- P(Y_(t-1), Y_(t-2), ..., Y_(t-(k+1)))
        pY_tm1_tmk_X_tm1_tml {dict of tuple: float} -- P(Y_(t-1), Y_(t-2), ..., Y_(t-k), X_(t-1), ... X_(t-l))
        pY_t_tmk_X_tm1_tml {dict of tuple: float} --  P(Y_t, Y_(t-1), ..., Y_(t-k), X_(t-1), ... X_(t-l))

    Returns:
        float -- transfer entropy from X to Y
    """
    T = 0
    for (YtXt_list, val) in pY_t_tmk_X_tm1_tml.items():
        Yt_list = YtXt_list[:k]
        logval1 = (val * pY_tm1_tmk[Yt_list[1:]])
        logval2 = (pY_tm1_tmk_X_tm1_tml[YtXt_list[1:]]*pY_t_tmk[Yt_list])
        if logval1 == 0 or logval2 == 0:
            continue
        logval = logval1 / logval2
        T += val * np.log(logval)/np.log(2)

    return T


def TE(Sy, Sx, bins, T, T_func):
    """Computes transfer entropy from X to Y (TE_XY)
    
    Arguments:
        Sy {list of float} -- timestamps of user Y
        Sx {list of float} -- timestamps of user X
        bins {list of int} -- bin widths in seconds, bin[0] = bin width at time t0, bin[1] = bin width at time t-1, bin[2] = bin width at time t-2, ...
        T {int} -- time boundary in hours
        T_func {function} -- which function to use for TE computation
    
    Returns:
        float -- transfer entropy from X to Y
        float -- bias estimation
    """
    Sx.sort()
    Sy.sort()
    k = len(bins)
    prob_map, total = binning.compute_binning(Sy, Sx, bins, T)
    binsX_indices = list(range(k, 2*k))
    pY_t_tmk_X_tm1_tml = binning.eliminate_bin(prob_map, [binsX_indices[0]])
    
    pY_tm1_tmk_X_tm1_tml = binning.eliminate_bin(prob_map, [0]+[binsX_indices[0]])
    pY_t_tmk = binning.eliminate_bin(prob_map, binsX_indices)
    pY_tm1_tmk = binning.eliminate_bin(prob_map, [0]+binsX_indices)
    pt_bias = panzeri_treves_bias(prob_map, total, len(bins), len(bins))

    te = T_func(pY_t_tmk, pY_tm1_tmk, pY_tm1_tmk_X_tm1_tml, pY_t_tmk_X_tm1_tml, k)
    return te, pt_bias
    
