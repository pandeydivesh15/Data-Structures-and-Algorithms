#include <iostream>
#include <cmath>
#include <climits>
/*
 *STL headers
 */
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>

using namespace std;
	
#define PN 				cout<<'\n'
#define PI 			    3.1415926535
#define MOD				1000000007

pair<int, vector<vector<int>> > matrix_chain(int n, vector<int> p){
	vector<vector<int>> M, POS;
	M.resize(n+1);
	POS.resize(n+1);
 	for (int i = 0; i < n + 1; ++i){
		M[i].resize(n+1);
		POS[i].resize(n+1);
 	}

 	for (int i = 0; i < n + 1; ++i){
		M[i][i] = 0;
		POS[i][i] = -1;
 	}

 	int i, j, l, k, cost_min;
 	for(l = 2; l < n+1; ++l) {
 		for(i = 1; i < n-l+2; ++i) {
 			j = i+l-1;
 			M[i][j] = INT_MAX;
 			for(k = i; k < j; ++k){
 				cost_min = M[i][k] + M[k+1][j] + p[i-1]*p[k]*p[j];
 				//cout<<cost_min<<'\n';
 				//cout<<i<<"->"<<k<<"-->"<<j<<'\n';
 				if(cost_min <= M[i][j]) {
 					M[i][j] = cost_min;
 					POS[i][j] = k;
 				}
 			}
 		}
 	}

 	return make_pair(M[1][n], POS);
}

void print_minimum_cost_chain(vector<vector<int>> POS, int i, int j){
	if (i == j){
		cout<<"A"<<i;
		return;
	}
	cout<<"(";
	print_minimum_cost_chain(POS, i, POS[i][j]);
	cout<<"*";
	print_minimum_cost_chain(POS, POS[i][j] + 1, j);
	cout<<")";

	return;
}

int main()
{
	int n, temp;
	vector<int> p;

	cout<<"Enter number of matrices--> ";
	cin>>n;
	p.resize(n+1);
	cout<<"Enter matrix orders one by one.\n";
	for(unsigned i = 0; i < n; ++i) {
		cin>>p[i];
		cin>>temp;
	}
	p[n] = temp;

	pair<int, vector<vector<int>> > ans;
	ans= matrix_chain(n, p);
	cout<<"Minimum cost ->\t"<<ans.first<<'\n';
	cout<<"Optimum Sequence of multiplication -> \t";
	print_minimum_cost_chain(ans.second, 1, n);
	return 0;
}