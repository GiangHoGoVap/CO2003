void Util(int v, bool visited[], stack<int> &s)
{
    visited[v] = true;
    for (int i = 0; i < adj[v].getSize(); i++)
    {
        if (!visited[adj[v].getElement(i)])
            Util(adj[v].getElement(i), visited, s);
    }
    s.push(v);
}

void topologicalSort()
{
    //TODO
    stack<int> s;
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
            Util(i, visited, s);
    }
    while (!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
}