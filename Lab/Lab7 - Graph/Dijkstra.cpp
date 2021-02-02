#include <iostream>
using namespace std;

// Some helping functions
int minDistance(int dist[], bool sptSet[])
{
    int min = INT32_MAX;
    int min_index;
    for (int k = 0; k < 6; k++)
    {
        if (sptSet[k] == false && dist[k] <= min)
        {
            min = dist[k];
            min_index = k;
        }
    }
    return min_index;
}

int Dijkstra(int **graph, int src, int dst)
{
    // TODO: return the length of shortest path from src to dst.
    int dist[6];
    bool sptSet[6];
    for (int i = 0; i < 6; i++)
    {
        dist[i] = INT32_MAX;
        sptSet[i] = false;
    }
    dist[src] = 0;
    for (int count = 0; count < 5; count++)
    {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int j = 0; j < 6; j++)
        {
            if (!sptSet[j] && graph[u][j] && dist[u] != INT32_MAX && dist[u] + graph[u][j] < dist[j])
            {
                dist[j] = dist[u] + graph[u][j];
            }
        }
    }
    for (int i = 0; i < 6; i++)
    {
        if (dst == i)
            dst = dist[i];
    }
    return dst;
}

int main()
{
    int n = 6;
    int init[6][6] = {
        {0, 10, 20, 0, 0, 0},
        {10, 0, 0, 50, 10, 0},
        {20, 0, 0, 20, 33, 0},
        {0, 50, 20, 0, 20, 2},
        {0, 10, 33, 20, 0, 1},
        {0, 0, 0, 2, 1, 0}};

    int **graph = new int *[n];
    for (int i = 0; i < n; ++i)
    {
        graph[i] = init[i];
    }

    cout << Dijkstra(graph, 0, 1);
}