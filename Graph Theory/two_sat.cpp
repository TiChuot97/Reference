// Tested with: http://www.spoj.com/problems/TORNJEVI/
// Note: for tarjan() see tarjan.cpp

bool two_sat() {
    for (int i = 0; i < list_node.size(); ++i)
        if (!num[list_node[i]]) tarjan(list_node[i]);
    for (int i = 0; i < list_node.size(); ++i) {
        int u = list_node[i];
        if (comp[u] == comp[neg[u]]) return false;
        if (comp[u] < comp[neg[u]])
            check[u] = 1; // Pick u (otherwise pick !u)
    }
    return true;
}
