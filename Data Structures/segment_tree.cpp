// Tested with: https://leetcode.com/problems/range-sum-query-mutable

void build(int k, int l, int r, const vector<int>& a) {
    if (l > r) return;
    if (l == r) {
        tree[k] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(k * 2, l, mid, a);
    build(k * 2 + 1, mid + 1, r, a);
    tree[k] = tree[k * 2] + tree[k * 2 + 1];
}

int get(int k, int l, int r, int i, int j) {
    if (r < i || j < l) return 0;
    if (i <= l && r <= j) return tree[k];
    int mid = (l + r) >> 1;
    return get(k * 2, l, mid, i, j) + get(k * 2 + 1, mid + 1, r, i, j); 
}

void update(int k, int l, int r, int i, int val) {
    if (i < l || i > r) return;
    if (l == r) {
        tree[k] = val;
        return;
    }
    int mid = (l + r) >> 1;
    update(k * 2, l, mid, i, val);
    update(k * 2 + 1, mid + 1, r, i, val);
    tree[k] = tree[k * 2] + tree[k * 2 + 1];
}
