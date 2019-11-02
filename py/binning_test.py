import unittest
from binning import compute_binning, eliminate_bin, get_logarithmic_bins
from time import time

class TestBinning(unittest.TestCase):

    

    def test_bin_1(self):
        Sy = [1, 5, 9, 17, 22, 29]
        Sx = [1, 5, 9, 17, 22, 29]
        bins = [1, 2, 3]
        T = 30
        res, total = compute_binning(Sy, Sx, bins, T)

        self.assertEqual(total, 26)
        self.assertEqual(res[(0, 0, 0, 0, 0, 0)], 3.0/26)
        self.assertEqual(res[(0, 1, 0, 0, 1, 0)], 7.0/26)
        self.assertEqual(res[(0, 1, 1, 0, 1, 1)], 2.0/26)
        self.assertEqual(res[(1, 0, 0, 1, 0, 0)], 2.0/26)
        self.assertEqual(res[(0, 0, 1, 0, 0, 1)], 9.0/26)
        self.assertEqual(res[(1, 0, 1, 1, 0, 1)], 3.0/26)

        
        pY_t_tmk = eliminate_bin(res, [3,4,5])

        pY_tm1_tmk = eliminate_bin(res, [0, 3,4,5]) #ignore bin[0]
        
        self.assertEqual(pY_t_tmk[((1, 0, 1))], 3.0/26.0)
        self.assertEqual(pY_t_tmk[((0, 1, 1))], 2.0/26.0)
        self.assertEqual(pY_t_tmk[((0, 1, 0))], 7.0/26.0)
        self.assertEqual(pY_t_tmk[((0, 0, 1))], 9.0/26.0)
        self.assertEqual(pY_t_tmk[((0, 0, 0))], 3.0/26.0)
        self.assertEqual(pY_t_tmk[((1, 0, 0))], 2.0/26.0)

        self.assertEqual(pY_tm1_tmk[((0, 1))], 12.0/26.0)
        self.assertEqual(pY_tm1_tmk[((1, 1))], 2.0/26.0)
        self.assertEqual(pY_tm1_tmk[((1, 0))], 7.0/26.0)
        self.assertEqual(pY_tm1_tmk[((0, 0))], 5.0/26.0)


    def test_bin_2(self):
        St = [1, 5, 9, 17, 22, 29]
        bins = [1]
        T = 30
        res, total = compute_binning(St, [], bins, T)
        self.assertEqual(total, 31)
        self.assertEqual(res[(1, 0)], 6.0/31.0)
        self.assertEqual(res[(0, 0)], 25.0/31.0)
        res = eliminate_bin(res, [1])
        self.assertEqual(res[((0,))], 25.0/31.0)
        self.assertEqual(res[((1,))], 6.0/31.0)
    
    def test_bin_3(self):
        St = [10, 20, 30, 40]
        bins = [4,4,4,4]
        T = 50
        res, total = compute_binning(St, [], bins, T)
        
        self.assertEqual(total, 36)
        self.assertEqual(res[(1, 0, 0, 1, 0, 0, 0, 0)], 6.0/36.0)
        self.assertEqual(res[(0, 1, 0, 1, 0, 0, 0, 0)], 6.0/36.0)
        self.assertEqual(res[(0, 0, 1, 0, 0, 0, 0, 0)], 9.0/36.0)
        self.assertEqual(res[(0, 1, 0, 0, 0, 0, 0, 0)], 9.0/36.0)
        self.assertEqual(res[(1, 0, 1, 0, 0, 0, 0, 0)], 6.0/36.0)
        res = eliminate_bin(res, [4,5,6,7])
        self.assertEqual(res[((0, 0, 1, 0))], 9.0/36.0)
        self.assertEqual(res[((0, 1, 0, 0))], 9.0/36.0)
        self.assertEqual(res[((1, 0, 1, 0))], 6.0/36.0)
        self.assertEqual(res[((1, 0, 0, 1))], 6.0/36.0)
        self.assertEqual(res[((0, 1, 0, 1))], 6.0/36.0)

    def test_bin_4(self):
        St = [10, 15, 20, 25, 30, 35, 40]
        bins = [1,4]
        T = 50
        k = l = 2
        res, total = compute_binning(St, [], bins, T)
        
        self.assertEqual(total, 47)
        self.assertEqual(res[(0, 0, 0, 0)], 12.0/47.0)
        self.assertEqual(res[(0, 1, 0, 0)], 28.0/47.0)
        self.assertEqual(res[(1, 0, 0, 0)], 7.0/47.0)
        res = eliminate_bin(res, [2,3])
        self.assertEqual(res[((0,0))], 12.0/47.0)
        self.assertEqual(res[((1,0))], 7.0/47.0)
        self.assertEqual(res[((0,1))], 28.0/47.0)

    def test_bin_5(self):
        St = [1, 5, 5, 5, 9, 9, 17, 17, 22, 29]
        bins = [1,4]
        T = 30
        res, total = compute_binning(St, [], bins, T)
        
        self.assertEqual(total, 27)
        self.assertEqual(res[(1, 1, 0, 0)], 2.0/27)
        self.assertEqual(res[(0, 0, 0, 0)], 5.0/27)
        self.assertEqual(res[(0, 1, 0, 0)], 17.0/27)
        self.assertEqual(res[(1, 0, 0, 0)], 3.0/27)

        res = eliminate_bin(res, [2,3])
        self.assertEqual(res[((0, 1))], 17.0/27.0)
        self.assertEqual(res[((1, 1))], 2.0/27.0)
        self.assertEqual(res[((0, 0))], 5.0/27.0)
        self.assertEqual(res[((1, 0))], 3.0/27.0)

    def test_bin_6(self):
        St = [1, 2, 9, 10, 14, 15, 19, 21, 22, 27, 28, 29]
        bins = [4,1]
        T = 30
        res, total = compute_binning(St, [], bins, T)
        
        self.assertEqual(total, 27)
        self.assertEqual(res[(1, 1, 0, 0)], 7.0/27.0)
        self.assertEqual(res[(0, 0, 0, 0)], 2.0/27.0)
        self.assertEqual(res[(0, 1, 0, 0)], 2.0/27.0)
        self.assertEqual(res[(1, 0, 0, 0)], 16.0/27.0)

        res = eliminate_bin(res, [2,3])
        self.assertEqual(res[((1, 0))], 16.0/27.0)
        self.assertEqual(res[((1, 1))], 7.0/27.0)
        self.assertEqual(res[(0, 1)], 2.0/27.0)
        self.assertEqual(res[((0, 0))], 2.0/27.0)

    def test_bin_7(self):
        St = [6, 7, 9, 11, 19, 20, 21, 22, 23, 25, 29, 35, 36, 37, 42, 49, 52, 53, 57, 58]
        bins = [5,3,9]
        T = 60
        res, total = compute_binning(St, [], bins, T)
        
        self.assertEqual(total, 45)
        self.assertEqual(res[(1, 0, 1, 0, 0, 0)], 15.0/45.0)
        self.assertEqual(res[(0, 1, 1, 0, 0, 0)], 6.0/45.0)
        self.assertEqual(res[(1, 1, 1, 0, 0, 0)], 24.0/45.0)
        res = eliminate_bin(res, [3,4,5])
        self.assertEqual(res[((0, 1, 1))], 6.0/45.0)
        self.assertEqual(res[((1, 0, 1))], 15.0/45.0)
        self.assertEqual(res[((1, 1, 1))], 24.0/45.0)


    def test_bin_8(self):
        St =[0, 1, 2, 3, 4, 7, 9, 11, 12, 21, 24, 25, 28, 32, 36, 41, 43, 46, 47, 48, 50, 53]
        bins = [1,1,1]
        T = 60
        res, total = compute_binning(St, [], bins, T)
        
        self.assertEqual(total, 59)
        self.assertEqual(res[(1, 0, 1, 0, 0, 0)], 4.0/59)
        self.assertEqual(res[(0, 0, 0, 0, 0, 0)], 15.0/59)
        self.assertEqual(res[(1, 1, 1, 0, 0, 0)], 4.0/59)
        self.assertEqual(res[(1, 1, 0, 0, 0, 0)], 3.0/59)
        self.assertEqual(res[(0, 0, 1, 0, 0, 0)], 10.0/59)
        self.assertEqual(res[(1, 0, 0, 0, 0, 0)], 9.0/59)
        self.assertEqual(res[(0, 1, 0, 0, 0, 0)], 10.0/59)
        self.assertEqual(res[(0, 1, 1, 0, 0, 0)], 4.0/59)

        res = eliminate_bin(res, [3,4,5])
        self.assertEqual(res[((1, 1, 1))], 4.0/59)
        self.assertEqual(res[((0, 1, 1))], 4.0/59)
        self.assertEqual(res[((0, 0, 1))], 10.0/59)
        self.assertEqual(res[((1, 0, 0))], 9.0/59)
        self.assertEqual(res[((0, 1, 0))], 10.0/59)
        self.assertEqual(res[((1, 0, 1))], 4.0/59)
        self.assertEqual(res[((1, 1, 0))], 3.0/59)
        self.assertEqual(res[((0, 0, 0))], 15.0/59)
    
    def test_bin_9(self):
        St = [0, 2, 3, 5, 13, 14, 15, 19, 22, 24, 26, 27, 31, 33, 34, 35, 36, 44, 46, 48, 50, 52, 53]

        bins = [1,9,7]
        T = 60
        res, total = compute_binning(St, [], bins, T)
        
        self.assertEqual(total, 45)
        self.assertEqual(res[(0, 1, 1, 0, 0, 0)], 29.0/45)
        self.assertEqual(res[(1, 1, 1, 0, 0, 0)], 14.0/45)
        self.assertEqual(res[(1, 1, 0, 0, 0, 0)], 2.0/45)
        res = eliminate_bin(res, [3,4,5])
        self.assertEqual(res[((0, 1, 1))], 29.0/45)
        self.assertEqual(res[((1, 1, 1))], 14.0/45)
        self.assertEqual(res[((1, 1, 0))], 2.0/45)

   
    def test_bin_10(self):
        bins = get_logarithmic_bins(20, 2, 4)
        self.assertEqual(bins, [3, 5, 10, 20])

    def test_bin_11(self):
        St = [13, 16, 17, 18]
        bins = [1,2,3]
        T = 20
        res, total = compute_binning(St, St, bins, T)
        
        self.assertEqual(total,16)
        self.assertEqual(res[(0, 0, 0, 0, 0, 0)], 8.0/16)
        self.assertEqual(res[(0, 1, 0, 0, 1, 0)], 2.0/16)
        self.assertEqual(res[(0, 1, 1, 0, 1, 1)], 2.0/16)
        self.assertEqual(res[(1, 0, 0, 1, 0, 0)], 1.0/16)
        self.assertEqual(res[(1, 0, 1, 1, 0, 1)], 1.0/16)
        self.assertEqual(res[(1, 1, 1, 1, 1, 1)], 2.0/16)
        res = eliminate_bin(res, [3,4,5])
        self.assertEqual(res[(1, 1, 1)],  2.0/16)
        self.assertEqual(res[(1, 0, 1)],  1.0/16)
        self.assertEqual(res[(1, 0, 0)],  1.0/16) 
        self.assertEqual(res[(0, 1, 1)],  2.0/16)
        self.assertEqual(res[(0, 1, 0)],  2.0/16)
        self.assertEqual(res[(0, 0, 0)],  8.0/16)
      

    def test_bin_12(self): 
        St = [5, 10, 15]
        bins = [1,1,1]
        T = 20
        res, total = compute_binning(St, St, bins, T)
        
        self.assertEqual(total, 19)
        self.assertEqual(res[(1, 0, 0, 1, 0, 0)], 3.0/19)
        self.assertEqual(res[(0, 1, 0, 0, 1, 0)], 3.0/19)
        self.assertEqual(res[(0, 0, 0, 0, 0, 0)], 10.0/19)
        self.assertEqual(res[(0, 0, 1, 0, 0, 1)], 3.0/19)

    def test_bin_13(self):
        Sy = [5, 10, 15]
        Sx = [11]
        bins = [1,1,1]
        T = 16
        res, total = compute_binning(Sy, Sx, bins, T)
        
        self.assertEqual(total, 15)
        self.assertEqual(res[(0, 0, 1, 0, 1, 0)], 1.0/15)
        self.assertEqual(res[(0, 0, 1, 0, 0, 0)], 1.0/15)
        self.assertEqual(res[(1, 0, 0, 0, 0, 0)], 3.0/15)
        self.assertEqual(res[(0, 1, 0, 0, 0, 0)], 2.0/15)
        self.assertEqual(res[(0, 0, 0, 0, 0, 0)], 6.0/15)
        self.assertEqual(res[(0, 1, 0, 1, 0, 0)], 1.0/15)
        self.assertEqual(res[(0, 0, 0, 0, 0, 1)], 1.0/15)

        bins = [1,2,3]
        res, total = compute_binning(Sy, Sx, bins, T)
        self.assertEqual(total,12)
        self.assertEqual(res[(1, 0, 1, 0, 0, 0)], 1.0/12)
        self.assertEqual(res[(0, 0, 1, 0, 1, 0)], 1.0/12)
        self.assertEqual(res[(0, 1, 0, 0, 1, 0)], 1.0/12)
        self.assertEqual(res[(0, 0, 1, 0, 0, 0)], 2.0/12)
        self.assertEqual(res[(1, 0, 0, 0, 0, 0)], 1.0/12)
        self.assertEqual(res[(0, 1, 0, 0, 0, 0)], 2.0/12)
        self.assertEqual(res[(0, 0, 1, 0, 0, 1)], 1.0/12)
        self.assertEqual(res[(1, 0, 1, 0, 0, 1)], 1.0/12)
        self.assertEqual(res[(0, 1, 0, 1, 0, 0)], 1.0/12)
        self.assertEqual(res[(0, 1, 0, 0, 0, 1)], 1.0/12)
        self.assertEqual(res[(0, 0, 0, 0, 0, 0)], 0.0/12)

    def test_bin_14(self):
        Sy = [12, 81, 27, 66, 16, 69, 9, 42, 75, 15]
        Sx = [84, 97, 88, 21, 32, 94, 14, 63, 51, 36]
        T = 100
        bins = [1, 2, 3]
        res, total = compute_binning(Sy, Sx, bins, T)
        
        self.assertEqual(total, 96.0)
        self.assertEqual(res[(1, 0, 1, 0, 0, 0)], 2.0/96.0)
        self.assertEqual(res[(0, 0, 0, 0, 0, 0)], 13.0/96.0)
        self.assertEqual(res[(0, 0, 0, 0, 1, 0)], 12.0/96.0)
        self.assertEqual(res[(0, 1, 0, 0, 0, 1)], 2.0/96.0)
        self.assertEqual(res[(0, 0, 0, 0, 1, 1)], 4.0/96.0)
        self.assertEqual(res[(1, 0, 1, 0, 1, 0)], 1.0/96.0)
        self.assertEqual(res[(0, 0, 1, 0, 0, 0)], 12.0/96.0)
        self.assertEqual(res[(1, 0, 0, 0, 0, 0)], 5.0/96.0)
        self.assertEqual(res[(0, 1, 0, 0, 0, 0)], 10.0/96.0)
        self.assertEqual(res[(0, 0, 1, 1, 0, 0)], 3.0/96.0)
        self.assertEqual(res[(0, 1, 1, 0, 0, 1)], 2.0/96.0)
        self.assertEqual(res[(0, 0, 1, 0, 1, 0)], 2.0/96.0)
        self.assertEqual(res[(0, 0, 1, 0, 0, 1)], 1.0/96.0)
        self.assertEqual(res[(0, 1, 1, 1, 0, 0)], 1.0/96.0)
        self.assertEqual(res[(1, 0, 0, 0, 0, 1)], 1.0/96.0)
        self.assertEqual(res[(0, 0, 0, 0, 0, 1)], 15.0/96.0)
        self.assertEqual(res[(0, 0, 0, 1, 0, 1)], 3.0/96.0)
        self.assertEqual(res[(0, 0, 0, 1, 0, 0)], 3.0/96.0)
        self.assertEqual(res[(0, 1, 1, 0, 0, 0)], 3.0/96.0)
        self.assertEqual(res[(1, 1, 1, 0, 1, 0)], 1.0/96.0)

    def test_bin_15(self):
        Sy = [62, 2, 92, 27, 57, 25, 45, 23, 69, 88]
        Sx = [52, 3, 39, 41, 22, 76, 98, 44, 17, 6]

        T = 100
        bins = [1, 2, 3]
        res, total = compute_binning(Sy, Sx, bins, T)
        
        self.assertEqual(total, 96.0)
        self.assertEqual(res[(0, 1, 0, 0, 1, 1)], 1.0/96.0)
        self.assertEqual(res[(1, 0, 0, 0, 1, 0)], 1.0/96.0)
        self.assertEqual(res[(0, 0, 1, 0, 0, 0)], 16.0/96.0)
        self.assertEqual(res[(0, 0, 1, 1, 0, 1)], 1.0/96.0)
        self.assertEqual(res[(1, 0, 0, 0, 0, 1)], 1.0/96.0)
        self.assertEqual(res[(0, 0, 1, 0, 1, 1)], 1.0/96.0)
        self.assertEqual(res[(1, 0, 1, 0, 0, 0)], 2.0/96.0)
        self.assertEqual(res[(0, 0, 0, 0, 1, 1)], 3.0/96.0)
        self.assertEqual(res[(1, 1, 0, 0, 0, 1)], 1.0/96.0)
        self.assertEqual(res[(1, 0, 0, 0, 0, 0)], 2.0/96.0)
        self.assertEqual(res[(1, 1, 1, 0, 0, 1)], 1.0/96.0)
        self.assertEqual(res[(1, 0, 0, 0, 1, 1)], 1.0/96.0)
        self.assertEqual(res[(0, 0, 0, 1, 0, 1)], 2.0/96.0)
        self.assertEqual(res[(0, 0, 0, 0, 0, 0)], 20.0/96.0)
        self.assertEqual(res[(0, 1, 0, 0, 1, 0)], 1.0/96.0)
        self.assertEqual(res[(0, 0, 0, 1, 1, 0)], 1.0/96.0)
        self.assertEqual(res[(0, 0, 0, 0, 0, 1)], 10.0/96.0)
        self.assertEqual(res[(0, 1, 0, 0, 0, 1)], 1.0/96.0)
        self.assertEqual(res[(0, 0, 0, 1, 0, 0)], 5.0/96.0)
        self.assertEqual(res[(0, 1, 1, 0, 0, 0)], 3.0/96.0)
        self.assertEqual(res[(0, 0, 1, 0, 1, 0)], 1.0/96.0)
        self.assertEqual(res[(0, 0, 0, 0, 1, 0)], 9.0/96.0)
        self.assertEqual(res[(0, 1, 0, 0, 0, 0)], 9.0/96.0)
        self.assertEqual(res[(0, 1, 1, 0, 0, 1)], 1.0/96.0)
        self.assertEqual(res[(0, 0, 1, 0, 0, 1)], 2.0/96.0)

    def test_bin_16(self):
        Sy = [86, 55, 75, 61, 22, 9, 94, 3, 63, 93]
        Sx = [82, 58, 76, 30, 65, 97, 5, 49, 67, 62]

        T = 100
        bins = [4, 4, 4, 4]
        res, total = compute_binning(Sy, Sx, bins, T)
        
        self.assertEqual(total, 86.0)
        self.assertEqual(res[(0, 0, 1, 0, 1, 0, 1, 0)], 2.0/86.0)
        self.assertEqual(res[(1, 0, 1, 0, 0, 1, 1, 0)], 1.0/86.0)
        self.assertEqual(res[(0, 0, 0, 0, 0, 0, 0, 1)], 4.0/86.0)
        self.assertEqual(res[(1, 1, 0, 0, 0, 0, 1, 0)], 1.0/86.0)
        self.assertEqual(res[(0, 1, 0, 0, 1, 0, 1, 0)], 2.0/86.0)
        self.assertEqual(res[(0, 0, 0, 0, 0, 0, 1, 0)], 4.0/86.0)
        self.assertEqual(res[(0, 0, 0, 1, 0, 0, 0, 0)], 1.0/86.0)
        self.assertEqual(res[(1, 1, 0, 0, 1, 0, 0, 1)], 1.0/86.0)
        self.assertEqual(res[(1, 0, 0, 0, 1, 0, 1, 0)], 1.0/86.0)
        self.assertEqual(res[(0, 1, 0, 0, 1, 0, 0, 1)], 1.0/86.0)
        self.assertEqual(res[(0, 0, 0, 1, 0, 1, 0, 0)], 4.0/86.0)
        self.assertEqual(res[(1, 1, 1, 0, 1, 0, 0, 1)], 1.0/86.0)
        self.assertEqual(res[(0, 1, 1, 1, 0, 1, 0, 0)], 0.0/86.0)
        self.assertEqual(res[(0, 1, 0, 1, 1, 0, 0, 0)], 3.0/86.0)
        self.assertEqual(res[(0, 0, 1, 0, 1, 1, 0, 0)], 1.0/86.0)
        self.assertEqual(res[(1, 0, 0, 1, 0, 0, 1, 1)], 1.0/86.0)
        self.assertEqual(res[(0, 0, 1, 0, 0, 0, 0, 1)], 2.0/86.0)
        self.assertEqual(res[(0, 1, 0, 0, 0, 1, 0, 1)], 2.0/86.0)
        self.assertEqual(res[(1, 1, 1, 0, 1, 1, 0, 0)], 1.0/86.0)
        self.assertEqual(res[(1, 0, 0, 0, 0, 0, 1, 0)], 1.0/86.0)
        self.assertEqual(res[(1, 0, 0, 1, 0, 0, 0, 0)], 3.0/86.0)
        self.assertEqual(res[(0, 0, 1, 1, 0, 1, 1, 1)], 2.0/86.0)
        self.assertEqual(res[(1, 0, 0, 1, 1, 0, 1, 1)], 3.0/86.0)
        self.assertEqual(res[(1, 1, 0, 0, 1, 1, 0, 1)], 1.0/86.0)
        self.assertEqual(res[(1, 1, 1, 0, 1, 1, 1, 0)], 1.0/86.0)
        self.assertEqual(res[(0, 1, 0, 0, 0, 0, 0, 0)], 4.0/86.0)
        self.assertEqual(res[(0, 1, 0, 1, 1, 1, 1, 0)], 2.0/86.0)
        self.assertEqual(res[(1, 0, 0, 1, 0, 1, 0, 1)], 2.0/86.0)
        self.assertEqual(res[(0, 1, 0, 0, 1, 1, 0, 1)], 1.0/86.0)
        self.assertEqual(res[(0, 0, 1, 0, 0, 1, 1, 1)], 2.0/86.0)
        self.assertEqual(res[(1, 0, 0, 0, 0, 0, 0, 0)], 1.0/86.0)
        self.assertEqual(res[(0, 1, 0, 0, 0, 0, 1, 1)], 1.0/86.0)
        self.assertEqual(res[(0, 0, 0, 0, 1, 0, 0, 0)], 4.0/86.0)
        self.assertEqual(res[(1, 0, 0, 0, 0, 1, 0, 0)], 2.0/86.0)
        self.assertEqual(res[(1, 0, 1, 0, 1, 1, 0, 1)], 2.0/86.0)
        self.assertEqual(res[(1, 0, 0, 1, 0, 1, 1, 0)], 1.0/86.0)
        self.assertEqual(res[(0, 0, 1, 1, 0, 0, 0, 1)], 2.0/86.0)
        self.assertEqual(res[(0, 0, 1, 0, 1, 0, 0, 0)], 4.0/86.0)
        self.assertEqual(res[(0, 1, 0, 1, 0, 0, 1, 0)], 2.0/86.0)
        self.assertEqual(res[(0, 1, 0, 1, 0, 0, 1, 1)], 1.0/86.0)
        self.assertEqual(res[(0, 1, 0, 0, 0, 0, 1, 0)], 1.0/86.0)
        self.assertEqual(res[(0, 1, 1, 1, 1, 1, 1, 1)], 1.0/86.0)
        self.assertEqual(res[(0, 0, 0, 0, 0, 1, 0, 0)], 2.0/86.0)
        self.assertEqual(res[(1, 0, 1, 0, 0, 0, 0, 1)], 3.0/86.0)
        self.assertEqual(res[(0, 0, 0, 0, 0, 0, 0, 0)], 3.0/86.0)
        self.assertEqual(res[(0, 1, 1, 1, 1, 1, 1, 0)], 1.0/86.0)

    def test_bin_17(self):
        Sy = [54, 17, 84, 2, 57, 13, 15, 69, 80, 78, 58, 83, 1, 49, 16, 70, 34, 96, 64, 24, 29, 59, 93, 36, 81, 31, 68, 65, 48, 9, 86, 62, 22, 74, 66, 46, 92, 55, 19, 94, 14, 99, 25, 77, 10, 98, 45, 67, 4, 21]
        Sx = [90, 22, 99, 36, 27, 85, 73, 74, 66, 96, 20, 1, 89, 16, 53, 40, 52, 56, 98, 59]

        T = 100
        bins = [4, 4, 4, 4]
        res, total = compute_binning(Sy, Sx, bins, T)
        
        self.assertEqual(total, 86.0)
        self.assertEqual(res[(1, 0, 1, 1, 0, 1, 1, 0)], 5.0/86.0)
        self.assertEqual(res[(1, 0, 1, 1, 1, 1, 0, 0)], 1.0/86.0)
        self.assertEqual(res[(1, 1, 1, 1, 1, 0, 1, 1)], 8.0/86.0)
        self.assertEqual(res[(1, 1, 0, 0, 1, 0, 0, 1)], 1.0/86.0)
        self.assertEqual(res[(1, 1, 0, 1, 1, 1, 1, 0)], 1.0/86.0)
        self.assertEqual(res[(0, 1, 1, 0, 1, 0, 0, 1)], 1.0/86.0)
        self.assertEqual(res[(1, 1, 1, 0, 1, 0, 0, 1)], 2.0/86.0)
        self.assertEqual(res[(1, 1, 1, 1, 1, 0, 0, 0)], 3.0/86.0)
        self.assertEqual(res[(0, 1, 1, 1, 1, 1, 0, 1)], 3.0/86.0)
        self.assertEqual(res[(1, 0, 0, 1, 0, 0, 1, 1)], 1.0/86.0)
        self.assertEqual(res[(1, 1, 1, 1, 0, 1, 1, 1)], 6.0/86.0)
        self.assertEqual(res[(1, 1, 0, 1, 0, 0, 1, 1)], 3.0/86.0)
        self.assertEqual(res[(1, 1, 1, 1, 0, 0, 1, 1)], 1.0/86.0)
        self.assertEqual(res[(1, 1, 1, 0, 1, 1, 0, 0)], 2.0/86.0)
        self.assertEqual(res[(1, 1, 1, 1, 1, 1, 0, 1)], 2.0/86.0)
        self.assertEqual(res[(1, 1, 1, 1, 1, 1, 1, 0)], 8.0/86.0)
        self.assertEqual(res[(1, 1, 1, 1, 1, 1, 1, 1)], 5.0/86.0)
        self.assertEqual(res[(1, 1, 0, 1, 1, 0, 1, 1)], 2.0/86.0)
        self.assertEqual(res[(1, 1, 1, 1, 0, 0, 0, 1)], 1.0/86.0)
        self.assertEqual(res[(1, 1, 1, 1, 0, 1, 0, 1)], 6.0/86.0)
        self.assertEqual(res[(1, 1, 1, 1, 1, 1, 0, 0)], 6.0/86.0)
        self.assertEqual(res[(1, 1, 1, 1, 0, 0, 1, 0)], 3.0/86.0)
        self.assertEqual(res[(1, 1, 1, 0, 0, 1, 1, 1)], 1.0/86.0)
        self.assertEqual(res[(1, 1, 1, 1, 0, 1, 1, 0)], 2.0/86.0)
        self.assertEqual(res[(0, 1, 1, 1, 1, 1, 0, 0)], 3.0/86.0)
        self.assertEqual(res[(1, 1, 1, 1, 1, 0, 0, 1)], 4.0/86.0)
        self.assertEqual(res[(0, 0, 1, 1, 0, 1, 1, 0)], 1.0/86.0)
        self.assertEqual(res[(1, 1, 0, 1, 1, 0, 0, 1)], 1.0/86.0)
        self.assertEqual(res[(1, 1, 1, 1, 1, 0, 1, 0)], 3.0/86.0)

    def test_bin_18(self):
        Sy = [1484, 8060, 7191, 7566, 907, 4526, 9175, 4559, 125, 2315, 4268, 9643, 7740, 3136, 3970, 3315, 2915, 7173, 2392, 8428, 4212, 7337, 1393, 5325, 6088, 4709, 7341, 4225, 3124, 7629, 3194, 555, 7139, 1016, 1816, 8874, 5472, 9015, 1570, 4602, 4091, 2406, 2279, 8736, 7010, 6030, 4191, 1360, 5089, 7196]
        Sx = [9770, 5651, 468, 5545, 8823, 8722, 831, 7096, 611, 6434, 1075, 8931, 6955, 229, 4664, 562, 1512, 1453, 5975, 6052]

        T = 10000
        bins = [30, 20, 10]
        res, total = compute_binning(Sy, Sx, bins, T)
        
        self.assertEqual(total, 9942.0)
        self.assertEqual(res[(1, 0, 0, 0, 1, 0)], 57.0/9942.0)
        self.assertEqual(res[(1, 1, 0, 0, 0, 0)], 148.0/9942.0)
        self.assertEqual(res[(0, 0, 1, 0, 0, 0)], 334.0/9942.0)
        self.assertEqual(res[(0, 0, 1, 1, 0, 1)], 3.0/9942.0)
        self.assertEqual(res[(1, 0, 0, 1, 0, 0)], 48.0/9942.0)
        self.assertEqual(res[(1, 0, 0, 0, 0, 1)], 60.0/9942.0)
        self.assertEqual(res[(1, 0, 1, 0, 0, 0)], 63.0/9942.0)
        self.assertEqual(res[(1, 0, 0, 0, 0, 0)], 982.0/9942.0)
        self.assertEqual(res[(1, 0, 0, 1, 0, 1)], 1.0/9942.0)
        self.assertEqual(res[(0, 0, 0, 1, 0, 1)], 7.0/9942.0)
        self.assertEqual(res[(0, 0, 0, 0, 0, 0)], 6505.0/9942.0)
        self.assertEqual(res[(1, 1, 1, 0, 0, 0)], 16.0/9942.0)
        self.assertEqual(res[(1, 0, 1, 0, 1, 0)], 2.0/9942.0)
        self.assertEqual(res[(0, 1, 0, 0, 1, 0)], 19.0/9942.0)
        self.assertEqual(res[(0, 1, 0, 1, 0, 0)], 47.0/9942.0)
        self.assertEqual(res[(0, 0, 0, 0, 0, 1)], 119.0/9942.0)
        self.assertEqual(res[(0, 1, 0, 0, 0, 1)], 10.0/9942.0)
        self.assertEqual(res[(0, 0, 0, 1, 0, 0)], 479.0/9942.0)
        self.assertEqual(res[(0, 1, 1, 0, 0, 0)], 42.0/9942.0)
        self.assertEqual(res[(0, 0, 1, 0, 1, 0)], 14.0/9942.0)
        self.assertEqual(res[(0, 0, 0, 0, 1, 0)], 307.0/9942.0)
        self.assertEqual(res[(0, 1, 0, 0, 0, 0)], 664.0/9942.0)
        self.assertEqual(res[(0, 0, 1, 1, 0, 0)], 14.0/9942.0)
        self.assertEqual(res[(0, 0, 1, 1, 1, 0)], 1.0/9942.0)

    def test_bin_19(self):
        Sy = [59501, 63387, 97596, 67133, 84610, 86697, 79469, 25100, 6476, 47952, 18158, 66416, 19987, 33440, 8331, 98105, 84462, 5530, 33506, 53166, 1894, 67461, 24677, 27559, 64795, 26308, 38221, 31690, 67452, 84275, 52860, 73382, 5740, 64202, 68341, 87324, 84646, 33566, 78638, 31101, 55910, 17663, 479, 44979, 85065, 70744, 20027, 48965, 54573, 86209]
        Sx = [17163, 7615, 8027, 84123, 53996, 38542, 82753, 71516, 33675, 71840, 41189, 11142, 37523, 15166, 53365, 20155, 91251, 51139, 34538, 63644]
        print("len: ", len(Sy), len(Sx))

        T = 100000
        bins = [30, 20, 10]
        res, total = compute_binning(Sy, Sx, bins, T)
        for r in res:
            if(res[r]):
                print("ASSERT_NEAR(prob_map[{0}], {1}/{2}, 0.00000001);".format(int("".join([str(c) for c in r]),2), res[r]*total, total))

        self.assertEqual(total, 99942.0)
        self.assertEqual(res[(1, 0, 1, 0, 0, 0)], 20.0/99942.0)
        self.assertEqual(res[(0, 0, 0, 0, 0, 0)], 95837.0/99942.0)
        self.assertEqual(res[(1, 1, 0, 0, 0, 0)], 33.0/99942.0)
        self.assertEqual(res[(0, 0, 1, 0, 0, 0)], 470.0/99942.0)
        self.assertEqual(res[(1, 0, 0, 0, 0, 0)], 1426.0/99942.0)
        self.assertEqual(res[(0, 1, 1, 0, 0, 0)], 9.0/99942.0)
        self.assertEqual(res[(0, 1, 0, 0, 0, 0)], 947.0/99942.0)
        self.assertEqual(res[(0, 0, 0, 0, 0, 1)], 200.0/99942.0)
        self.assertEqual(res[(0, 0, 0, 1, 0, 0)], 600.0/99942.0)
        self.assertEqual(res[(0, 0, 0, 0, 1, 0)], 400.0/99942.0)

    def test_bin_20(self):
        Sy = [5794872, 8521503, 5160203, 6970555, 5394460, 4868795, 5528838, 2656425, 738190, 3388549, 2710033, 4625363, 2213201, 7353506, 275778, 4045780, 3980515, 9074583, 3513606, 2722249, 1552599, 2510575, 8853283, 7469933, 1482614, 8249944, 3413151, 898077, 1784071, 1290751, 8004110, 9723082, 2292587, 2774755, 1867822, 1750241, 9859374, 385795, 7783911, 5243866, 5574209, 7419988, 6034063, 5970672, 7276745, 8720298, 5752114, 9433016, 4594207, 534465]
        Sx = [1646556, 9532998, 5321762, 835566, 2897468, 1035603, 1002595, 4045530, 2069799, 5581481, 6658449, 4655977, 7104045, 5475766, 3175328, 2344459, 7760081, 4088226, 5432869, 2426765]
        T = 10000000
        bins = [30, 20, 10]
        res, total = compute_binning(Sy, Sx, bins, T)
        self.assertEqual(total, 9999942.0)
        self.assertEqual(res[(0, 0, 0, 0, 0, 0)], 9995742.0/9999942.0)
        self.assertEqual(res[(0, 0, 1, 0, 0, 0)], 500.0/9999942.0)
        self.assertEqual(res[(1, 0, 0, 0, 0, 0)], 1500.0/9999942.0)
        self.assertEqual(res[(0, 1, 0, 0, 0, 0)], 1000.0/9999942.0)
        self.assertEqual(res[(0, 0, 0, 0, 0, 1)], 200.0/9999942.0)
        self.assertEqual(res[(0, 0, 0, 1, 0, 0)], 600.0/9999942.0)
        self.assertEqual(res[(0, 0, 0, 0, 1, 0)], 400.0/9999942.0)
        
if __name__ == '__main__':
    unittest.main()