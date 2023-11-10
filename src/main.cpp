#include<iostream>
#include "Solution.h"
#include "time.h"

int main(int argc, char* argv[]) {
    
    clock_t start, end;
    start = clock(); 
    
    if(argc != 5) {
        std::cerr << "E, A, L, P" << std::endl;
        exit(1);
    }
    
    int prob = 0, N = 0;
    #ifndef PROB
        std::cerr << "problem number not defined" << std::endl;
        exit(1);
    #else   
        prob = (int)PROB;
    #endif

    #ifndef NUM_ELE
        std::cerr << "number of elements not defined" << std::endl;
        exit(1);
    #else
        N = (int)NUM_ELE;
    #endif

    double E, A, L, P;
    E = std::stod(argv[1]);
    A = std::stod(argv[2]);
    L = std::stod(argv[3]);
    P = std::stod(argv[4]);

    Domain<double> dom(N, E, A, L);
    Solution<double> sol(dom, P, prob);
    sol.solve();
    
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    // sol.show_displacement_vector();

    std::cout << "\nExecution Time : "<< time_taken << " sec " << std::endl;
    return 0;
}