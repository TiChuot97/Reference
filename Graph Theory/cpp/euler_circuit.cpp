// Tested with problem D, contest 3, Bytedance Moscow Workshop
// adj[] is unordered_map
void euler(int start) {
    stack < int > st; st.push(start);
    while (!st.empty()) {
        int u = st.top();
        if (adj[u].empty()) circuit.push_back(u), st.pop();
        else {
            auto v = adj[u].begin()->first;
            --adj[u][v]; --adj[v][u];
            if (adj[u][v] == 0) {
                adj[u].erase(v);
                adj[v].erase(u);
            }
            st.push(v);
        }
    }
}
