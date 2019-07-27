// Tested with https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=6289

bool find_path() {
    int l = 1, r = 1; ++flag;
    q[1] = source; check[source] = flag;
    while (l <= r) {
        int u = q[l++];
        for (auto v : adj[u])
            if (check[v] != flag && c[u][v] > f[u][v]) {
                pre[v] = u;
                check[v] = flag;
                if (v == target) return true;
                q[++r] = v;
            }
    }
    return false;
}

void augment() {
    int v = target, delta = oo;
    while (v != source) {
        int u = pre[v];
        delta = min(c[u][v] - f[u][v], delta);
        v = u;
    }
    v = target; flow += delta;
    while (v != source) {
        int u = pre[v];
        f[u][v] += delta;
        f[v][u] -= delta;
        v = u;
    }
}
