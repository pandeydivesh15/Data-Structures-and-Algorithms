#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

std::pair<int, int> operator -(const std::pair<int, int>& x, const std::pair<int, int>& y) {
    return std::make_pair(x.first - y.first, x.second - y.second);
}

bool compare_func(pair<int,int> a, pair<int,int> b){
	return (a.first < b.first);
}

float cross_product(pair<int,int> a, pair<int,int> b){
	return float(a.first)*b.second - float(a.second)*b.first;
}

float check_angle(pair<int,int> a, pair<int,int> b, pair<int,int> c){
	// Checks angle of turn for vectors -->ab to -->bc
	// Return False for a left turn at b and True if right turn at b
	return cross_product((c-a),(b-a));
	
}

pair<int,int> upper_tangent_calculator(vector<pair<int,int>> A, 
									   vector<pair<int,int>> B, int x_max_in_A, int x_min_in_B){
	int l1 = A.size();
	int l2 = B.size();

	int I = x_max_in_A, J = x_min_in_B;
	while((check_angle(A[I], B[J], B[(l2 + J - 1) % l2]) <= 0) || (check_angle( B[J], A[I], A[(I + 1) % l1])) >= 0) {
	    for(unsigned j = J; ; j = (l2 + j - 1) % l2) {
	    	if(check_angle(A[I], B[j], B[(l2 + j - 1) % l2]) > 0) {
	    		J = j;
	    		break;
	    	}
	    	if((l2 + j - 1) % l2 == J) {
	    		J = j;
	    		break;
	    	}
	    }
	    for(unsigned i = I; ; i = (i + 1) % l1) {
	    	if(check_angle(B[J], A[i], A[(i+1) % l1]) < 0) {
	    		I = i;
	    		break;
	    	}
	    	if((i + 1) % l1 == I) {
	    		I = i;
	    		break;
	    	}
	    }
	    if((check_angle(A[I], B[J], B[(l2 + J - 1) % l2]) >= 0) && (check_angle( B[J], A[I], A[(I + 1) % l1]) <= 0)) {
	    	break;
	    }
	}
	return pair<int,int>(I, J);
}
pair<int,int> lower_tangent_calculator(vector<pair<int,int>> A, 
									   vector<pair<int,int>> B, int x_max_in_A, int x_min_in_B){
	int l1 = A.size();
	int l2 = B.size();

	int I = x_max_in_A, J = x_min_in_B;
	while((check_angle(A[I], B[J], B[(J + 1) % l2]) >= 0 ) || (check_angle( B[J], A[I], A[(l1 + I - 1) % l1]) <= 0)) {
	    for(unsigned j = J; j < l2; j = (j + 1) % l2) {
	    	if(check_angle(A[I], B[j], B[(j + 1) % l2]) < 0) {
	    		J = j;
	    		break;
	    	}
	    	if((j + 1) % l2 == J) {
	    		J = j;
	    		break;
	    	}
	    }
	    for(unsigned i = I; i < l1; i = (l1 + i - 1) % l1) {
	    	if(check_angle(B[J], A[i], A[(l1 + i - 1) % l1]) > 0) {
	    		I = i;
	    		break;
	    	}
	    	if((l1 + i - 1) % l1 == I) {
	    		I = i;
	    		break;
	    	}
	    }
	    if((check_angle(A[I], B[J], B[(J + 1) % l2]) <= 0 ) && (check_angle( B[J], A[I], A[(l1 + I - 1) % l1]) >= 0)) {
	    	break;
	    }
	}
	return pair<int,int>(I, J);
}

vector<pair<int,int>> convex_hull_finder(vector<pair<int,int>> all_points){
	int l = all_points.size();
	// Base case.
	if(l <= 3){
		// if(l==2) {
		// 	if(check_angle(make_pair(0,0), all_points[0], all_points[1]) > 0) {
		// 		pair<int,int> temp = all_points[1];
		// 		all_points[1] = all_points[2];
		// 		all_points[2] = temp;
		// 	}
		// }
		if(l == 3){
			if(check_angle(all_points[0], all_points[1], all_points[2]) > 0) {
				pair<int,int> temp = all_points[1];
				all_points[1] = all_points[2];
				all_points[2] = temp;
			}
		}
		return all_points;
	}

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
	int x_max_in_A, x_min_in_B;
	int i, j;
	int l1 = A.size();
	int l2 = B.size();

	for ( i = 0; i < l1; ++i)
	{
		if (A[i].first > maxm)
		{
			x_max_in_A = i;
			maxm = A[i].first;
		}
	}
	for ( i = 0; i < l2; ++i)
	{
		if (B[i].first < minm)
		{
			x_min_in_B = i;
			minm = B[i].first;
		}
	}
	pair<int,int> upper_t = upper_tangent_calculator(A, B, x_max_in_A, x_min_in_B);
	pair<int,int> lower_t = lower_tangent_calculator(A, B, x_max_in_A, x_min_in_B);

	vector<pair<int,int>> temp;
	for(unsigned i = lower_t.second; ; i = (i+1)%l2) {
		temp.push_back(B[i]);
		if(i == upper_t.second) {
			break;
		}
	}
	if(lower_t.first < upper_t.first) {
		A.erase (A.begin() + lower_t.first + 1, A.begin() + upper_t.first);
	}
	else{
		temp.insert(temp.end(), A.begin() + upper_t.first, A.begin() + lower_t.first + 1);
		return temp;
	}
	
	A.insert(A.begin() + lower_t.first + 1, 
			 temp.begin(), temp.end());
	return A;

}

int main()
{
		
	vector<pair<int,int>> v;
	// v.push_back(pair<int,int>(1,2));
	// v.push_back(pair<int,int>(2,3));
	// v.push_back(pair<int,int>(2,4));
	// v.push_back(pair<int,int>(2,5));
	// v.push_back(pair<int,int>(3,3));
	// v.push_back(pair<int,int>(4,3));
	// v.push_back(pair<int,int>(3,2));
	// v.push_back(pair<int,int>(5,2));
	// v.push_back(pair<int,int>(1,1));
	// v.push_back(pair<int,int>(4,4));
	// v.push_back(pair<int,int>(7,2));


	int n, x, y;
	cout<<"Enter n?\n";
	cin>>n;
	cout<<"Coordinates?\n";
	for(unsigned i = 0; i < n; ++i) {
		cin>>x>>y;
		v.push_back(pair<int,int>(x,y));
	}
	
	cout<<"\n";
	sort(v.begin(), v.end(), compare_func);
	v = convex_hull_finder(v);
	for(unsigned i = 0; i < v.size(); ++i) {
		cout<<v[i].first<<" "<<v[i].second<<"\n";
	}
	
	return 0;
}