#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> topologicalSorting(vector<vector<int>> graph){
	int V = graph.size();
	vector<int> in_degree(V, 0);
	for (int u = 0; u < V; u++){
		vector<int>::iterator itr;
		for (itr = graph[u].begin(); itr != graph[u].end(); itr++){
			in_degree[*itr]++;
		}
	}
	queue<int> q;
	for (int i=0; i<V; i++){
		if (in_degree[i] == 0) q.push(i);
	}
	int counter = 0;
	vector<int> top_order;
	while (!q.empty()){
		int u = q.front();
		q.pop();
		top_order.push_back(u);
		vector<int>::iterator itr;
		for (itr = graph[u].begin(); itr != graph[u].end(); itr++){
			if (--in_degree[*itr] == 0) q.push(*itr);
		}
		counter++;
	}
	if (counter != V) return vector<int>();
	else return top_order;
}

int main(){
	int n = 6;
    int G[6][6] = { {0, 1, 0, 1, 0, 0},
                    {0, 0, 1, 1, 0, 0},
                    {0, 0, 0, 1, 1, 1},
                    {0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 1},
                    {0, 0, 0, 0, 0, 0} };
    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (G[i][j] == 1) graph[i].push_back(j);
        }
    }

    vector<int> res = topologicalSorting(graph);
    if (res.empty()) printf("-1");
    else {
        for (int e : res) printf("%d ", e);
    }
}
