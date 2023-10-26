#include <vector>
#include <string>
#include <algorithm>


const int INF = 1e8;

struct Matrix
{
 public:
	Matrix(int n, int m);

	void printMatrix();
	void scanMatrix();
	Matrix dot(const Matrix& other) const;
	Matrix dot_vin(const Matrix& other) const;
	Matrix dot_vin_opt(const Matrix& other) const;
	Matrix dot_shtrassen(const Matrix& other) const;
	Matrix shtrassen_extend(std::size_t new_dim) const;

	size_t _n;
	size_t _m;
	std::vector<std::vector<int>> _table;

};