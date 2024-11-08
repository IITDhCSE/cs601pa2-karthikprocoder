#include "Domain.h"
#include <Eigen/Dense>
using namespace Eigen;

template<class T>
class Solution {
public:
    Solution(const Domain<T>& dom, T load, int prob);
    void generate_global_stiffness_matrix();
    void generate_force_vector();
    void solve();
    void show_displacement_vector() const;
    ~Solution();

private:
    int prob;
    T load;
    Domain<T> dom;
    Matrix<T, Dynamic, Dynamic> global_stiffness_matrix;
    Matrix<T, Dynamic, 1> displacement_vector, force_vector;
    /* global_stiffness_matrix * displacement_vector = force_vector */
};


template<class T>
Solution<T>::Solution(const Domain<T>& dom, T load, int prob) {
    this->dom = dom;
    this->load = load;
    this->prob = prob;
    int n = dom.nodes_count();
    this->global_stiffness_matrix = Matrix<T, Dynamic, Dynamic>::Zero(n, n); // all values = 0
    this->force_vector = this->displacement_vector = Matrix<T, Dynamic, 1>::Zero(n, 1);

}

template<class T>
void Solution<T>::generate_global_stiffness_matrix() {
    for(int i = 0; i < dom.get_N(); i++) {
        /* first set the stiffness matrix for ith element */
        Element<T> element = this->dom.get_element(i);
        // printf("prob: %d\n", prob);
        if(this->prob == 1) 
            element.set_stiffness_matrix(dom.get_E(), dom.get_A());
        else if(prob == 2)
            element.set_stiffness_matrix(dom.get_E(), dom.get_A() * (1 + i / T(dom.get_N())));
        
        // printf("\nvalue: %f", element.stiffness_matrix_cell(0,0));
        /* use this to find the global stiffness matrix */
        this->global_stiffness_matrix(i, i)         += element.stiffness_matrix_cell(0, 0);
        this->global_stiffness_matrix(i, i + 1)     += element.stiffness_matrix_cell(0, 1);
        this->global_stiffness_matrix(i + 1, i)     += element.stiffness_matrix_cell(1, 0);
        this->global_stiffness_matrix(i + 1, i + 1) += element.stiffness_matrix_cell(1, 1);
    }
}

/* For compression force at x = 0 */
template<class T>
void Solution<T>::generate_force_vector() {
    this->force_vector(0, 0) = this->load;
    this->force_vector(dom.nodes_count() - 1, 0) = -this->load;
}

/* finds the displacement vector */
/* For the given problem, it is not difficult to solve the system of linear equations */
template<class T>
void Solution<T>::solve() {
    this->generate_global_stiffness_matrix();
    this->generate_force_vector();
    int dim = this->displacement_vector.rows();
    /* boundary condition : u = 0 at x = L */
    displacement_vector(dim-1, 0) = 0 ;
    displacement_vector(dim-2, 0) = (this->force_vector(dim-1, 0) - 0)/ this->global_stiffness_matrix(dim-1, dim-2); 

    for (int i = this->displacement_vector.rows()-2; i > 0 ; i--) {
        displacement_vector(i-1, 0) =(  this->force_vector(i, 0) - this->global_stiffness_matrix(i, i) * displacement_vector(i, 0) - this->global_stiffness_matrix(i, i+1)*this->displacement_vector(i+1)) / this->global_stiffness_matrix(i,i-1); 
    }
}

template<class T>
void Solution<T>::show_displacement_vector() const {
    std::cout << "\nDISPLACEMENT VECTOR:\n" << this->displacement_vector << std::endl;
}

template<class T>
Solution<T>::~Solution() {}