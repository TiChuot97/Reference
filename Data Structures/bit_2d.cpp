// Tested with: http://www.spoj.com/problems/MATSUM/
// Support 2 types of queries:
// - Add v to cell (x, y)
// - Get the sum of rectangle with top-left corner (1, 1) 
// and lower-right corner (x, y)

void update(int x, int y, int v) {
    while (x <= n) {
        int z = y;
        while (z <= n) {
            bit[x][z] += v;
            z += (z & (-z));
        }
        x += (x & (-x));
    }
}

int get(int x, int y) {
    if (x == 0 || y == 0) return 0;
    int sum = 0;
    while (x) {
        int z = y;
        while (z) {
            sum += bit[x][z];
            z -= (z & (-z));
        }
        x -= (x & (-x));
    }
    return sum;
}
