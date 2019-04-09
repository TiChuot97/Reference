// Tested with: http://www.spoj.com/problems/TORNJEVI/
// avail[] initialized to be all 0
void tarjan(int u) {
    num[u] = low[u] = ++num_node;
    st.push(u);
    for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (!avail[v]) {
            if (num[v] == 0) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            }
            else low[u] = min(low[u], num[v]);
        }
    }
    if (low[u] == num[u]) {
        int v = -1;
        ++num_comp;
        while (v != u) {
            v = st.top(); st.pop();
            comp[v] = num_comp;
            avail[v] = 1;
        }
    }
}
