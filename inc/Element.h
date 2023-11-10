#include <Eigen/Dense>
using namespace Eigen;

template<class T>
class Element {
public:
Element();
Element(T length, int n);
T gauss_quad(T E, T A);
void set_stiffness_matrix(T E, T A);
T stiffness_matrix_cell(int i, int j) const;
~Element();

private:
    T length;
    Matrix<T, Dynamic, Dynamic> stiffness_matrix;  
    int num_of_nodes;
};

template<class T>
Element<T>::Element() {}

template<class T>
Element<T>::Element(T length, int n) {
    this->length = length;
    this->num_of_nodes = n;
    stiffness_matrix = Matrix<T, Dynamic, Dynamic>::Zero(n, n);
}

/* one point gauss quadrature */
template<class T>
T Element<T>::gauss_quad(T E, T A) {
    return E * A / length;
}

template<class T>
void Element<T>::set_stiffness_matrix(T E, T A) {
    for(int i = 0; i < this->num_of_nodes; i++) 
        for(int j = 0; j < this->num_of_nodes; j++)    
            this->stiffness_matrix(i, j) = gauss_quad(E, A) * ((i + j) % 2 ? -1 : 1);
}

/* returns Kij */
template<class T>
T Element<T>::stiffness_matrix_cell(int i, int j) const {
    return this->stiffness_matrix(i, j);
}

template<class T>
Element<T>::~Element() {}