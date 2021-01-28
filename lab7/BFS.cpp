Adjacency *BFS(int v)
{
    // v is a vertex we start BFS
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
