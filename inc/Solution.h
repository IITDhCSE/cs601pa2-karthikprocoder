#include "Rod.h"

template<class T>
class Solution {
public:
    Solution(Rod<T>, T, int, int);
    void intitialize();
private:
    int num_of_elements;
    int prob;
    Rod<T> rod;
    T P;
};

