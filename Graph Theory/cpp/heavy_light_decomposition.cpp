//Tested with: http://www.spoj.com/problems/QTREE3/

void build(int u) {
    size_tree[u] = 1;
    for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (parent[u] == v) continue;
        parent[v] = u;
        build(v);
        size_tree[u] += size_tree[v];
    }
}

void hld(int u) {
    if (chain_head[num_chain] == 0)
        chain_head[num_chain] = u;
    chain_idx[u] = num_chain;
    arr_idx[u] = ++num_arr;
    node_arr[num_arr] = u;
    
    int heavy_child = -1;
    for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (parent[u] == v) continue;
        if (heavy_child == -1 || size_tree[v] > size_tree[heavy_child])
            heavy_child = v;
    }

    if (heavy_child != -1)
        hld(heavy_child);

    for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (v == heavy_child || parent[u] == v) continue;
        ++num_chain;
        hld(v);
    }
}

// u is an ancestor of v
int query_hld(int u, int v) {
    int uchain = chain_idx[u], vchain = chain_idx[v], ans = -1;
    while (true) {
        if (uchain == vchain) {
            get(..., arr_idx[u], arr_idx[v]);
            break;
        }
        get(..., arr_idx[chain_head[vchain]], arr_idx[v]);
        v = parent[chain_head[vchain]];
        vchain = chain_idx[v];
    }
    return ans;
}
