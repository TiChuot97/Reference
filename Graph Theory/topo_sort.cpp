// Tested with: http://www.spoj.com/problems/TORNJEVI/

void topo_sort() {
    for (int i = 1; i <= num_comp; ++i)
        if (deg[i] == 0) q.push(i);
    int num = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < new_adj[u].size(); ++i) {
            int v = new_adj[u][i];
            --deg[v];
            if (deg[v] == 0) q.push(v);
        }
        position[u] = ++num;
    }
}
