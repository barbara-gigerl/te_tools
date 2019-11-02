import unittest
import transfer_entropy as te
import numpy as np
import binning


class TestTransferEntropy(unittest.TestCase):
       
    def test_te_1(self):
        Sy = [1, 5, 9, 17, 22, 29]
        Sx = [1, 5, 9, 17, 22, 29]
        bins = [1, 2, 3] 
        T = 30
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        self.assertAlmostEqual(te_ , 0, 7)
        self.assertAlmostEqual(pt_bias, 0, 7)

        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0, 7)
        self.assertAlmostEqual(pt_bias, 0, 7)

        te_, _ = te.TE(Sy, Sx, bins, T, te.T2)
        self.assertAlmostEqual(te_, 0, 7)

        te_, _ = te.TE(Sx, Sy, bins, T, te.T2)
        self.assertAlmostEqual(te_, 0, 7)

    def test_te_2(self):
        Sy = [1, 5, 9, 10, 17, 22, 29]
        Sx = [2, 7, 10, 13, 18, 20]
        bins = [1, 2, 3] 
        T = 30
        
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)   

        self.assertAlmostEqual(te_, 0.0667437497504, 7)
        self.assertAlmostEqual(pt_bias, 0.0832324062051, 7)   

        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)  
        self.assertAlmostEqual(te_, 0.0822154170814, 7)
        self.assertAlmostEqual(pt_bias, 0.0554882708034, 7)   
        
        te_, _ = te.TE(Sy, Sx, bins, T, te.T2)  
        self.assertAlmostEqual(te_, 0.0667437497504, 7)        
        
        # te_, _ = te.TE(Sx, Sy, bins, T, te.T2)  
        # self.assertAlmostEqual(te_, 0.0822154170814, 7)
        
    def test_te_3(self):
        Sy = [1, 5, 9, 17, 22, 29]
        Sx = [2, 7, 10, 13, 18, 20]
        bins = [1,1] 
        T = 30
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.0980449991346, 7)  
        self.assertAlmostEqual(pt_bias, 0, 7)
      
        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.0590090465783, 7)
        self.assertAlmostEqual(pt_bias, 0.0240449173481, 7)

        te_, _ = te.TE(Sy, Sx, bins, T, te.T2)
        self.assertAlmostEqual(te_, 0.0980449991346, 7)        
        te_, _ = te.TE(Sx, Sy, bins, T, te.T2)
        self.assertAlmostEqual(te_, 0.0590090465783, 7)

        bins = [1,1,1,1] 
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.0761267101713, 7)  
        self.assertAlmostEqual(pt_bias, 0.0515248228889, 7)
      
        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.143380278132, 7)
        self.assertAlmostEqual(pt_bias, 0.0515248228889, 7)

        te_, _ = te.TE(Sy, Sx, bins, T, te.T2)
        self.assertAlmostEqual(te_, 0.0761267101713, 7)        
        te_, _ = te.TE(Sx, Sy, bins, T, te.T2)
        self.assertAlmostEqual(te_, 0.143380278132, 7)


    def test_te_4(self):
        Sy = [10, 15, 20, 25, 30, 35, 40]
        Sx = [2,5,9,20,22,27,32,37]
        bins = [4,4,4,4] 
        T = 40
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.380774404996, 7)        
        self.assertAlmostEqual(pt_bias, 0.305185489419, 7)  

        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.615384615385, 7)
        self.assertAlmostEqual(pt_bias, 0.16646481241, 7)  

        te_, _ = te.TE(Sy, Sx, bins, T, te.T2)
        self.assertAlmostEqual(te_, 0.380774404996, 7)  

        te_, _ = te.TE(Sx, Sy, bins, T, te.T2)
        self.assertAlmostEqual(te_, 0.615384615385, 7)



    def test_te_5(self):
        Sy = [0, 2, 4, 5, 13, 17, 20, 23, 26, 30, 31, 32, 33, 37, 38, 40, 44, 45, 46, 48, 52, 56, 57, 64, 69, 70, 72, 73, 77, 78, 79, 80, 82, 85, 92, 95, 97]
        Sx = [1, 2, 4, 5, 7, 9, 11, 12, 14, 25, 27, 29, 31, 35, 36, 43, 45, 46, 48, 51, 58, 59, 61, 63, 64, 69, 72, 76, 77, 78, 81, 82, 83, 86, 89, 93, 94, 95, 96]
        T = 100

        bins = [1, 10, 15]
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.0092008313723, 7)
        self.assertAlmostEqual(pt_bias, 0, 7)          

        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.0, 7)
        self.assertAlmostEqual(pt_bias, 0, 7)  
        te_, _ = te.TE(Sy, Sx, bins, T, te.T2)
        self.assertAlmostEqual(te_, 0.0092008313723, 7) 
        te_, _ = te.TE(Sx, Sy, bins, T, te.T2)
        self.assertAlmostEqual(te_, 0.0, 7)



        bins = [1,1,5,8]
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.100474069503, 7)
        self.assertAlmostEqual(pt_bias, 0.0580394556679, 7)          
        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.0741316822663, 7)
        self.assertAlmostEqual(pt_bias, 0.0497481048582, 7)  
        te_, _ = te.TE(Sy, Sx, bins, T, te.T2)
        self.assertAlmostEqual(te_, 0.100474069503, 7) 
        te_, _ = te.TE(Sx, Sy, bins, T, te.T2)
        self.assertAlmostEqual(te_, 0.0741316822663, 7)

        bins = [1,20,30]

        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0, 7)
        self.assertAlmostEqual(pt_bias, 0.0, 7)          
        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0, 7)
        self.assertAlmostEqual(pt_bias, 0.0, 7)  
        te_, _ = te.TE(Sy, Sx, bins, T, te.T2 )
        self.assertAlmostEqual(te_, 0, 7) 
        te_, _ = te.TE(Sy, Sx, bins, T, te.T2)
        self.assertAlmostEqual(te_, 0, 7)


    def test_te_6(self):
        Sy = [512, 515, 7, 16, 529, 542, 47, 574, 578, 70, 72, 78, 597, 98, 105, 624, 118, 120, 122, 124, 125, 642, 140, 653, 656, 147, 672, 163, 675, 169, 683, 685, 185, 699, 188, 702, 193, 708, 198, 201, 207, 720, 722, 728, 731, 737, 226, 742, 231, 755, 248, 768, 256, 257, 265, 783, 281, 798, 814, 824, 834, 334, 846, 340, 856, 859, 862, 353, 871, 363, 365, 366, 879, 881, 889, 378, 902, 391, 907, 399, 410, 413, 933, 423, 941, 942, 944, 440, 967, 979, 470, 986, 991, 998, 495, 504]
        Sx = [513, 514, 516, 518, 6, 531, 546, 547, 554, 555, 46, 558, 560, 561, 559, 55, 568, 576, 65, 68, 84, 599, 88, 95, 613, 614, 113, 116, 630, 130, 645, 138, 146, 148, 664, 156, 157, 173, 698, 700, 188, 711, 712, 717, 730, 221, 228, 751, 752, 766, 272, 276, 788, 792, 799, 806, 812, 300, 305, 824, 325, 327, 846, 336, 341, 854, 857, 347, 869, 886, 374, 896, 898, 396, 909, 404, 936, 942, 433, 442, 955, 965, 966, 967, 454, 975, 471, 991, 482, 497, 499]
 
        T = 1000
        bins = [1,1,1]
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.00409879953443, 7)
        self.assertAlmostEqual(pt_bias, 0.00288827836014, 7)
        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)        
        self.assertAlmostEqual(te_, 0.0086617579233, 7)
        self.assertAlmostEqual(pt_bias, 0.00288827836014, 7)
        te_, _ = te.TE(Sy, Sx, bins, T, te.T2)
        self.assertAlmostEqual(te_, 0.00409879953443, 7)   
        te_, _ = te.TE(Sx, Sy, bins, T, te.T2)     
        self.assertAlmostEqual(te_, 0.0086617579233, 7)

        bins = [1,2,4]
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.00627071829187, 7)   
        self.assertAlmostEqual(pt_bias, 0.00652475144121, 7)
        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)     
        self.assertAlmostEqual(te_, 0.0184209338786, 7)
        self.assertAlmostEqual(pt_bias, 0.00507480667649, 7)
        te_, _ = te.TE(Sy, Sx, bins, T, te.T2)
        self.assertAlmostEqual(te_, 0.00627071829187, 7)
        te_, _ = te.TE(Sx, Sy, bins, T, te.T2)        
        self.assertAlmostEqual(te_, 0.0184209338786, 7)


        bins = [1,2,3,4,10]
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.0936929753158, 7)  
        self.assertAlmostEqual(pt_bias, 0.0301173608332, 7)
        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.0775064179923, 7)       
        self.assertAlmostEqual(pt_bias, 0.0293827910568, 7)
        te_, _ = te.TE(Sy, Sx, bins, T, te.T2)
        self.assertAlmostEqual(te_, 0.0936929753158, 7)        
        te_, _ = te.TE(Sx, Sy, bins, T, te.T2)
        self.assertAlmostEqual(te_, 0.0775064179923, 7)

    def test_te_7(self):
        Sy = [0, 2, 4, 5, 13, 17, 20, 23, 26, 30, 31, 32, 33, 37, 38, 40, 44, 45, 46, 48, 52, 56, 57, 64, 69, 70, 72, 73, 77, 78, 79, 80, 82, 85, 92, 95, 97]
        Sx = [1, 2, 4, 5, 7, 9, 11, 12, 14, 25, 27, 29, 31, 35, 36, 43, 45, 46, 48, 51, 58, 59, 61, 63, 64, 69, 72, 76, 77, 78, 81, 82, 83, 86, 89, 93, 94, 95, 96]
        T = 100
       
        bins = binning.get_logarithmic_bins(20, 2, 4)
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.0, 7)  
        self.assertAlmostEqual(pt_bias, 0.011271055006945026, 7)
        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.024922529365165924, 7)  
        self.assertAlmostEqual(pt_bias, 0.011271055006945026, 7)

        bins = binning.get_equal_bins(2, 3)
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.1781851618234498, 7)  
        self.assertAlmostEqual(pt_bias, 0.075140366713, 7)
        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.132255376361, 7)  
        self.assertAlmostEqual(pt_bias, 0.0826544033843, 7)

        bins = binning.get_linear_bins(1, 5, 2)
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.0129588077822, 7)  
        self.assertAlmostEqual(pt_bias, 0.0147213779683, 7)
        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)
        self.assertAlmostEqual(te_, 0.000564815552854, 7)  
        self.assertAlmostEqual(pt_bias, 0.0147213779683, 7)
        

    def test_te_8(self):
        Sy = [1, 5, 9, 17, 22, 29]
        Sx = [2, 7, 10, 13, 18, 20]
        binsY = [1,1]
        T = 30
        te_, pt_bias = te.TE(Sy, Sx, binsY, T, te.T1)
        self.assertAlmostEqual(te_, 0.0980449991346, 7)  
        self.assertAlmostEqual(pt_bias, 0.0, 7)
      
        te_, pt_bias = te.TE(Sx, Sy, binsY, T, te.T1)
        self.assertAlmostEqual(te_, 0.0590090465783, 7)
        self.assertAlmostEqual(pt_bias, 0.0240449173481, 7)

        te_, _ = te.TE(Sy, Sx, binsY, T, te.T2)
        self.assertAlmostEqual(te_, 0.0980449991346, 7)        
        te_, _ = te.TE(Sx, Sy, binsY, T, te.T2)
        self.assertAlmostEqual(te_, 0.0590090465783, 7)

    def test_te_9(self):
        Sy = [3279945, 3427340, 2573366, 3946138, 3163656, 8688831, 4125068, 6118634, 4038727, 6195770, 5853039, 3557960, 9781308, 1079404, 7274951, 3152428, 9047755, 2580214, 3598433, 9078574, 9278855, 2779121, 4089748, 6958134, 8211367, 1010264, 3411002, 4189681, 3823186, 5109343, 6658030, 5594693, 8301088, 8663247, 1518263, 989712, 202930, 4762816, 7822971, 5783613, 423888, 7925554, 6573321, 5981109, 1933272, 6129176, 3148330, 9860403, 4847021, 2025788]
        Sx = [901421, 7863502, 4461387, 8873213, 6327257, 9053755, 9680550, 1010824, 6597410, 9157089, 7144571, 9392518, 2561799, 3079317, 4100985, 6984279, 3177219, 9047543, 2402167, 5205809]
        T = 10000000
        bins = [10, 20, 30]
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        self.assertAlmostEqual(te_, 7.21590407218e-09, 7)
        self.assertAlmostEqual(pt_bias, 0.0, 7)
        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)
        self.assertAlmostEqual(te_, 7.21525451278e-09, 7)
        self.assertAlmostEqual(pt_bias, 0.0, 7) 
    
    def test_te_10(self):
        Sy = [5368532, 433652, 8985678, 7550227, 2846495, 1095361, 4766726, 5972762, 3724270, 7221365, 3480359, 3739357, 9857126, 1399566, 5792540, 4523129, 5440765, 9345260, 7899495, 6766269, 3765125, 6093604, 6551839, 9398649, 1727774, 9024611, 5775455, 4173582, 5222399, 6276308, 7678311, 6426189, 1689332, 7321275, 6518495, 8089604, 5390096, 1542599, 4888141, 3891087, 5563292, 7048916, 1910976, 9365294, 1322664, 8117581, 1072674, 8263426, 2365274, 6337909]
        Sx = [29754, 4200404, 6299033, 9017864, 9672901, 6647336, 3645457, 4289465, 9439877, 3344284, 7098085, 4858515, 2431659, 7632120, 5012133, 6283685, 3677871, 3493916, 5685796, 448822]
        T = 10000000
        bins = [10, 20, 30]
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        self.assertAlmostEqual(te_, 7.21590407218e-09, 7)
        self.assertAlmostEqual(pt_bias, 0.0, 7)
        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)
        self.assertAlmostEqual(te_, 7.21525451278e-09, 7)
        self.assertAlmostEqual(pt_bias, 0.0, 7)

    def test_te_11(self):
        Sy = [2993881, 6142050, 5151574, 6935362, 8404178, 3075134, 642930, 2636242, 2852081, 6186366, 3861712, 316858, 1613862, 129513, 6553789, 5912494, 283299, 82486, 5452838, 1377041, 9790286, 5684975, 9429817, 6699264, 872080, 2874634, 741820, 830387, 2375145, 7045407, 2537150, 500588, 5393285, 4688863, 5052038, 4532110, 6316356, 365774, 4836209, 2381098, 3379386, 6101909, 9497920, 9682332, 5798803, 6887869, 6716655, 5406602, 9055354, 9518146, 8635249, 914299, 9210317, 7774801, 7620687, 5639531, 7734519, 7671432, 6604098, 7315314, 1798441, 844475, 6134032, 6490485, 7388519, 8442526, 6726564, 901136, 3779131, 9422416, 7976420, 7328349, 5532554, 7718214, 266371, 4230897, 2120619, 9083254, 9875856, 2124790, 7668721, 8659530, 4154259, 2875348, 8762568, 101561, 3072834, 702796, 1578400, 6065070, 421135, 3091191, 773576, 3990463, 4683199, 2735329, 4279657, 669732, 5889026, 3286698]
        Sx = [9529233, 1914023, 785046, 5702726, 2426220, 9796201, 4013438, 5039266, 7531250, 3801969, 6872655, 2632221, 7736235, 1687719, 7351084, 1452314, 2917584, 6355872, 7069314, 2042444, 2022644, 1363704, 1177159, 932735, 891277, 2806633, 680282, 1157387, 4363065, 7672800, 5649887, 4521340, 4191531, 7652123, 3843633, 4091889, 7404311, 7399255, 3267060, 9651253, 7753898, 3260313, 1044279, 9055335, 3958554, 6883037, 8870788, 5825791, 1551253, 100269, 8212884, 93337, 7044259, 7411765, 7789913, 9823930, 4135398, 5633411, 9109158, 8332614, 6009443, 4232395, 9325282, 1245155, 9036786, 1962322, 1116557, 4208933, 2699990, 3561334, 4901777, 7640903, 6826256, 4826405, 6626018, 7318983, 2889002, 8223918, 5281759, 812242, 7201645, 9204323, 7312591, 6171519, 7228776, 5520289, 7420886, 6784361, 5321510, 7311527, 6692726, 4824833, 2402357, 3551595, 2116348, 1172110, 6185683, 1530131, 625929, 874701]
        T = 10000000
        bins = [10, 20, 30]
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        self.assertAlmostEqual(te_, 4.28291393679e-06, 7)
        self.assertAlmostEqual(pt_bias, 7.21351704284e-08, 7)
        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)
        self.assertAlmostEqual(te_, 7.17456353355e-08, 7)
        self.assertAlmostEqual(pt_bias, 0.0, 7)
    
    def test_te_12(self):
        Sy = [1778776, 8214065, 6564176, 9746309, 1853489, 1708381, 2308788, 4285308, 7341283, 4052961, 379516, 6517630, 6663148, 3529462, 7764278, 6282623, 4962894, 6268541, 2672471, 4155232, 9971300, 3036386, 1431736, 1390967, 1962097, 5793423, 3093121, 9008163, 1380555, 8173486, 8235351, 7824127, 3824681, 6570691, 5871483, 4411654, 3191864, 262182, 4997107, 6187278, 8470911, 206592, 5613527, 401138, 29850, 1369904, 1068791, 5901058, 4144509, 3518394, 8796202, 1440691, 296013, 8257995, 4032316, 6883550, 6751218, 5688435, 9570350, 6071529, 6307764, 7703423, 3585263, 7425376, 1730741, 1048684, 560280, 2839782, 7542130, 4579583, 23075, 9939384, 880750, 247834, 2753962, 7879530, 3473082, 5259778, 4286353, 2623837, 5275262, 3838615, 2101972, 1165174, 736415, 778308, 2266477, 1380502, 3235236, 9621688, 4289270, 5040946, 4466085, 8477535, 4490197, 4338639, 2252101, 9977626, 9446172, 3878262]
        Sx = [1824218, 661757, 9248541, 1057685, 6590927, 2463974, 2545983, 5794291, 8298960, 7208562, 3013822, 4102745, 2251820, 5055617, 1307558, 4120015, 8551111, 4211643, 7779891, 5737524, 605893, 8676599, 2061500, 9712468, 2592224, 1055877, 2329821, 8592568, 9598898, 1378918, 7394964, 7535290, 8314322, 6857202, 324481, 1363116, 6244710, 6986734, 161032, 4309178, 6223777, 2752427, 6477014, 9280392, 1984623, 9426588, 7031173, 6940040, 2696256, 1694776, 2877798, 2903365, 5423222, 4510859, 992637, 550336, 3875110, 1140335, 440372, 5343346, 8322386, 7609199, 3542993, 6529789, 856561, 4869951, 2824730, 7257716, 2204961, 7783309, 9519343, 5547625, 1958083, 1268565, 827604, 167076, 7358382, 3116490, 3043935, 658581, 1007006, 8823964, 9365520, 5019215, 3720168, 7626337, 3870345, 2782874, 26123, 8197670, 6050034, 2266170, 209522, 8850360, 836954, 4028825, 495902, 9756875, 1829477, 3392492]
        T = 10000000
        bins = [10, 20, 30]
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        te_, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
        self.assertAlmostEqual(te_, 7.16879668614e-08, 7)
        self.assertAlmostEqual(pt_bias, 0.0, 7)
        te_, pt_bias = te.TE(Sx, Sy, bins, T, te.T1)
        self.assertAlmostEqual(te_, 7.21933453903e-08, 7)
        self.assertAlmostEqual(pt_bias, 0.0, 7)

if __name__ == '__main__':
    unittest.main()