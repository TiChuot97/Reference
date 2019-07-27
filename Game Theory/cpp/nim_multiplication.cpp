// Tested with: http://www.spoj.com/problems/WINSTRAT
// Note: (i | j) might overflow

int nim_multiply(int x, int y) {
    int p = 0;
    for (int i = 0; i < maxLog + 1; ++i)
        if (x & (1 << i))
            for (int j = 0; j < maxLog + 1; ++j)
                if (y & (1 << j))
                    p ^= mul[i][j];
    return p;
}

void init() {
    for (int i = 0; i < maxLog + 1; ++i)
        for (int j = 0; j <= i; ++j) {
            if ((i & j) == 0) mul[i][j] = 1 << (i | j);
            else {
                mul[i][j] = 1;
                for (int t = 0; t < maxLog + 1; ++t) {
                    int k = (1 << t);
                    if (i & j & k) mul[i][j] = nim_multiply(mul[i][j], ((1 << k) * 3) >> 1);
                    else
                        if ((i | j) & k) mul[i][j] = nim_multiply(mul[i][j], (1 << k));
                }
            }
            mul[j][i] = mul[i][j];
        }
}
