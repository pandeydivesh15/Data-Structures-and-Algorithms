#include <iostream>
#include <cmath>
/*
 *STL headers
 */
#include <vector>
// #include <deque>
// #include <list>
// #include <set>
#include <map>
// #include <iterator>
#include <algorithm>
// #include <numeric>
#include <string>

using namespace std;
vector<vector<int>> Memory;

int knapsack_bottom_up_DP(vector<int> v, vector<int> w, int n, int W){
	vector<vector<int>> Table;
	Table.resize(n+1);
	for(int i = 0 ; i < n + 1 ; ++i){
        Table[i].resize(W + 1);
    }

    for(unsigned i = 0; i < n+1; ++i) {
    	for(unsigned j = 0; j < W+1; ++j) {
    		// number of elements = i and Max Weight = j

    		if(j == 0 || i == 0) {
    			Table[i][j] = 0;
    		}
    		else if (w[i-1] > j)
    			Table[i][j] = Table[i-1][j];
    		else{
    			Table[i][j] = max(Table[i-1][j], Table[i-1][j-w[i-1]] + v[i-1]);
    		}	

    	}
    }
    return Table[n][W];

}

int knapsack_top_down_DP(vector<int> v, vector<int> w, int n, int W){
	if (Memory[n][W] != -1)
		return Memory[n][W];

	if( n == 0 || W == 0 ){
		Memory[n][W] = 0;
		return 0;
	}

	if (w[n-1] > W){
		Memory[n][W] = knapsack_top_down_DP(v, w, n-1, W);
	}
	else{
		Memory[n][W] = max(knapsack_top_down_DP(v, w, n-1, W), 
						   knapsack_top_down_DP(v, w, n-1, W - w[n-1]) + v[n-1]);
	}
	return Memory[n][W];   		
}

int main()
{


	int n; 
	cin>>n;
	vector<int> values;
	vector<int> weights;
	cout<<"\nStart entering values and weights one by one\n";
	int input_count=0;
	int temp_input;
	while(input_count<n){
			cin>>temp_input;
			values.push_back(temp_input);
			cin>>temp_input;
			weights.push_back(temp_input);
			input_count++;
	}
	int Max_weight;
	cin>>Max_weight;

	cout<<"\nMax Value is --(Bottom Up DP)--> "
		<<knapsack_bottom_up_DP(values, weights, n, Max_weight)<<"\n";
	
	// Initialising Memory element for Top down DP approach
	Memory.resize(n+1);
	for(unsigned i = 0; i < n+1; ++i) {
    	for(unsigned j = 0; j < Max_weight+1; ++j) {
    		Memory[i].push_back(-1);
    	}
    }
	cout<<"\nMax Value is --(Top Down DP)--> "
		<<knapsack_top_down_DP(values, weights, n, Max_weight)<<"\n";
	

	
	
	return 0;
}