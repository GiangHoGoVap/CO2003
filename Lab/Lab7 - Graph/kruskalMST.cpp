#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <set>
using namespace std;

struct Graph
{
    int V, E;
    vector<pair<int, pair<int, int>>> edges;
    // Constructor
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }

    void addEdge(int u, int v, int w)
    {
        edges.push_back({w, {u, v}});
    }

    //YOUR CODE HERE
    // Some helping functions
    struct DisjointSets
    {
        int *parent, *rnk;
        int n;

        DisjointSets(int n)
        {
            this->n = n;
            parent = new int[n + 1];
            rnk = new int[n + 1];

            for (int i = 0; i <= n; i++)
            {
                rnk[i] = 0;
                parent[i] = i;
            }
        }

        int find(int u)
        {
            if (u != parent[u])
                parent[u] = find(parent[u]);
            return parent[u];
        }

        void merge(int x, int y)
        {
            x = find(x);
            y = find(y);
            if (rnk[x] > rnk[y])
                parent[y] = x;
            else
                parent[x] = y;
            if (rnk[x] == rnk[y])
                rnk[y]++;
        }
    };

    int kruskalMST()
    {
        // TODO: return weight of the minimum spanning tree.
        int mst_wt = 0;
        sort(edges.begin(), edges.end());
        DisjointSets ds(V);

        vector<pair<int, pair<int, int>>>::iterator it;
        for (it = edges.begin(); it != edges.end(); it++)
        {
            int u = it->second.first;
            int v = it->second.second;

            int set_u = ds.find(u);
            int set_v = ds.find(v);

            if (set_u != set_v)
            {
                mst_wt += it->first;
                ds.merge(set_u, set_v);
            }
        }
        return mst_wt;
    }
};

int main()
{
    int V = 3, E = 3;
    Graph g(V, E);

    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 3);

    cout << g.kruskalMST();
}