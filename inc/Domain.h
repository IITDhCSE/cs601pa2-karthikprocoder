#include "Element.h"
#include <vector>

template<class T>
class Domain {
public:
    Domain();
    Domain(int N, T E, T A, T L);
    Element<T> get_element(int i) const;
    int get_N() const;
    int nodes_count() const;
    T get_E() const;
    T get_A() const;
    T get_L() const;
    ~Domain();
private:
    int N; // number of elements
    T E, A, L;
    std::vector<Element<T>> elements;
};

template<class T>
Domain<T>::Domain() {}

/* parameterized constructor */
template<class T>
Domain<T>::Domain(int N, T E, T A, T L) {
    this->N = N;
    this->E = E;
    this->A = A;
    this->L = L;
    this->elements.resize(N, Element<T>(L / N, 2));
}

/* fetches the ith element of the rod */
template<class T>
Element<T> Domain<T>::get_element(int i) const {
    return this->elements[i];
}

/* Get the number of elements  */
template<class T>
int Domain<T>::get_N() const {
    return this->N;
}

/* count of total number of nodes */
template<class T>
int Domain<T>::nodes_count() const {
    return this->N + 1;
}

/* young's modulus of rod */
template<class T>
T Domain<T>::get_E() const {
    return this->E;
}

/* area constant A_0 */
template<class T>
T Domain<T>::get_A() const {
    return this->A;
}

/* length of the rod */
template<class T>
T Domain<T>::get_L() const {
    return this->L;
}

/* Destructor */
template<class T>
Domain<T>::~Domain() {}
