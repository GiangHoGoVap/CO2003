#include <iostream>
#include <list>
using namespace std;

class Adjacency
{
private:
    int *arr;
    int *weight;
    int size;

public:
    Adjacency() {}
    Adjacency(int v)
    {
        arr = new int[v];
        weight = new int[v];
        size = 0;
    }
    void init(int v)
    {
        arr = new int[v];
        weight = new int[v];
        size = 0;
    }
    void push(int v)
    {
        arr[size] = v;
        weight[size] = 1;
        size++;
    }
    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << "->" << arr[i];
        }
        cout << endl;
    }
    void printArray()
    {
        for (int i = 0; i < size - 1; i++)
        {
            cout << arr[i] << " ";
        }
        cout << arr[size - 1] << endl;
    }
    int getSize()
    {
        return size;
    }
    int getElement(int idx)
    {
        return arr[idx];
    }
    int getWeight(int idx)
    {
        return weight[idx];
    }
};

class Graph
{
private:
    int V;
    Adjacency *adj;

public:
    Graph(int V)
    {
        this->V = V;
        adj = new Adjacency[V];
        for (int i = 0; i < V; i++)
        {
            adj[i].init(V);
        }
    }
    void addEdge(int v, int w)
    {
        adj[v].push(w);
        adj[w].push(v);
    }
    void printGraph()
    {
        for (int v = 0; v < V; v++)
        {
            cout << "\nAdjacency list of vertex " << v << "\nhead ";
            adj[v].print();
        }
    }
    Adjacency *BFS(int v)
    {
        //v is a vertex we start BFS
        Adjacency *arr = new Adjacency(V);
        list<int> queue;
        bool *visited = new bool[V];
        queue.push_back(v);
        while (!queue.empty())
        {
            v = queue.front();
            queue.pop_front();
            if (!visited[v])
            {
                arr->push(v);
                visited[v] = true;
                for (int i = 0; i < adj[v].getSize(); i++)
                {
                    if (!visited[adj[v].getElement(i)])
                        queue.push_back(adj[v].getElement(i));
                }
            }
        }
        return arr;
    }
    void DFSUtil(int v, bool visited[], Adjacency *arr)
    {
        visited[v] = true;
        arr->push(v);
        for (int i = 0; i < adj[v].getSize(); i++)
        {
            if (!visited[adj[v].getElement(i)])
                DFSUtil(adj[v].getElement(i), visited, arr);
        }
    }
    Adjacency *DFS(int v)
    {
        Adjacency *arr = new Adjacency(V);
        bool *visited = new bool[V];
        DFSUtil(v, visited, arr);
        delete[] visited;
        visited = NULL;
        return arr;
    }
};

int main()
{
    int V = 6;
    int visited = 2;
    Graph g(V);
    Adjacency *arr = new Adjacency(V);
    int edge[][2] = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 4}, {3, 4}, {3, 5}, {4, 5}};
    for (int i = 0; i < 8; i++)
    {
        g.addEdge(edge[i][0], edge[i][1]);
    }
    arr = g.BFS(visited);
    g.printGraph();
    cout << endl;
    arr->print();
    cout << endl;
    arr->printArray();
    arr = g.DFS(visited);
    g.printGraph();
    delete arr;
}