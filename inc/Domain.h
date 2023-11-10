#include "Element.h"

template<class T>
class Domain {
public:
    Domain();
    Domain(int N, T E, T A, T L);
    Element<T>& get_element(int i) const;
    int get_N() const;
    int nodes_count() const;
    T get_E() const;
    T get_A() const;
    T get_L() const;
    ~Domain();
private:
    int N; // number of elements
    T E, A, L;
    Element<T>* elements;
};

template<class T>
Domain<T>::Domain() {}

template<class T>
Domain<T>::Domain(int N, T E, T A, T L) {
    this->N = N;
    this->E = E;
    this->A = A;
    this->L = L;
    this->elements = new Element<T>[N];

    for(int i = 0; i < N; i++) {
        this->elements[i] = Element<T>(L / N, 2);
    }
}

template<class T>
Element<T>& Domain<T>::get_element(int i) const {
    return this->elements[i];
}

template<class T>
int Domain<T>::get_N() const {
    return this->N;
}

template<class T>
int Domain<T>::nodes_count() const {
    return this->N + 1;
}
template<class T>
T Domain<T>::get_E() const {
    return this->E;
}
template<class T>
T Domain<T>::get_A() const {
    return this->A;
}
template<class T>
T Domain<T>::get_L() const {
    return this->L;
}
template<class T>
Domain<T>::~Domain() {
    delete[] this->elements;
}
