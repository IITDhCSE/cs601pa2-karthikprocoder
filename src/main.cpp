#include<iostream>
#include "Rod.h"
#include "Solution.h"

#define PROB 1
#define N 2

double const L = 0.5;
double const A0 = 12.5E-4;
double const P = 5000;
double const E = 70;


int main() {
    int prob = 1, n = 2; // default values
    #ifdef PROB
        prob = PROB;
    #endif
    #ifdef N
        n = N;
    #endif

    Rod<double> rod(L, E, A0);
    Solution<double> sol(rod, P, N, prob);
    

}