// Tested with: http://www.spoj.com/problems/QTREE2/
// Note: Log = ceil(log2(n))
// d[u] = depth of node u + 1 (ie: d[root] = 1)

void buildLCA() {
    for (int i = 1; i <= n; ++i) p[i][0] = par[i];
    for (int j = 1; j <= Log; ++j)
        for (int i = 1; i <= n; ++i)
            p[i][j] = p[p[i][j - 1]][j - 1];
}

int LCA(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    for (int j = Log; j >= 0; --j)
        if (d[p[u][j]] >= d[v]) u = p[u][j];
    if (u == v) return u;
    for (int j = Log; j >= 0; --j)
        if (p[u][j] != p[v][j]) {
            u = p[u][j];
            v = p[v][j];
        }
    return p[u][0];
}
