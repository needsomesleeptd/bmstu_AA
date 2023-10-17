#include <vector>
#include <string>
#include <algorithm>


const int INF = 1e8;

struct Matrix
{
 public:
	Matrix(int n, int m);

	void printMatrix();
	Matrix dot(const Matrix& other);
	Matrix dot_vin(const Matrix& other);
	Matrix dot_vin_opt(const Matrix& other);
	Matrix dot_shtrassen(const Matrix& other);
	void split_matrix(Matrix &mat1, Matrix& mat2);

	size_t _n;
	size_t _m;
	std::vector<std::vector<int>> _table;

};