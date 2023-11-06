#include "Rod.h"
#include "Solution.h"

template<class T>
Solution<T>::Solution(Rod<T> rod_, T P_, int N, int prob_) {
    rod = rod_;
    num_of_elements = N;
    prob = prob_;
    P = P_;
}