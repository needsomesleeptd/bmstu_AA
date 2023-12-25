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