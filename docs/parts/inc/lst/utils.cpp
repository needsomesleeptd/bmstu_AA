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