#include <gtest/gtest.h>
#include "../include/binning.h"

TEST(BinningTest1, Standard1) { 
    double Sy [] = {1, 5, 9, 17, 22, 29};
    double Sx [] = {1, 5, 9, 17, 22, 29};
    int bins [] = {1, 2, 3};
    int k = 3;
    int T = 30;
    Binning binning;
    int total = binning.compute_binning(Sy, 6, Sx, 6, bins, 3, T);
    double* prob_map = binning.get_prob_map();




    
    ASSERT_EQ(total, 26);
    ASSERT_NEAR(prob_map[63], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[62], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[61], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[60], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[59], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[58], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[57], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[56], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[55], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[54], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[53], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[52], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[51], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[50], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[49], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[48], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[47], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[46], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[45], 3.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[44], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[43], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[42], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[41], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[40], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[39], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[38], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[37], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[36], 2.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[35], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[34], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[33], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[32], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[31], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[30], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[29], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[28], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[27], 2.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[26], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[25], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[24], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[23], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[22], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[21], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[20], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[19], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[18], 7.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[17], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[16], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[15], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[14], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[13], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[12], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[11], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[10], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[9], 9.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[8], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[7], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[6], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[5], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[4], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[3], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[2], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[1], 0.0/26, 0.00000001);
    ASSERT_NEAR(prob_map[0], 3.0/26, 0.00000001);
}

TEST(BinningTest1, Standard2)
{
    double Sy [] = {1, 5, 9, 17, 22, 29};
    int bins [] = {1};
    int T = 30;
    Binning binning;
    int total = binning.compute_binning(Sy, 6, 0, 0, bins, 1, T);
    double* prob_map = binning.get_prob_map();

    ASSERT_NEAR(prob_map[0], 25.0/31.0, 0.00000001);
    ASSERT_NEAR(prob_map[2], 6.0/31.0, 0.00000001);

}

TEST(BinningTest1, Standard3)
{
    double Sy [] = {10, 20, 30, 40};
    int bins [] = {4,4,4,4};
    int T = 50;
    Binning binning;
    int total = binning.compute_binning(Sy, 4, 0, 0, bins, 4, T);
    double* prob_map = binning.get_prob_map();
    ASSERT_EQ(total, 36);
    ASSERT_NEAR(prob_map[160], 6.0/36, 0.00000001);
    ASSERT_NEAR(prob_map[144], 6.0/36, 0.00000001);
    ASSERT_NEAR(prob_map[80], 6.0/36, 0.00000001);
    ASSERT_NEAR(prob_map[64], 9.0/36, 0.00000001);
    ASSERT_NEAR(prob_map[32], 9.0/36, 0.00000001);

}

TEST(BinningTest1, Standard4) {

    double Sy [] = {10, 15, 20, 25, 30, 35, 40};
    int bins [] = {1,4};
    int T = 50;
    Binning binning;
    int total = binning.compute_binning(Sy, 7, 0, 0, bins, 2, T);
    double* prob_map = binning.get_prob_map();
    ASSERT_NEAR(prob_map[8], 7.0/47, 0.00000001);
    ASSERT_NEAR(prob_map[4], 28.0/47, 0.00000001);
    ASSERT_NEAR(prob_map[0], 11.999999999999998/47, 0.00000001);
}

TEST(BinningTest1, Standard5) {
    double Sy [] = {1, 5, 5, 5, 9, 9, 17, 17, 22, 29};
    int bins[] = {1,4};
    int T = 30;
    Binning binning;
    int total = binning.compute_binning(Sy, 10, 0, 0, bins, 2, T);
    double* prob_map = binning.get_prob_map();
    ASSERT_EQ(total, 27);

    ASSERT_NEAR(prob_map[12], 2.0/27, 0.00000001);
    ASSERT_NEAR(prob_map[8], 3.0/27, 0.00000001);
    ASSERT_NEAR(prob_map[4], 17.0/27, 0.00000001);
    ASSERT_NEAR(prob_map[0], 5.0/27, 0.00000001);
}

TEST(BinningTest1, Standard6)
{
    double Sy [] = {1, 2, 9, 10, 14, 15, 19, 21, 22, 27, 28, 29};
    int bins[] = {4,1};
    int T = 30;
    Binning binning;
    int total = binning.compute_binning(Sy, 12, 0, 0, bins, 2, T);
    double* prob_map = binning.get_prob_map();
    ASSERT_NEAR(prob_map[12], 7.0/27, 0.00000001);
    ASSERT_NEAR(prob_map[8], 16.0/27, 0.00000001);
    ASSERT_NEAR(prob_map[4], 2.0/27, 0.00000001);
    ASSERT_NEAR(prob_map[0], 2.0/27, 0.00000001);
}

TEST(BinningTest1, Standard7)
{
    double Sy [] = {6, 7, 9, 11, 19, 20, 21, 22, 23, 25, 29, 35, 36, 37, 42, 49, 52, 53, 57, 58};
    int bins[] = {5,3,9};
    int T = 60;
    Binning binning;
    int total = binning.compute_binning(Sy, 20, 0, 0, bins, 3, T);
    double* prob_map = binning.get_prob_map();
    ASSERT_NEAR(prob_map[56], 24.0/45, 0.00000001);
    ASSERT_NEAR(prob_map[40], 15.0/45, 0.00000001);
    ASSERT_NEAR(prob_map[24], 6.0/45, 0.00000001);
}

TEST(BinningTest1, Standard8)
{
    double Sy [] = {0, 1, 2, 3, 4, 7, 9, 11, 12, 21, 24, 25, 28, 32, 36, 41, 43, 46, 47, 48, 50, 53};
    int bins[] = {1,1,1};
    int T = 60;
    Binning binning;
    int total = binning.compute_binning(Sy, 22, 0, 0, bins, 3, T);
    double* prob_map = binning.get_prob_map();
    ASSERT_NEAR(prob_map[56], 4.0/59, 0.00000001);
    ASSERT_NEAR(prob_map[48], 3.0/59, 0.00000001);
    ASSERT_NEAR(prob_map[40], 4.0/59, 0.00000001);
    ASSERT_NEAR(prob_map[32], 9.0/59, 0.00000001);
    ASSERT_NEAR(prob_map[24], 4.0/59, 0.00000001);
    ASSERT_NEAR(prob_map[16], 10.0/59, 0.00000001);
    ASSERT_NEAR(prob_map[8], 10.0/59, 0.00000001);
    ASSERT_NEAR(prob_map[0], 15.0/59, 0.00000001);
}

TEST(BinningTest1, Standard9) {
    double Sy[] = {0, 2, 3, 5, 13, 14, 15, 19, 22, 24, 26, 27, 31, 33, 34, 35, 36, 44, 46, 48, 50, 52, 53};
    int bins[] = {1,9,7};
    int T = 60;
    Binning binning;
    int total = binning.compute_binning(Sy, 23, 0, 0, bins, 3, T);
    double* prob_map = binning.get_prob_map();
    ASSERT_NEAR(prob_map[56], 14.0/45, 0.00000001);
    ASSERT_NEAR(prob_map[48], 2.0/45, 0.00000001);
    ASSERT_NEAR(prob_map[24], 29.000000000000004/45, 0.00000001);
}


TEST(BinningTest1, Standard11)
{
    double Sy [] = {13, 16, 17, 18};
    int bins[] = {1,2,3};
    int T = 20;
    Binning binning;
    int total = binning.compute_binning(Sy, 4, Sy, 4, bins, 3, T);
    double* prob_map = binning.get_prob_map();
    ASSERT_NEAR(prob_map[63], 2.0/16, 0.00000001);
    ASSERT_NEAR(prob_map[45], 1.0/16, 0.00000001);
    ASSERT_NEAR(prob_map[36], 1.0/16, 0.00000001);
    ASSERT_NEAR(prob_map[27], 2.0/16, 0.00000001);
    ASSERT_NEAR(prob_map[18], 2.0/16, 0.00000001);
    ASSERT_NEAR(prob_map[0], 8.0/16, 0.00000001);
}

TEST(BinningTest1, Standard12)
{
    double Sy [] = {5, 10, 15};
    int bins[] = {1,1,1};
    int T = 20;
    Binning binning;
    int total = binning.compute_binning(Sy, 3, Sy, 3, bins, 3, T);
    double* prob_map = binning.get_prob_map();
    ASSERT_EQ(total, 19);
    ASSERT_NEAR(prob_map[36], 3.0/19, 0.00000001);
    ASSERT_NEAR(prob_map[18], 3.0/19, 0.00000001);
    ASSERT_NEAR(prob_map[9], 3.0/19, 0.00000001);
    ASSERT_NEAR(prob_map[0], 10.0/19, 0.00000001);
}

TEST(BinningTest1, Standard13) { 
    double Sy [] = {5,10,15};
    double Sx [] = {11};
    int bins [] = {1, 1, 1};
    int T = 16;
    Binning binning;
    int total = binning.compute_binning(Sy, 3, Sx, 1, bins, 3, T);
    double* prob_map = binning.get_prob_map();
    
    ASSERT_NEAR(prob_map[63], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[62], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[61], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[60], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[59], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[58], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[57], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[56], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[55], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[54], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[53], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[52], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[51], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[50], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[49], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[48], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[47], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[46], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[45], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[44], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[43], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[42], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[41], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[40], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[39], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[38], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[37], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[36], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[35], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[34], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[33], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[32], 3.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[31], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[30], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[29], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[28], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[27], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[26], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[25], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[24], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[23], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[22], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[21], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[20], 1.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[19], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[18], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[17], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[16], 2.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[15], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[14], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[13], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[12], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[11], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[10], 1.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[9], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[8], 1.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[7], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[6], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[5], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[4], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[3], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[2], 0.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[1], 1.0/15, 0.00000001);
    ASSERT_NEAR(prob_map[0], 6.0/15, 0.00000001);

}


TEST(BinningTest1, Standard14) {
    double Sy [] = {12, 81, 27, 66, 16, 69, 9, 42, 75, 15};
    double Sx [] = {84, 97, 88, 21, 32, 94, 14, 63, 51, 36};
    int bins [] = {1, 2, 3};
    int T = 100;
    Binning binning;
    sort(Sy, Sy+10);
    sort(Sx, Sx+10);
    int total = binning.compute_binning(Sy, 10, Sx, 10, bins, 3, T);
    double* prob_map = binning.get_prob_map();


    int k = 3;

    

    ASSERT_NEAR(prob_map[58], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[42], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[40], 2.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[33], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[32], 5.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[28], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[25], 2.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[24], 3.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[17], 2.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[16], 10.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[12], 3.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[10], 2.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[9], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[8], 12.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[5], 3.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[4], 3.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[3], 4.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[2], 12.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[1], 15.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[0], 13.0/96, 0.00000001);
}
TEST(BinningTest1, Standard15) {
    double Sy [] = {62, 2, 92, 27, 57, 25, 45, 23, 69, 88};
    double Sx [] = {52, 3, 39, 41, 22, 76, 98, 44, 17, 6};
    int bins [] = {1, 2, 3};
    int T = 100;
    Binning binning;
    sort(Sy, Sy+10);
    sort(Sx, Sx+10);
    int total = binning.compute_binning(Sy, 10, Sx, 10, bins, 3, T);
    double* prob_map = binning.get_prob_map();
    ASSERT_NEAR(prob_map[57], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[49], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[40], 2.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[35], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[34], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[33], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[32], 2.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[25], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[24], 3.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[19], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[18], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[17], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[16], 9.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[13], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[11], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[10], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[9], 2.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[8], 16.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[6], 1.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[5], 2.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[4], 5.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[3], 3.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[2], 9.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[1], 10.0/96, 0.00000001);
    ASSERT_NEAR(prob_map[0], 20.0/96, 0.00000001);

}


TEST(BinningTest1, Standard16) {
double Sy [] = {86, 55, 75, 61, 22, 9, 94, 3, 63, 93};
    double Sx [] = {82, 58, 76, 30, 65, 97, 5, 49, 67, 62};
    int bins [] = {4,4,4,4};
    int T = 100;
    Binning binning;
    sort(Sy, Sy+10);
    sort(Sx, Sx+10);
    int total = binning.compute_binning(Sy, 10, Sx, 10, bins, 4, T);
    double* prob_map = binning.get_prob_map();
    ASSERT_NEAR(prob_map[238], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[236], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[233], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[205], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[201], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[194], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[173], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[166], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[161], 3.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[155], 3.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[150], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[149], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[147], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[144], 3.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[138], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[132], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[130], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[128], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[127], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[126], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[94], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[88], 3.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[83], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[82], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[77], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[74], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[73], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[69], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[67], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[66], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[64], 4.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[55], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[49], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[44], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[42], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[40], 4.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[39], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[33], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[20], 4.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[16], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[8], 4.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[4], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[2], 4.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[1], 4.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[0], 3.0/86, 0.00000001);
}


TEST(BinningTest1, Standard17) {
    double Sy [] = {54, 17, 84, 2, 57, 13, 15, 69, 80, 78, 58, 83, 1, 49, 16, 70, 34, 96, 64, 24, 29, 59, 93, 36, 81, 31, 68, 65, 48, 9, 86, 62, 22, 74, 66, 46, 92, 55, 19, 94, 14, 99, 25, 77, 10, 98, 45, 67, 4, 21};
    double Sx [] = {90, 22, 99, 36, 27, 85, 73, 74, 66, 96, 20, 1, 89, 16, 53, 40, 52, 56, 98, 59};
    int bins [] = {4,4,4,4};
    int T = 100;
    Binning binning;
    sort(Sy, Sy+50);
    sort(Sx, Sx+20);
    int total = binning.compute_binning(Sy, 50, Sx, 20, bins, 4, T);
    double* prob_map = binning.get_prob_map();
    ASSERT_NEAR(prob_map[255], 5.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[254], 8.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[253], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[252], 6.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[251], 8.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[250], 3.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[249], 4.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[248], 3.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[247], 6.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[246], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[245], 6.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[243], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[242], 3.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[241], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[236], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[233], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[231], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[222], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[219], 2.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[217], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[211], 3.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[201], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[188], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[182], 5.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[147], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[125], 3.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[124], 3.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[105], 1.0/86, 0.00000001);
    ASSERT_NEAR(prob_map[54], 1.0/86, 0.00000001);

}


TEST(BinningTest1, Standard18) {
double Sy [] = {1484, 8060, 7191, 7566, 907, 4526, 9175, 4559, 125, 2315, 4268, 9643, 7740, 3136, 3970, 3315, 2915, 7173, 2392, 8428, 4212, 7337, 1393, 5325, 6088, 4709, 7341, 4225, 3124, 7629, 3194, 555, 7139, 1016, 1816, 8874, 5472, 9015, 1570, 4602, 4091, 2406, 2279, 8736, 7010, 6030, 4191, 1360, 5089, 7196};
    double Sx [] = {9770, 5651, 468, 5545, 8823, 8722, 831, 7096, 611, 6434, 1075, 8931, 6955, 229, 4664, 562, 1512, 1453, 5975, 6052};
    int bins [] = {30,20,10};
    int T = 10000;
    Binning binning;
    int total = binning.compute_binning(Sy, 50, Sx, 20, bins, 3, T);
    double* prob_map = binning.get_prob_map();
    sort(Sy, Sy+50);
    sort(Sx, Sx+20);
    ASSERT_NEAR(prob_map[56], 16.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[48], 148.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[42], 2.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[40], 63.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[37], 1.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[36], 48.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[34], 57.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[33], 60.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[32], 982.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[24], 42.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[20], 47.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[18], 19.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[17], 9.999999999999998/9942, 0.00000001);
    ASSERT_NEAR(prob_map[16], 664.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[14], 1.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[13], 3.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[12], 14.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[10], 14.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[8], 334.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[5], 7.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[4], 479.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[2], 307.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[1], 119.0/9942, 0.00000001);
    ASSERT_NEAR(prob_map[0], 6505.0/9942, 0.00000001);
}


TEST(BinningTest1, Standard19) {
    double Sy [] = {59501, 63387, 97596, 67133, 84610, 86697, 79469, 25100, 6476, 47952, 18158, 66416, 19987, 33440, 8331, 98105, 84462, 5530, 33506, 53166, 1894, 67461, 24677, 27559, 64795, 26308, 38221, 31690, 67452, 84275, 52860, 73382, 5740, 64202, 68341, 87324, 84646, 33566, 78638, 31101, 55910, 17663, 479, 44979, 85065, 70744, 20027, 48965, 54573, 86209};
    double Sx [] = {17163, 7615, 8027, 84123, 53996, 38542, 82753, 71516, 33675, 71840, 41189, 11142, 37523, 15166, 53365, 20155, 91251, 51139, 34538, 63644};
    int bins [] = {30,20,10};
    int T = 100000;
    Binning binning;
    int total = binning.compute_binning(Sy, 50, Sx, 20, bins, 3, T);
    double* prob_map = binning.get_prob_map();
    sort(Sy, Sy+50);
    sort(Sx, Sx+20);
    ASSERT_NEAR(prob_map[48], 33.0/99942, 0.00000001);
    ASSERT_NEAR(prob_map[40], 20.0/99942, 0.00000001);
    ASSERT_NEAR(prob_map[32], 1426.0/99942, 0.00000001);
    ASSERT_NEAR(prob_map[24], 9.0/99942, 0.00000001);
    ASSERT_NEAR(prob_map[16], 947.0/99942, 0.00000001);
    ASSERT_NEAR(prob_map[8], 470.00000000000006/99942, 0.00000001);
    ASSERT_NEAR(prob_map[4], 600.0/99942, 0.00000001);
    ASSERT_NEAR(prob_map[2], 400.0/99942, 0.00000001);
    ASSERT_NEAR(prob_map[1], 200.0/99942, 0.00000001);
    ASSERT_NEAR(prob_map[0], 95837.0/99942, 0.00000001);
}




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}