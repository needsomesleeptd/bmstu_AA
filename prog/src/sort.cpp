

#include "sort.hpp"

#include <vector>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>

#include <valarray>




using namespace std;

void svd(std::vector<std::vector<float>> matrix, std::vector<std::vector<float>>& s,
	std::vector<std::vector<float>>& u, std::vector<std::vector<float>>& v)
{
	std::vector<std::vector<float>> matrix_t;
	matrix_transpose(matrix, matrix_t);

	std::vector<std::vector<float>> matrix_product1;
	matrix_by_matrix(matrix, matrix_t, matrix_product1);

	std::vector<std::vector<float>> matrix_product2;
	matrix_by_matrix(matrix_t, matrix, matrix_product2);

	std::vector<std::vector<float>> u_1;
	std::vector<std::vector<float>> v_1;

	std::vector<float> eigenvalues;
	compute_evd(matrix_product2, eigenvalues, v_1, 0);

	matrix_transpose(v_1, v);

	s.resize(matrix.size());
	for (std::size_t index = 0; index < eigenvalues.size(); index++)
	{
		s[index].resize(eigenvalues.size());
		s[index][index] = eigenvalues[index];
	}

	std::vector<std::vector<float>> s_inverse;
	get_inverse_diagonal_matrix(s, s_inverse);

	std::vector<std::vector<float>> av_matrix;
	matrix_by_matrix(matrix, v, av_matrix);
	matrix_by_matrix(av_matrix, s_inverse, u);
}

std::vector<std::vector<float>> matrix_i;


void compute_evd(std::vector<std::vector<float>> matrix,
	std::vector<float>& eigenvalues, std::vector<std::vector<float>>& eigenvectors, std::size_t eig_count)
{
	std::size_t m_size = matrix.size();
	std::vector<float> vec; vec.resize(m_size);
	std::generate(vec.begin(), vec.end(), []() {
	  return rand() % 100;
	});

	if (eigenvalues.size() == 0 && eigenvectors.size() == 0)
	{
		eigenvalues.resize(m_size);
		eigenvectors.resize(eigenvalues.size());
		matrix_i = matrix;
	}

	std::vector<std::vector<float>> m; m.resize(m_size);
	for (std::size_t row = 0; row < m_size; row++)
		m[row].resize(100);

	float lambda_old = 0;

	std::size_t index = 0; bool is_eval = false;
	while (is_eval == false)
	{
		for (std::size_t row = 0; row < m_size && (index % 100) == 0; row++)
			m[row].resize(m[row].size() + 100);

		for (std::size_t row = 0; row < m_size; row++)
		{
			m[row][index] = 0;
			for (std::size_t col = 0; col < m_size; col++)
				m[row][index] += matrix[row][col] * vec[col];
		}

		for (std::size_t col = 0; col < m_size; col++)
			vec[col] = m[col][index];

		if (index > 0)
		{
			float lambda = ((index - 1) > 0) ? \
				(m[0][index] / m[0][index - 1]) : m[0][index];
			is_eval = (fabs(lambda - lambda_old) < /*10e-15*/10e-10);

			eigenvalues[eig_count] = lambda; lambda_old = lambda;
		}

		index++;
	}

	std::vector<std::vector<float>> matrix_new;

	if (m_size > 1)
	{
		std::vector<std::vector<float>> matrix_tfloatet;
		matrix_tfloatet.resize(m_size);

		for (std::size_t row = 0; row < m_size; row++)
		{
			matrix_tfloatet[row].resize(m_size);
			for (std::size_t col = 0; col < m_size; col++)
				matrix_tfloatet[row][col] = (row == col) ? \
				(matrix[row][col] - eigenvalues[eig_count]) : matrix[row][col];
		}

		std::vector<float> eigenvector;
		jordan_gaussian_transform(matrix_tfloatet, eigenvector);

		std::vector<std::vector<float>> hermitian_matrix;
		get_hermitian_matrix(eigenvector, hermitian_matrix);

		std::vector<std::vector<float>> ha_matrix_product;
		matrix_by_matrix(hermitian_matrix, matrix, ha_matrix_product);

		std::vector<std::vector<float>> inverse_hermitian_matrix;
		get_hermitian_matrix_inverse(eigenvector, inverse_hermitian_matrix);

		std::vector<std::vector<float>> iha_matrix_product;
		matrix_by_matrix(ha_matrix_product, inverse_hermitian_matrix, iha_matrix_product);

		get_reduced_matrix(iha_matrix_product, matrix_new, m_size - 1);
	}

	if (m_size <= 1)
	{
		for (std::size_t i = 0; i < eigenvalues.size(); i++)
		{
			float lambda = eigenvalues[i];
			std::vector<std::vector<float>> matrix_tfloatet;
			matrix_tfloatet.resize(matrix_i.size());

			for (std::size_t row = 0; row < matrix_i.size(); row++)
			{
				matrix_tfloatet[row].resize(matrix_i.size());
				for (std::size_t col = 0; col < matrix_i.size(); col++)
					matrix_tfloatet[row][col] = (row == col) ? \
					(matrix_i[row][col] - lambda) : matrix_i[row][col];
			}

			eigenvectors.resize(matrix_i.size());
			jordan_gaussian_transform(matrix_tfloatet, eigenvectors[i]);

			float eigsum_sq = 0;
			for (std::size_t v = 0; v < eigenvectors[i].size(); v++)
				eigsum_sq += pow(eigenvectors[i][v], 2.0);

			for (std::size_t v = 0; v < eigenvectors[i].size(); v++)
				eigenvectors[i][v] /= sqrt(eigsum_sq);

			eigenvalues[i] = sqrt(eigenvalues[i]);
		}

		return;
	}

	compute_evd(matrix_new, eigenvalues, eigenvectors, eig_count + 1);

	return;
}


void matrix_transpose(std::vector<std::vector<float>> matrix1,
	std::vector<std::vector<float>>& matrix2)
{
	matrix2.resize(matrix1.size());
	for (std::size_t row = 0; row < matrix1.size(); row++)
	{
		matrix2[row].resize(matrix1[row].size());
		for (std::size_t col = 0; col < matrix1[row].size(); col++)
			matrix2[row][col] = matrix1[col][row];
	}
}


void matrix_by_matrix(std::vector<std::vector<float>> matrix1,
	std::vector<std::vector<float>>& matrix2, std::vector<std::vector<float>>& matrix3)
{
	matrix3.resize(matrix1.size());
	for (std::size_t row = 0; row < matrix1.size(); row++)
	{
		matrix3[row].resize(matrix1[row].size());
		for (std::size_t col = 0; col < matrix1[row].size(); col++)
		{
			matrix3[row][col] = 0.00;
			for (std::size_t k = 0; k < matrix1[row].size(); k++)
				matrix3[row][col] += matrix1[row][k] * matrix2[k][col];
		}
	}
}


void get_hermitian_matrix(std::vector<float> eigenvector,
	std::vector<std::vector<float>>& h_matrix)
{
	h_matrix.resize(eigenvector.size());
	for (std::size_t row = 0; row < eigenvector.size(); row++)
		h_matrix[row].resize(eigenvector.size());

	h_matrix[0][0] = 1.0 / eigenvector[0];
	for (std::size_t row = 1; row < eigenvector.size(); row++)
		h_matrix[row][0] = -eigenvector[row] / eigenvector[0];

	for (std::size_t row = 1; row < eigenvector.size(); row++)
		h_matrix[row][row] = 1;
}


void get_hermitian_matrix_inverse(std::vector<float> eigenvector,
	std::vector<std::vector<float>>& ih_matrix)
{
	ih_matrix.resize(eigenvector.size());
	for (std::size_t row = 0; row < eigenvector.size(); row++)
		ih_matrix[row].resize(eigenvector.size());

	ih_matrix[0][0] = eigenvector[0];
	for (std::size_t row = 1; row < eigenvector.size(); row++)
		ih_matrix[row][0] = -eigenvector[row];

	for (std::size_t row = 1; row < eigenvector.size(); row++)
		ih_matrix[row][row] = 1;
}


void jordan_gaussian_transform(
	std::vector<std::vector<float>> matrix, std::vector<float>& eigenvector)
{
	const float eps = 10e-6; bool eigenv_found = false;
	for (std::size_t s = 0; s < matrix.size() - 1 && !eigenv_found; s++)
	{
		std::size_t col = s; float alpha = matrix[s][s];
		while (col < matrix[s].size() && alpha != 0 && alpha != 1)
			matrix[s][col++] /= alpha;

		for (std::size_t c = s; col < matrix[s].size() && !alpha; col++)
			std::swap(matrix[s][col], matrix[s + 1][col]);

		for (std::size_t row = 0; row < matrix.size(); row++)
		{
			float gamma = matrix[row][s];
			for (std::size_t c = s; c < matrix[row].size() && row != s; c++)
				matrix[row][c] = matrix[row][c] - matrix[s][c] * gamma;
		}
	}

	std::size_t row = 0;
	while (row < matrix.size())
		eigenvector.push_back(-matrix[row++][matrix.size() - 1]);

	eigenvector[eigenvector.size() - 1] = 1;
}


void get_inverse_diagonal_matrix(std::vector<std::vector<float>> matrix,
	std::vector<std::vector<float>>& inv_matrix)
{
	inv_matrix.resize(matrix.size());
	for (std::size_t index = 0; index < matrix.size(); index++)
	{
		inv_matrix[index].resize(matrix[index].size());
		inv_matrix[index][index] = 1.0 / matrix[index][index];
	}
}


void get_reduced_matrix(std::vector<std::vector<float>> matrix,
	std::vector<std::vector<float>>& r_matrix, std::size_t new_size)
{
	if (new_size > 1)
	{
		r_matrix.resize(new_size);
		std::size_t index_d = matrix.size() - new_size;
		std::size_t row = index_d, row_n = 0;
		while (row < matrix.size())
		{
			r_matrix[row_n].resize(new_size);
			std::size_t col = index_d, col_n = 0;
			while (col < matrix.size())
				r_matrix[row_n][col_n++] = matrix[row][col++];

			row++; row_n++;
		}
	}

	else if (new_size == 1)
	{
		r_matrix.resize(new_size);
		r_matrix[0].resize(new_size);
		r_matrix[0][0] = matrix[1][1];
	}
}


void generate_matrix(std::vector<std::vector<float>>&
matrix, std::size_t rows, std::size_t cols)
{
	std::srand((unsigned int)std::time(nullptr)); matrix.resize(rows);
	for (std::size_t row = 0; row < matrix.size(); row++)
	{
		matrix[row].resize(cols);
		for (std::size_t col = 0; col < matrix[row].size(); col++)
			matrix[row][col] = std::rand() % 10;
	}
}


void print_matrix(std::vector<std::vector<float>>	matrix)
{
	for (std::size_t row = 0; row < matrix.size(); row++)
	{
		for (std::size_t col = 0; col < matrix[row].size(); col++)
			std::cout << std::setprecision(5) << matrix[row][col] << " ";

		std::cout << "\n";
	}

	std::cout << "\n";
}

void scanMatrix(std::vector<std::vector<float>>& matrix)
{
	float val;
	int m = matrix[0].size();
	for (size_t i = 0; i < matrix.size(); i++)
		for (size_t j = 0; j < m; j++)
		{
			std::cin >> val;
			matrix[i][j] = val;
		}
}