#ifndef ROD
#define ROD

template<class T>
class Rod {
public:
    Rod(T, T, T);  // constructor

private: 
    T L;  // length of the 1D rod
    T E;  // Young's modulus
    T A0;  // area constant
};

#endif