template<class T>
class Element {
public:
Element();
Element(T length, int n);
T gauss_quad(T E, T A, T L);
void set_stiffness_matrix(T E, T A, T L);
T stiffness_matrix_cell(int i, int j) const;
~Element();

private:
    T length;
    T** stiffness_matrix;  
    int num_of_nodes;
};

template<class T>
Element<T>::Element() {}

template<class T>
Element<T>::Element(T length, int n) {
    this->length = length;
    this->num_of_nodes = n;
    /* memory allocation on heap */
    stiffness_matrix = new T*[n];
    for(int i = 0; i < n; i++) 
        stiffness_matrix[i] = new T[n];

    /* initialization */
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            stiffness_matrix[i][j] = T();
}

template<class T>
T Element<T>::gauss_quad(T E, T A, T L) {
    // one point gauss_quad
    return E * A / L;
}
template<class T>
void Element<T>::set_stiffness_matrix(T E, T A, T L) {
    for(int i = 0; i < this->num_of_nodes; i++) 
        for(int j = 0; j < this->num_of_nodes; j++)    
            this->stiffness_matrix[i][j] = gauss_quad(E, A, L) * ((i + j) % 2 ? -1 : 1);
}
template<class T>
T Element<T>::stiffness_matrix_cell(int i, int j) const {
    return this->stiffness_matrix[i][j];
}

template<class T>
Element<T>::~Element() {
    for(int i = 0; i < num_of_nodes; i++) 
        delete[] stiffness_matrix[i];
    delete[] stiffness_matrix;
}