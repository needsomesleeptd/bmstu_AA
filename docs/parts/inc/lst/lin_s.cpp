int search(std::vector<int>& v, int x, std::vector<std::pair<int,int>>& res)
{

	int cmpCount = 0;
	for (int i = 0; i < v.size(); i++)
	{
		++cmpCount;
		res.emplace_back(i,cmpCount);
		if (v[i] == x)
			return i;
	}
	return -1;
}