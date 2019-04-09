// Tested with: https://codeforces.com/gym/100513/problem/L
// For multitest, initialize label[], l[], r[] to 0 and
// clear adj[], radj[], bucket[], child[].

struct DominatorTree {
    DominatorTree() = default;

    bool reachable(int u) { return label[u] > 0; }

    void add_edge(int u, int v) { adj[u].push_back(v); }

    void dfs(int u) {
        label[u] = ++num; orig[num] = u;
        dsu[num] = mdsu[num] = sdom[num] = num;
        for (int v : adj[u]) {
            if (!label[v]) {
                dfs(v);
                parent[label[v]] = label[u];
            }
            radj[label[v]].push_back(label[u]);
        }
    }
     
    int find_dsu(int u, int flag = 0) {
        if (u == dsu[u]) return flag ? -1 : u;
        int p = find_dsu(dsu[u], 1);
        if (p < 0) return u;
        if (sdom[mdsu[dsu[u]]] < sdom[mdsu[u]])
            mdsu[u] = mdsu[dsu[u]];
        dsu[u] = p;
        return flag ? p : mdsu[u];
    }

    void dfs_dominator(int u) {
        l[u] = ++num;
        for (int v : child[u]) dfs_dominator(v);
        r[u] = num;
    }

    bool dominates(int u, int v) {
        return l[u] <= l[v] && l[v] <= r[u];
    }
    
    void build() {
        num = 0; dfs(root);
        for (int u = num; u >= 1; --u) {
            for (int v : radj[u])
                sdom[u] = min(sdom[u], sdom[find_dsu(v)]);
            if (u != 1) bucket[sdom[u]].push_back(u);
            for (int v : bucket[u]) {
                int w = find_dsu(v);
                if (sdom[w] == sdom[v]) idom[v] = sdom[v];
                else idom[v] = w;
            }
            if (u != 1) dsu[u] = parent[u];
        }
        for (int i = 2; i <= num; ++i) {
            if (idom[i] != sdom[i]) idom[i] = idom[idom[i]];
            child[orig[idom[i]]].push_back(orig[i]);
        }
        num = 0; dfs_dominator(root);
    }
    
    vector < int > adj[maxN], radj[maxN], bucket[maxN], child[maxN];
    int sdom[maxN], idom[maxN], dsu[maxN], mdsu[maxN], n, root, num;
    int parent[maxN], label[maxN], orig[maxN], l[maxN], r[maxN];
};
