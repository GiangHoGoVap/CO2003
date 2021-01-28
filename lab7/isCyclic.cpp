bool Util(int v, bool visited[], bool *recStack)
{
    if (visited[v] == false)
    {
        visited[v] = true;
        recStack[v] = true;
        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); i++)
        {
            if (!visited[*i] && Util(*i, visited, recStack))
                return true;
            else if (recStack[*i])
                return true;
        }
    }
    recStack[v] = false;
    return false;
}

bool isCyclic()
{
    // Student answer
    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }
    for (int i = 0; i < V; i++)
    {
        if (Util(i, visited, recStack))
            return true;
    }
    return false;
}