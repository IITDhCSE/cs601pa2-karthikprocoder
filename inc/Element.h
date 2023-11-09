template<class T>
class Element {
public:
    Element(T length, int n) {
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


    T gauss_quad(T E, T A, T L) {
        // one point gauss_quad
        return E * A / L;
    }

    void set_stiffness_matrix(T E, T A, T L) {
        for(int i = 0; i < this->num_of_nodes; i++) 
            for(int j = 0; j < this->num_of_nodes; j++)    
                this->stiffness_matrix[i][j] = gauss_quad(E, A, L) * ((i + j) % 2 ? -1 : 1);
    }

    T stiffness_matrix_cell(int i, int j) const {
        return this->stiffness_matrix[i][j];
    }


    ~Element() {
        for(int i = 0; i < num_of_nodes; i++) 
            delete[] stiffness_matrix[i];
        delete[] stiffness_matrix;
    }


private:
    T length;
    T** stiffness_matrix;  
    int num_of_nodes;
};