"""Module binning
   Converts a list of timestamps into a binned RV
"""



import numpy as np
import itertools
import time
from decimal import Decimal, ROUND_HALF_UP





def get_logarithmic_bins(start, divisor, n):
    """Returns a list of logarithmicaly distributed bin widths
       Example: start=20, divisor=2, n=3 returns [5,10,20]
    
    Arguments:
        start {int} -- width of largest bin
        divisor {int} -- bin width decrement
        n {int} -- number of bins

    Returns:
        list of int -- bin widths
    """
    bin_width = start
    bins = []
    for i in range(0, n):
        bins.append(int(Decimal(bin_width).to_integral_value(rounding=ROUND_HALF_UP)))
        bin_width = bin_width / divisor
    bins.reverse()
    return bins
    

def get_equal_bins(width, n):
    """Returns a list of equally sized bins with a constant width
       Example: width=4, n=3 returns [4,4,4,4]
    
    Arguments:
        width {int} -- width of bin
        n {int} -- number of bins to generate
    
    Returns:
        list of int -- bin widths
    """
    return [width] * n


def get_linear_bins(start, stop, step):
    """Returns a list bins with a change in size step.
    The smallest bin has size start, the largest bin has size stop.
    
    Arguments:
        start {int} -- size of largest bin
        stop {int} -- size of smallest bin
        step {int} -- size difference between each two bins
    
    Returns:
        list of int -- bin widths
    """
    return np.arange(start=start, stop=stop, step=step).tolist()


def compute_binning(Sy, Sx, bins, T):
    """Computes probability P(Yt, Yt-1, ... Yt-k, Xt-1, ... Xt-l)
    
    Arguments:
        Sy {list of int} -- timestamp list of user Y, S[0] = timestamp at time t0, S[1] = timestamp at time t1, ...
        Sx {list of int} -- timestamp list of user X, S[0] = timestamp at time t0, S[1] = timestamp at time t1, ...
        bins {list of int} -- bin widths in seconds, bin[0] = bin width at time t0, bin[1] = bin width at time t-1, bin[2] = bin width at time t-2, ...
        T {int} -- upper time boundary
    
    Returns:
        dict of tuple: float -- probability map, key: (Yt, Yt-1, Yt-2, ... Yt-k, Xt-1, Xt-2, ... X-l)
    """
    w = sum(bins)
    p = dict.fromkeys(itertools.product([1,0], repeat=len(bins)*2), 0)
    Sy = sorted(Sy)
    Sx = sorted(Sx)
    S_total = sorted(Sy + Sx)

    idxY = idxX = 0

    for idx in range(0, len(S_total)):
        val = S_total[idx]
       

        for i in range(val-w+1, val+1):

            if i+w == T+2:
                break
            
            if i < 0:
                continue
            

            if idx > 0 and i <= S_total[idx-1] < i+w:
                
                continue

            comb = [0] * (len(bins) * 2)

            idxY_tmp = idxY
            while idxY_tmp < len(Sy) and Sy[idxY_tmp] < (i+w):
                sumbins = 0
                for bin_idx in range(len(bins)-1, -1, -1):
                    if(i + sumbins) <= Sy[idxY_tmp] < (i + sumbins + bins[bin_idx]):
                        comb[bin_idx] = 1
                    sumbins += bins[bin_idx]
                idxY_tmp +=1
            
            idxX_tmp = idxX
            while idxX_tmp < len(Sx) and Sx[idxX_tmp] < (i+w):
                sumbins = 0
                for bin_idx in range(len(bins)-1, -1, -1):
                    if(i+ sumbins) <= Sx[idxX_tmp] < (i+sumbins+bins[bin_idx]):
                        comb[bin_idx+len(bins)] = 1
                    sumbins += bins[bin_idx]
                idxX_tmp +=1

            p [tuple(comb)] += 1

        if idxY < len(Sy) and S_total[idx] == Sy[idxY]:
            idxY+=1
        elif idxX < len(Sx) and S_total[idx] == Sx[idxX]:
            idxX+=1
        else:
            assert(False)
    p_sum = sum(p.values())
    p[tuple([0]*len(bins)*2)] = T - w - p_sum + 2
    total = T - w + 2
    return {k: v / total for k, v in p.items()}, total                

def eliminate_bin(p, eliminate_bins):
    """Marginalizes probability distribution by eliminating bins with indices in eliminate_bins

    Arguments:
        p {dictionary of tuple: float} -- probability map
        eliminate_bins {list of int} -- indices of bins to be eliminated, for exmample: bins = [1,2,3], eliminate_bins = [0] gives new bins = [2,3]
    
    Returns:
        p_eliminated {dictionary of tuple: float} -- probability map
    """
    p_eliminated = {}
    for comb in p:
        comb_eliminated = tuple([ comb[i] for i in range(0, len(comb)) if i not in eliminate_bins])
        
        p_eliminated[comb_eliminated] = p[comb] if comb_eliminated not in p_eliminated else p[comb] +  p_eliminated[comb_eliminated]
    return p_eliminated
