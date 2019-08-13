// Tested with: https://codeforces.com/contest/1120/problem/C
// z[] is 1-based, z[1] = 0
void z_function(string s){
    int l = 0, r = 0, n = s.length();
    for (int i = 2; i <= n; ++i) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l + 1]);
        else z[i] = 0;
        while (i + z[i] <= n && s[i + z[i] - 1] == s[z[i]])
            ++z[i];
        if (r < i + z[i] - 1) {
            l = i;
            r = i + z[i] - 1;
        }
    }
}
