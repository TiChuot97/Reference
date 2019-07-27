// Tested with: https://codeforces.com/contest/1096/problem/G

struct NTT {
    typedef vector < int64_t > ivector;
    typedef int64_t ctype;
    typedef vector < ctype > cvector;

    static ctype add(ctype x, ctype y) { 
        return 1ll * x + y < mod ? x + y : x + y - mod;
    }
    static ctype subtract(ctype x, ctype y) { 
        return x < y ? 1ll * x - y + mod : x - y;
    }
    static ctype multiply(ctype x, ctype y) {
        return (1ll * x * y) % mod;
    }
    static ctype generate_root(int len, bool invert) {
        ctype wlen = invert ? inv_root : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (1ll * wlen * wlen) % mod;
        return wlen;
    }
    static void prepare_output(
        const cvector& vin, ivector& vout, uint32_t out_size) {
        vout = vin;
        while (vout.size() > 1 && vout.back() == 0) vout.pop_back();
    }
    static void invert(cvector& a) {
        int32_t inv_n = inverse(a.size(), mod);
        for (auto& x : a) x = (1ll * x * inv_n) % mod;
    }
    static int32_t root, inv_root, root_pw, mod;
};
// Let mod = c * 2^NBIT + 1. Then, NTT::root is
// (g^c) % mod, where g is primitive root of mod.
int32_t NTT::root = /* ... */
int32_t NTT::inv_root = inverse(NTT::root, modP);
int32_t NTT::root_pw = PolyMul::N;
int32_t NTT::mod = modP;
