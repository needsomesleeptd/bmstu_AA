int binSearch(std::vector<int>& v, int x, std::vector<std::pair<int,int>>& res)
{
	int low = 0;
	int high = (int)v.size() - 1;
	int cmpCount = 0;
	while (low <= high)
	{
		int mid = (high + low) / 2;
		res.emplace_back(mid,cmpCount);
		++cmpCount;

		if (v[mid] == x)
			return mid;

		if (v[mid] < x)
			low = mid + 1;

		else
			high = mid - 1;
	}
	++cmpCount;

	return -1;

}