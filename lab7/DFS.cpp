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
    // v is a vertex we start DFS
    Adjacency *arr = new Adjacency(V);
    bool *visited = new bool[V];
    DFSUtil(v, visited, arr);
    delete[] visited;
    visited = NULL;
    return arr;
}