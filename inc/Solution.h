#include "Domain.h"
#include <Eigen/Dense>
using namespace Eigen;
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
    Matrix<T, Dynamic, Dynamic> global_stiffness_matrix;
    Matrix<T, Dynamic, 1> displacement_vector, force_vector;
    /* global_stiffness_matrix * displacement_vector = force_vector */
};


template<class T>
Solution<T>::Solution(const Domain<T>& dom, T load, int prob) {
    printf("\ntest\n");
    this->dom = dom;
    this->load = load;
    this->prob = prob;
    int n = dom.nodes_count();
    printf("\nnodes count: %d\n", n);
    this->global_stiffness_matrix = Matrix<T, Dynamic, Dynamic>::Zero(n, n); // all values = 0
    printf("PASSED\n");
    this->force_vector = this->displacement_vector = Matrix<T, Dynamic, 1>::Zero(n, 1);
    printf("PASSED\n");

}

template<class T>
void Solution<T>::generate_global_stiffness_matrix() {
    for(int i = 0; i < dom.get_N(); i++) {
        /* first set the stiffness matrix for ith element */
        printf("\ngenerating global stiffness matrix\n");
        Element<T> element = this->dom.get_element(i);
        if(this->prob == 1) 
            element.set_stiffness_matrix(dom.get_E(), dom.get_A(), dom.get_L());
        else if(prob == 2)
            element.set_stiffness_matrix(dom.get_E(), dom.get_A() * (1 + i), dom.get_L());
        
        // printf("\nvalue: %f", element.stiffness_matrix_cell(0,0));
        /* use this to find the global stiffness matrix */
        this->global_stiffness_matrix(i, i)         += element.stiffness_matrix_cell(0, 0);
        this->global_stiffness_matrix(i, i + 1)     += element.stiffness_matrix_cell(0, 1);
        this->global_stiffness_matrix(i + 1, i)     += element.stiffness_matrix_cell(1, 0);
        this->global_stiffness_matrix(i + 1, i + 1) += element.stiffness_matrix_cell(1, 1);

        printf("\nend\n");
    }
}

template<class T>
void Solution<T>::generate_force_vector() {
    printf("\ncalculating force vector\n");
    this->force_vector(0, 0) = this->load;
    this->force_vector(dom.nodes_count() - 1, 0) = -this->load;
    printf("\nforce vector: \n");
}

template<class T>
void Solution<T>::solve() {
    this->generate_global_stiffness_matrix();
    this->generate_force_vector();
    this->displacement_vector = this->global_stiffness_matrix.completeOrthogonalDecomposition().pseudoInverse() * (this->force_vector);
    printf("calculated disp vec\n");
}

template<class T>
void Solution<T>::show_matrices() const {
    std::cout << "GLOBAL STIFFNESS MATRIX:\n" << this->global_stiffness_matrix << "\n\n";
    std::cout << "FORCE VECTOR:\n" << this->force_vector << "\n\n";
    std::cout << "DISPLACEMENT VECTOR:\n" << this->displacement_vector << std::endl;
}

template<class T>
Solution<T>::~Solution() {}