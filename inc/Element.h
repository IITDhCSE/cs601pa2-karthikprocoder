template<class T>
class Element {
public:
    Element(T length, int n = 2) {}

    void set_node_loc(int node_no, T loc) {}

    T gauss_quad(T E, T A, T L);

    void set_stiffness_matrix(T E, T A, T L);

    T const stiffness_matrix_cell(int i, int j) const;
    ~Element() {}

private:
    T length;
    int num_of_nodes;
    T* node_loc;  // x coordinate of the nodes on this element
    T** stiffness_matrix;  
};