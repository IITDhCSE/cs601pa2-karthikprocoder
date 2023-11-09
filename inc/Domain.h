#include "Element.h"

template<class T>
class Domain {
public:
    Domain(int N, T E, T A, T L) {
        this->N = N;
        this->E = E;
        this->A = A;
        this->L = L;
        this->elements = new Element<T>[N];

        for(int i = 0; i < N; i++) {
            this->elements[i] = Element<T>(L / N, 2);
        }
    }

    Element<T>& get_element(int i) const {
        return this->elements[i];
    }

    int get_N() const {
        return this->N;
    }
    int nodes_count() const {
        return this->N + 1;
    }

    T get_E() const {
        return this->E;
    }

    T get_A() const {
        return this->A;
    }

    T get_L() const {
        return this->L;
    }

    ~Domain() {
        delete[] this->elements;
    }

private:
    int N; // number of elements
    T E, A, L;
    Element<T>* elements;
};