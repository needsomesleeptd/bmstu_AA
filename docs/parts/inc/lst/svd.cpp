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