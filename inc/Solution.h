#include "Domain.h"
#include <Eigen/Dense>
/* include path: /home/resiliente/cs601software/eigen-3.3.9 */

template<class T>
class Solution {
public:
    Solution(const Domain<T>& dom, T load, int prob);
    void generate_global_stiffness_matrix();
    void generate_force_vector();
    void solve();
    void show_matrices() const;
    ~Solution();

private:
    int prob;
    T load;
    Domain<T> dom;
    Eigen::Matrix<T, -1, -1> global_stiffness_matrix;
    Eigen::Matrix<T, -1, 1> displacement_vector;
    Eigen::Matrix<T, -1, 1> force_vector;
    /* global_stiffness_matrix * displacement_vector = force_vector */
};


template<class T>
Solution<T>::Solution(const Domain<T>& dom, T load, int prob) {
    this->dom = dom;
    this->load = load;
    this->prob = prob;
    int n = dom.nodes_count();
    this->global_stiffness_matrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Zero(n, n); // all values = 0
    this->force_vector = this->displacement_vector = Eigen::Matrix<T, Eigen::Dynamic, 1>::Zero(n, 1);
}

template<class T>
void Solution<T>::generate_global_stiffness_matrix() {
    for(int i = 0; i < dom.get_N(); i++) {
        /* first set the stiffness matrix for ith element */
        Element<T> element = this->dom.get_element(i);
        if(this->prob == 1) 
            element.set_stiffness_matrix(dom.get_E(), dom.get_A(), dom.get_L());
        else if(prob == 2)
            element.set_stiffness_matrix(dom.get_E(), dom.get_A() * (1 + i), dom.get_L());

        /* use this to find the global stiffness matrix */
        this->global_stiffness_matrix(i, i)         += element.stiffness_matrix_cell(0, 0);
        this->global_stiffness_matrix(i, i + 1)     += element.stiffness_matrix_cell(0, 1);
        this->global_stiffness_matrix(i + 1, i)     += element.stiffness_matrix_cell(1, 0);
        this->global_stiffness_matrix(i + 1, i + 1) += element.stiffness_matrix_cell(1, 1);
    }
}

template<class T>
void Solution<T>::generate_force_vector() {
    this->force_vector(0, 0) = this->load;
    this->force_vector(dom.nodes_count() - 1, 0) = -this->load;
}

template<class T>
void Solution<T>::solve() {
    this->generate_global_stiffness_matrix();
    this->generate_force_vector();
    this->displacement_vector = this->global_stiffness_matrix.completeOrthogonalDecomposition().pseudoInverse();
}

template<class T>
void Solution<T>::show_matrices() const {
    std::cout << "GLOBAL STIFFNESS MATRIX:\n\t" << this->global_stiffness_matrix << "\n\n";
    std::cout << "FORCE VECTOR:\n\t" << this->force_vector << "\n\n";
    std::cout << "DISPLACEMENT VECTOR:\n\t" << this->displacement_vector << std::endl;
}

template<class T>
Solution<T>::~Solution() {}