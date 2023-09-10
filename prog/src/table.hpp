#include <vector>
#include <string>


const int INF = 1e8;

struct Matrix
{
 public:
	Matrix(int n, int m);
	int findMatrixDistDamerau(const std::string& st1,const std::string& st2);
	int findMatrixDistLev(const std::string& st1, const std::string& st2);
	size_t findRecurseDistDamerau(const std::string& st1, const std::string& st2);
	size_t findRecurseDistMemDamerau(const std::string& st1,const std::string& st2);

	void printMatrix();

	int _n;
	int _m;
	std::vector<std::vector<int>> _table;

};