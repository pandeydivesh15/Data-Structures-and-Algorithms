#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

bool compare_func(pair<int,int> a, pair<int,int> b){
	return (a.first < b.first);
}

vector<pair<int,int>> convex_hull_finder(vector<pair<int,int>> all_points){
	int l = all_points.size();
	// Base case.
	if(l <= 3)
		return all_points;

	sort(all_points.begin(), all_points.end(), compare_func);
	vector<pair<int,int>>::iterator itr = all_points.begin();

	vector<pair<int,int>> A, B;
	A.insert(A.begin(), itr, itr + (int)(l/2));
	B.insert(B.begin(), itr + (int)(l/2), all_points.end());

	// for (std::vector<pair<int,int>>::iterator i = B.begin(); i != B.end(); ++i)
	// {
	// 	cout<<(*i).first<<'%'<<(*i).second<<'\n';
	// }
	A = convex_hull_finder(A);
	B = convex_hull_finder(B);

	int minm = 50000, maxm = -1;
	pair<int,int> x_max_in_A, x_min_in_B;
	for (std::vector<pair<int,int>>::iterator i = A.begin(); i != A.end(); ++i)
	{
		if ((*i).first > maxm)
		{
			x_max_in_A.first = (*i).first;
			x_max_in_A.second = (*i).second;
			maxm = (*i).first;
		}
	}
	for (std::vector<pair<int,int>>::iterator i = B.begin(); i != B.end(); ++i)
	{
		if ((*i).first < minm)
		{
			x_min_in_B.first = (*i).first;
			x_min_in_B.second = (*i).second;
			minm = (*i).first;
		}
	}
	




}

int main()
{
		
	vector<pair<int,int>> v = {pair<int,int>(1,2), pair<int,int>(2,5), pair<int,int>{212,23}, pair<int,int>(121,2), pair<int,int>(11,4)};
	convex_hull_finder(v);
	return 0;
}