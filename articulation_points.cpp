#include <iostream>
#include <cmath>
/*
 *STL headers
 */
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <string>

using namespace std;
	
#define LLI				long long int
#define PN 				cout<<'\n'

#define PI 			    3.1415926535
#define MOD				1000000007

class Graph
{
public:
	vector<int> vertices; 
	vector< list<int> > Adjlist;
	Graph(int n){
		for(unsigned i = 0; i < n; ++i) {
			vertices.push_back(i);
		}
		Adjlist.resize(n);
	}

	void add_edge(int i, int j){
		Adjlist[i].push_back(j);
		Adjlist[j].push_back(i);
	}
};

void ARTI_points_by_DFS(Graph graph, int u, vector<bool>& visited, vector<int>& disc_time, 
							 vector<bool>& articulation_points, vector<int>& back_edge_time, 
							 vector<int>& parent, int _time){
	disc_time[u] = back_edge_time[u] = _time + 1;
	++_time;
	visited[u] = true;

	int children_count = 0, v;

	for (list<int>::iterator i = graph.Adjlist[u].begin(); i != graph.Adjlist[u].end(); ++i){
		v = *i;

		if(!visited[v]){
			parent[v] = u;
			children_count++;
			ARTI_points_by_DFS(graph, v, visited, disc_time,
							   articulation_points, back_edge_time, parent,
							   _time);

			back_edge_time[u] = min(back_edge_time[u], back_edge_time[v]);
			// Finding best/minimum back edge of all subtrees

			if(children_count > 1 && parent[u] == -1) {
				articulation_points[u] = true;
				continue;
			}
			if(parent[u] != -1 && back_edge_time[v] >= disc_time[u]) {
				// If there would have been a back edge, 
				// then back_edge[v] would store lesser discovery time
				articulation_points[u] = true;
			}
			// else{
			// 	articulation_points[u] = false;
			// }
			// This else condition should not come as for not being an articulation point,
			// all subtrees must have back edges
		}
		else if(parent[u] != v){
			back_edge_time[u] = min(back_edge_time[u], disc_time[v]);
			// We are using min because we want to store the minimum discovery time 
			// of all vertices in the current subtree
			// earliest back edge in the subtree
			// In our case, back_edge_time[u] = disc_time[v]; will also work.
			// But this will not give best back edge.
		}
	}

}

int main()
{
	int n, count, temp1, temp2;
	cout<<"Enter number of vertices in the Graph?\n";
	cin>>n;

	Graph graph = Graph(n);

	cout<<"Enter Edges Count\n";
	cin>>count;
	for(unsigned i = 0; i < count; ++i) {
		cin>>temp1>>temp2;
		graph.add_edge(temp1, temp2);
	}


	vector<bool> visited(n, false);
	vector<int> disc_time(n, 0);
	vector<int> back_edge_time(n, 0);
	vector<bool> articulation_points(n, false);
	vector<int> parent(n, -1); 

	ARTI_points_by_DFS(graph, 1, visited, disc_time, 
					   articulation_points, back_edge_time, parent,
					   0);
	// copy(articulation_points.begin(), articulation_points.end(),
	// 		ostream_iterator<bool>(cout," "));
	cout<<"\nArticulation points:\n";
	for (int i = 0; i < n; ++i){
		if(articulation_points[i] == true){
			cout<<"Vertex: "<<i<<'\n';
		}
	}
	return 0;
}