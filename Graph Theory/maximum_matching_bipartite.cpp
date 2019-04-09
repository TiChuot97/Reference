// Tested with https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=6293

bool find_match(int u) {
    if (check[u] == flag) return 0;
    check[u] = flag;
    for (int v : rhs)
        if (c[u][v] && (!rmatch[v] || find_match(rmatch[v]))) {
            rmatch[v] = u;
            lmatch[u] = v;
            return true;
        }
    return false;
}

int max_matching() {
    int ret = 0;
    for (int u : rhs) rmatch[u] = 0;
    for (int u : lhs) {
        ++flag; lmatch[u] = 0;
        if (find_match(u)) ++ret;
    }
    return ret;
}
