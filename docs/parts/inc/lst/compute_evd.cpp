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