// Tested with: https://www.spoj.com/problems/EZDIJKST/

struct CmpHeap {
    bool operator () (pi x, pi y) {
        return y.second < x.second;
    }
};

priority_queue < pi, vector < pi >, CmpHeap > heap;

void dijkstra(int s) {
    for (int i = 1; i <= n; ++i) check[i] = 0, d[i] = oo;
    d[s] = 0; heap.push({s, 0});
    while (!heap.empty()) {
        auto p = heap.top(); heap.pop();
        while (check[p.first] && !heap.empty())
            p = heap.top(), heap.pop();
        if (check[p.first]) return;
        int u = p.first; check[u] = 1;
        for (auto ou : adj[u]) {
            int v = ou.first;
            int w = ou.second;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                heap.push({v, d[v]});
            }
        }
    }
}
