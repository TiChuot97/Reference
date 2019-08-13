// Tested with: http://codeforces.com/contest/86/problem/D
// The array is 1-based

bool cmp_mo(Query i, Query j) {
    int s = (int) sqrt(n);
    return ((i.l - 1) / s < (j.l - 1) / s || ((i.l - 1) / s == (j.l - 1) / s && i.r < j.r));
}
