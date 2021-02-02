#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool chk(vector<vector<int>> adj , vector<int> &vis ,int child,int c,vector<int> &col )
{
    vis[child] = 1;
    col[child] = c;
    for(auto x : adj[child])
    {
        if(vis[x]==0)
        {
            if(chk(adj,vis,x,!c,col)==0)
                return false;
        }
        else
            if(col[child]==col[x])
                return false;
    }
    return true;
}
bool isBipartite(vector<vector<int>> graph) {
    vector<vector<int>> adj(graph.size()+1);
    vector<int> vis(graph.size()+1, 0);
    vector<int> col(graph.size()+1, 0);
        
    for(unsigned i=0;i<graph.size();i++)
    {   
        for(unsigned k=0;k<graph[i].size();k++)
             adj[i].push_back(graph[i][k]);  
    } 
        
    for(unsigned j=0;j<graph.size();j++)
    {   
        if(vis[j]==0)
        { 
            if(!chk(adj,vis,j,1,col))
            return false;
        }
    }
    return true;
}

int main(){
	int G[6][6] = { {0, 1, 0, 0, 0, 1},
                	{1, 0, 1, 0, 0, 0},
                	{0, 1, 0, 1, 0, 0},
                	{0, 0, 1, 0, 1, 0},
                	{0, 0, 0, 1, 0, 1},
                	{1, 0, 0, 0, 1, 0} };
	int n = 6;

	vector<vector<int>> graph(n, vector<int>());
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (G[i][j]) graph[i].push_back(j);
		}
	}

	isBipartite(graph) ? cout << "Yes" : cout << "No";
}
