// Tested with: https://codeforces.com/gym/101221/attachments

void alternate(int u) {
    lmvc[u] = false;
    for (int v : rhs)
        if (c[u][v]) {
            rmvc[v] = true;
            if (rmatch[v] && lmvc[rmatch[v]])
                alternate(rmatch[v]);
        }
}

void MVC() {
    max_matching();
    for (int u : rhs) rmvc[u] = false;
    for (int u : lhs) lmvc[u] = (lmatch[u] != 0);
    for (int u : lhs)
        if (!lmvc[u]) alternate(u);
}
