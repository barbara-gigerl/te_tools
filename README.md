# Transfer Entropy Tools

Implementation of a framework for transfer entropy computations in C++ and Python according to [1].
Both the C++ and Python code implement the same things, but sometimes it might be preferable to use a specific language.

## Structure of C++ code
Directories:
* include: .h files
* src: .cpp files - actual implementation
* test: tests for the computation of binned RV and transfer entropy

The most important files are `transfer_entropy.cpp` and `binning.cpp`.
Test data can be generated using the `test_data*.cpp` files for Influencer-Follower and Coupled model in a network or two-user scenario.

## Structure of Python code
The most important files are `transfer_entropy.py` and `binning.py`.
Test data can be generated using the `test_data*.py` files for Influencer-Follower and Coupled model in a network or two-user scenario.

## Usage examples
```C++
double Sy [] = {10, 15, 20, 25, 30, 35, 40};
int len_Sy = 7;

double Sx [] = {2,5,9,20,22,27,32,37};
int len_Sx = 8;

int bins [] = {4,4,4,4};
int len_bins = 4;

int T = 40; 

double (TransferEntropy::*T_func1)(double*, double*, double*, double*, int) = &TransferEntropy::T1;
double pt_bias;

TransferEntropy te = TransferEntropy(Sy, len_Sy, Sx, len_Sx);
double TE_X_Y = te.TE(bins, len_bins, T, T_func1, &pt_bias);
```
```python
import transfer_entropy as te

Sy = [10, 15, 20, 25, 30, 35, 40]
Sx = [2,5,9,20,22,27,32,37]
bins = [4,4,4,4] 
T = 40

TE_X_Y, pt_bias = te.TE(Sy, Sx, bins, T, te.T1)
```






[1] https://arxiv.org/abs/1110.2724
