#include <gtest/gtest.h>
#include "../include/transfer_entropy.h"
#include "../include/binning.h"

TEST(TransferEntropyTest1, Standard1) { 
    double Sy [] = {1, 5, 9, 17, 22, 29};
    double Sx [] = {1, 5, 9, 17, 22, 29};
    int bins [] = {1, 2, 3};
    int T = 30;

    TransferEntropy te1 = TransferEntropy(Sy, 6, Sx, 6);
    TransferEntropy te2 = TransferEntropy(Sx, 6, Sy, 6);

    double (TransferEntropy::*T_func1)(double*, double*, double*, double*, int) = &TransferEntropy::T1;
    double (TransferEntropy::*T_func2)(double*, double*, double*, double*, int) = &TransferEntropy::T2;

    double pt_bias;
    double te_ = te1.TE(bins, 3, T, T_func1, &pt_bias);
    ASSERT_DOUBLE_EQ(te_, 0.0);
    ASSERT_NEAR(pt_bias, 0.0, 0.0000001);

    te_ = te1.TE(bins, 3, T, T_func2, &pt_bias);
    ASSERT_DOUBLE_EQ(te_, 0.0);
    ASSERT_NEAR(pt_bias, 0.0, 0.0000001);

    te_ = te2.TE(bins, 3, T, T_func1, &pt_bias);
    ASSERT_DOUBLE_EQ(te_, 0.0);
    ASSERT_NEAR(pt_bias, 0.0, 0.0000001);

    te_ = te2.TE(bins, 3, T, T_func2, &pt_bias);
    ASSERT_DOUBLE_EQ(te_, 0.0);
    ASSERT_NEAR(pt_bias, 0.0, 0.0000001);

}

TEST(TransferEntropyTest1, Standard2) {
    double Sy [] = {1, 5, 9, 10, 17, 22, 29};
    double Sx [] = {2, 7, 10, 13, 18, 20};

    sort(Sy, Sx+7);
    sort(Sx, Sx+6);
    int bins [] = {1, 2, 3};
    int T = 30;
    TransferEntropy te1 = TransferEntropy(Sy, 7, Sx, 6);
    TransferEntropy te2 = TransferEntropy(Sx, 6, Sy, 7);

    double (TransferEntropy::*T_func1)(double*, double*, double*, double*, int) = &TransferEntropy::T1;
    double (TransferEntropy::*T_func2)(double*, double*, double*, double*, int) = &TransferEntropy::T2;

    double pt_bias;

    double te_ = te1.TE(bins, 3,  T, T_func1, &pt_bias);
    cout << "TE: " << te_ << endl;
    ASSERT_NEAR(te_, 0.0667437497504, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0832324062051, 0.0000001);
    
    te_ = te1.TE(bins, 3, T, T_func2, &pt_bias);
    ASSERT_NEAR(te_, 0.0667437497504, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0832324062051, 0.0000001);

    te_ = te2.TE(bins, 3, T, T_func1, &pt_bias);
    ASSERT_NEAR(te_, 0.0822154170814, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0554882708034, 0.0000001);

    te_ = te2.TE(bins, 3, T, T_func2, &pt_bias);
    ASSERT_NEAR(te_, 0.0822154170814, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0554882708034, 0.0000001);
}

TEST(TransferEntropyTest1, Standard3) {
    double Sy [] = {1, 5, 9, 17, 22, 29};
    double Sx [] = {2, 7, 10, 13, 18, 20};
    int bins [] = {1,1};
    int T = 30;
    TransferEntropy te1 = TransferEntropy(Sy, 6, Sx, 6);
    TransferEntropy te2 = TransferEntropy(Sx, 6, Sy, 6);

    double (TransferEntropy::*T_func1)(double*, double*, double*, double*, int) = &TransferEntropy::T1;
    double (TransferEntropy::*T_func2)(double*, double*, double*, double*, int) = &TransferEntropy::T2;
    double pt_bias;

    double te_ = te1.TE(bins, 2, T, T_func1, &pt_bias);
    ASSERT_NEAR(te_, 0.0980449991346, 0.0000001);
    ASSERT_NEAR(pt_bias,0, 0.0000001);

    te_ = te1.TE(bins, 2, T, T_func2, &pt_bias);
    ASSERT_NEAR(te_, 0.0980449991346, 0.0000001);
    ASSERT_NEAR(pt_bias, 0, 0.0000001);

    te_ = te2.TE(bins, 2,  T, T_func1, &pt_bias);
    ASSERT_NEAR(te_, 0.0590090465783, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0240449173481, 0.0000001);

    te_ = te2.TE(bins, 2, T, T_func2, &pt_bias);
    ASSERT_NEAR(te_, 0.0590090465783, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0240449173481, 0.0000001);

}

TEST(TransferEntropyTest1, Standard4) {
    double Sy [] = {10, 15, 20, 25, 30, 35, 40};
    int len_Sy = 7;
    double Sx [] = {2,5,9,20,22,27,32,37};
    int len_Sx = 8;
    int bins [] = {4,4,4,4};
    int len_bins = 4;
    int T = 40;
    TransferEntropy te1 = TransferEntropy(Sy, len_Sy, Sx, len_Sx);
    TransferEntropy te2 = TransferEntropy(Sx, len_Sx, Sy, len_Sy);

    double (TransferEntropy::*T_func1)(double*, double*, double*, double*, int) = &TransferEntropy::T1;
    double (TransferEntropy::*T_func2)(double*, double*, double*, double*, int) = &TransferEntropy::T2;
    double pt_bias;

    double te_ = te1.TE(bins, len_bins, T, T_func1, &pt_bias);
    cout << te_ << endl;
    ASSERT_NEAR(te_, 0.380774404996, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.305185489419, 0.0000001);

    te_ = te1.TE(bins, len_bins,  T, T_func2, &pt_bias);
    ASSERT_NEAR(te_, 0.380774404996, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.305185489419, 0.0000001);


    te_ = te2.TE(bins, len_bins,T, T_func1, &pt_bias);
    ASSERT_NEAR(te_, 0.615384615385, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.16646481241, 0.0000001);

    te_ = te2.TE(bins, len_bins, T, T_func2, &pt_bias);
    ASSERT_NEAR(te_, 0.615384615385, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.16646481241, 0.0000001);

}

TEST(TransferEntropyTest1, Standard5) {
    double Sy [] = {0, 2, 4, 5, 13, 17, 20, 23, 26, 30, 31, 32, 33, 37, 38, 40, 44, 45, 46, 48, 52, 56, 57, 64, 69, 70, 72, 73, 77, 78, 79, 80, 82, 85, 92, 95, 97};
    int len_Sy = 37;
    double Sx [] = {1, 2, 4, 5, 7, 9, 11, 12, 14, 25, 27, 29, 31, 35, 36, 43, 45, 46, 48, 51, 58, 59, 61, 63, 64, 69, 72, 76, 77, 78, 81, 82, 83, 86, 89, 93, 94, 95, 96};
    int len_Sx = 39;
    int T = 100;

    TransferEntropy te1 = TransferEntropy(Sy, len_Sy, Sx, len_Sx);
    TransferEntropy te2 = TransferEntropy(Sx, len_Sx, Sy, len_Sy);
    double pt_bias;

    double (TransferEntropy::*T_func1)(double*, double*, double*, double*, int) = &TransferEntropy::T1;
    double (TransferEntropy::*T_func2)(double*, double*, double*, double*, int) = &TransferEntropy::T2;


    int bins1 [] = {1, 10, 15};
    int len_bins1 = 3;
    
    double te_ = te1.TE(bins1, len_bins1,T, T_func1, &pt_bias);
    ASSERT_NEAR(te_, 0.0092008313723, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0, 0.0000001);

    te_ = te1.TE(bins1, len_bins1, T, T_func2, &pt_bias);
    ASSERT_NEAR(te_, 0.0092008313723, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0, 0.0000001);


    te_ = te2.TE(bins1, len_bins1,  T, T_func1,&pt_bias);;
    ASSERT_NEAR(te_, 0.0, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0, 0.0000001);

    te_ = te2.TE(bins1, len_bins1,  T, T_func2, &pt_bias);;
    ASSERT_NEAR(te_, 0.0, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0, 0.0000001);



    int bins2 [] = {1,1,5,8};
    int len_bins2 = 4;
    
    te_ = te1.TE(bins2, len_bins2,  T, T_func1, &pt_bias);;
    ASSERT_NEAR(te_, 0.100474069503, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0580394556679, 0.0000001);
    
    te_ = te1.TE(bins2, len_bins2, T, T_func2,&pt_bias);;
    ASSERT_NEAR(te_, 0.100474069503, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0580394556679, 0.0000001);


    te_ = te2.TE(bins2, len_bins2,  T, T_func1, &pt_bias);;
    ASSERT_NEAR(pt_bias, 0.0497481048582, 0.0000001);
    ASSERT_NEAR(te_, 0.0741316822663, 0.0000001);
    
    te_ = te2.TE(bins2, len_bins2,T, T_func2, &pt_bias);;
    ASSERT_NEAR(te_, 0.0741316822663, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0497481048582, 0.0000001);


    int bins3 [] = {1,20,30};
    int len_bins3 = 3;
    
    te_ = te1.TE(bins3, len_bins3,  T, T_func1, &pt_bias);;
    ASSERT_NEAR(te_, 0, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0, 0.0000001);

    te_ = te1.TE(bins3, len_bins3, T, T_func2, &pt_bias);;
    ASSERT_NEAR(te_, 0, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0, 0.0000001);


    te_ = te2.TE(bins3, len_bins3,  T, T_func1, &pt_bias);;
    ASSERT_NEAR(te_, 0, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0, 0.0000001);

    te_ = te2.TE(bins3, len_bins3, T, T_func2, &pt_bias);;
    ASSERT_NEAR(te_, 0, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0, 0.0000001);

}

TEST(TransferEntropyTest1, Standard6) {
    double Sy [] = {512, 515, 7, 16, 529, 542, 47, 574, 578, 70, 72, 78, 597, 98, 105, 624, 118, 120, 122, 124, 125, 642, 140, 653, 656, 147, 672, 163, 675, 169, 683, 685, 185, 699, 188, 702, 193, 708, 198, 201, 207, 720, 722, 728, 731, 737, 226, 742, 231, 755, 248, 768, 256, 257, 265, 783, 281, 798, 814, 824, 834, 334, 846, 340, 856, 859, 862, 353, 871, 363, 365, 366, 879, 881, 889, 378, 902, 391, 907, 399, 410, 413, 933, 423, 941, 942, 944, 440, 967, 979, 470, 986, 991, 998, 495, 504};
    int len_Sy = 96;
    double Sx [] = {513, 514, 516, 518, 6, 531, 546, 547, 554, 555, 46, 558, 560, 561, 559, 55, 568, 576, 65, 68, 84, 599, 88, 95, 613, 614, 113, 116, 630, 130, 645, 138, 146, 148, 664, 156, 157, 173, 698, 700, 188, 711, 712, 717, 730, 221, 228, 751, 752, 766, 272, 276, 788, 792, 799, 806, 812, 300, 305, 824, 325, 327, 846, 336, 341, 854, 857, 347, 869, 886, 374, 896, 898, 396, 909, 404, 936, 942, 433, 442, 955, 965, 966, 967, 454, 975, 471, 991, 482, 497, 499};
    int len_Sx = 91;
    int T = 1000;

    TransferEntropy te1 = TransferEntropy(Sy, len_Sy, Sx, len_Sx);
    TransferEntropy te2 = TransferEntropy(Sx, len_Sx, Sy, len_Sy);
    double pt_bias;

    double (TransferEntropy::*T_func1)(double*, double*, double*, double*, int) = &TransferEntropy::T1;
    double (TransferEntropy::*T_func2)(double*, double*, double*, double*, int) = &TransferEntropy::T2;


    int bins1 [] = {1,1,1};
    int len_bins1 = 3;
    
    double te_ = te1.TE(bins1, len_bins1, T, T_func1,&pt_bias);
    ASSERT_NEAR(te_, 0.00409879953443, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.00288827836014, 0.0000001);

    te_ = te1.TE(bins1, len_bins1, T, T_func2, &pt_bias);
    ASSERT_NEAR(te_, 0.00409879953443, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.00288827836014, 0.0000001);


    te_ = te2.TE(bins1, len_bins1, T, T_func1, &pt_bias);
    ASSERT_NEAR(te_, 0.0086617579233, 0.0000001);    
    ASSERT_NEAR(pt_bias, 0.00288827836014, 0.0000001);

    te_ = te2.TE(bins1, len_bins1, T, T_func2, &pt_bias);
    ASSERT_NEAR(te_, 0.0086617579233, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.00288827836014, 0.0000001);


    int bins2 [] = {1,2,4};
    int len_bins2 = 3;
    
    te_ = te1.TE(bins2, len_bins2, T, T_func1,&pt_bias);
    ASSERT_NEAR(te_, 0.00627071829187, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.00652475144121, 0.0000001);
    te_ = te1.TE(bins2, len_bins2,  T, T_func2,&pt_bias);
    ASSERT_NEAR(te_, 0.00627071829187, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.00652475144121, 0.0000001);

    te_ = te2.TE(bins2, len_bins2, T, T_func1, &pt_bias);
    ASSERT_NEAR(te_, 0.0184209338786, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.00507480667649, 0.0000001);

    te_ = te2.TE(bins2, len_bins2, T, T_func2, &pt_bias);
    ASSERT_NEAR(te_, 0.0184209338786, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.00507480667649, 0.0000001);


    int bins3 [] = {1,2,3,4,10};
    int len_bins3 = 5;
    
    te_ = te1.TE(bins3, len_bins3, T, T_func1, &pt_bias);
    ASSERT_NEAR(te_, 0.0936929753158, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0301173608332, 0.0000001);

    te_ = te1.TE(bins3, len_bins3, T, T_func2,&pt_bias);
    ASSERT_NEAR(te_, 0.0936929753158, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0301173608332, 0.0000001);

    te_ = te2.TE(bins3, len_bins3, T, T_func1, &pt_bias);
    ASSERT_NEAR(te_, 0.0775064179923, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0293827910568, 0.0000001);

    te_ = te2.TE(bins3, len_bins3, T, T_func2,&pt_bias);
    ASSERT_NEAR(te_, 0.0775064179923, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0293827910568, 0.0000001);

}


TEST(TransferEntropyTest1, Standard7) 
{
    double Sy [] = {0, 2, 4, 5, 13, 17, 20, 23, 26, 30, 31, 32, 33, 37, 38, 40, 44, 45, 46, 48, 52, 56, 57, 64, 69, 70, 72, 73, 77, 78, 79, 80, 82, 85, 92, 95, 97};
    int len_Sy = 37;
    double Sx [] = {1, 2, 4, 5, 7, 9, 11, 12, 14, 25, 27, 29, 31, 35, 36, 43, 45, 46, 48, 51, 58, 59, 61, 63, 64, 69, 72, 76, 77, 78, 81, 82, 83, 86, 89, 93, 94, 95, 96};
    int len_Sx = 39;
    int T = 100;

    int bins[4];
    int len_bins = 4;
    Binning::get_logarithmic_bins(20, 2, 4, bins);

    TransferEntropy te1 = TransferEntropy(Sy, len_Sy, Sx, len_Sx);
    TransferEntropy te2 = TransferEntropy(Sx, len_Sx, Sy, len_Sy);
    double pt_bias;

    double (TransferEntropy::*T_func1)(double*, double*, double*, double*, int) = &TransferEntropy::T1;
    double (TransferEntropy::*T_func2)(double*, double*, double*, double*, int) = &TransferEntropy::T2;


    double te_ = te1.TE(bins, len_bins, T, T_func1, &pt_bias);
    ASSERT_NEAR(te_, 0.0, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.011271055006945026, 0.0000001);
    te_ = te1.TE(bins, len_bins,  T, T_func2, &pt_bias);
    ASSERT_NEAR(te_, 0.0, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.011271055006945026, 0.0000001);

    te_ = te2.TE(bins, len_bins, T, T_func1, &pt_bias);
    ASSERT_NEAR(te_, 0.024922529365165924, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.011271055006945026, 0.0000001);
    te_ = te2.TE(bins, len_bins,T, T_func2, &pt_bias);
    ASSERT_NEAR(te_, 0.024922529365165924, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.011271055006945026, 0.0000001);


    int bins3[3];
    int len_bins3 = 3;
    Binning::get_equal_bins(2,3, bins3);
    te_ = te1.TE(bins3, len_bins3,  T, T_func1, &pt_bias);
    ASSERT_NEAR(te_, 0.178185161823, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.075140366713, 0.0000001);
    te_ = te1.TE(bins3, len_bins3,  T, T_func2, &pt_bias);
    ASSERT_NEAR(te_, 0.178185161823, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.075140366713, 0.0000001);

    te_ = te2.TE(bins3, len_bins3,  T, T_func1, &pt_bias);
    ASSERT_NEAR(te_,  0.132255376361, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0826544033843, 0.0000001);
    te_ = te2.TE(bins3, len_bins3, T, T_func2, &pt_bias);
    ASSERT_NEAR(te_, 0.132255376361, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0826544033843, 0.0000001);


    int bins2[2];
    int len_bins2 = (5 - 1) / 2;
    Binning::get_linear_bins(1, 5, 2, bins2);

    te_ = te1.TE(bins2, len_bins2, T, T_func1, &pt_bias);
    ASSERT_NEAR(te_, 0.0129588077822, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0147213779683, 0.0000001);
    te_ = te1.TE(bins2, len_bins2, T, T_func2, &pt_bias);
    ASSERT_NEAR(te_,0.0129588077822, 0.0000001);
    ASSERT_NEAR(pt_bias, 0.0147213779683, 0.0000001);

    te_ = te2.TE(bins2, len_bins2,  T, T_func1, &pt_bias);
    ASSERT_NEAR(te_, 0, 0.000564815552854);
    ASSERT_NEAR(pt_bias, 0.0, 0.0147213779683);
    te_ = te2.TE(bins2, len_bins2, T, T_func2, &pt_bias);
    ASSERT_NEAR(te_, 0, 0.000564815552854);
    ASSERT_NEAR(pt_bias, 0.0, 0.0147213779683);

}
 


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}