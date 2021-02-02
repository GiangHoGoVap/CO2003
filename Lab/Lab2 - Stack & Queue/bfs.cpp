#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs(vector<vector<int>> graph, int start) {
	int V = graph.size();
	bool* visited = new bool[V];
	for (int i=0; i<V; i++){
		visited[i] = 0;
	}
	queue<int> q;
	visited[start] = 1;
	q.push(start);
	vector<int>::iterator itr;
	while (!q.empty()){
		start = q.front();
		cout << start << " ";
		q.pop();
		for (itr = graph[start].begin(); itr != graph[start].end(); itr++){
			if (visited[*itr] == 0){
				visited[*itr] = 1;
				q.push(*itr);
			}
		}
	}
}

int main(){
	int init_graph[10][10] = {  {0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
				    		 {0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
				    		 {0, 1, 0, 0, 0, 1, 1, 0, 1, 1},
				    		 {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
				    		 {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
				    		 {1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
				    		 {0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
				    		 {1, 0, 0, 0, 0, 1, 1, 0, 1, 0},
				    		 {0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
				    		 {1, 0, 1, 0, 1, 0, 0, 0, 1, 0} };
	int n = 10;
	vector<vector<int>> graph(n, vector<int>());
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (init_graph[i][j]) graph[i].push_back(j);
		}
	}

	bfs(graph, 0);
}
