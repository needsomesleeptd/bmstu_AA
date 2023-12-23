#include <vector>
#include <string>

void compute_evd(std::vector<std::vector<float>> matrix,
	std::vector<float>& eigenvalues, std::vector<std::vector<float>>& eigenvectors, std::size_t eig_count);

void get_inverse_diagonal_matrix(std::vector<std::vector<float>> matrix,
	std::vector<std::vector<float>>& inv_matrix);

void get_hermitian_matrix_inverse(std::vector<float> eigenvector,
	std::vector<std::vector<float>>& ih_matrix);

void get_reduced_matrix(std::vector<std::vector<float>> matrix,
	std::vector<std::vector<float>>& r_matrix, std::size_t new_size);

void print_matrix(std::vector<std::vector<float>>	matrix);


void jordan_gaussian_transform(
	std::vector<std::vector<float>> matrix, std::vector<float>& eigenvector);


void matrix_transpose(std::vector<std::vector<float>> matrix1,
	std::vector<std::vector<float>>& matrix2);

void matrix_by_matrix(std::vector<std::vector<float>> matrix1,
	std::vector<std::vector<float>>& matrix2, std::vector<std::vector<float>>& matrix3);


void get_hermitian_matrix(std::vector<float> eigenvector,
	std::vector<std::vector<float>>& h_matrix);


void svd(std::vector<std::vector<float>> matrix, std::vector<std::vector<float>>& s,
	std::vector<std::vector<float>>& u, std::vector<std::vector<float>>& v);



void generate_matrix(std::vector<std::vector<float>>&
matrix, std::size_t rows, std::size_t cols);