// Tested with https://www.spoj.com/problems/MUL/
struct FFT {
    typedef vector < int64_t > ivector;
    typedef complex < double > ctype;
    typedef vector < ctype > cvector;
    static ctype add(ctype x, ctype y) { return x + y; }
    static ctype subtract(ctype x, ctype y) { return x - y; }
    static ctype multiply(ctype x, ctype y) { return x * y; }
    static ctype generate_root(int len, bool invert) {
        double alpha = 2.0 * PI / len * (invert ? -1 : 1);
        return ctype(cos(alpha), sin(alpha));
    }
    static void prepare_output(
        const cvector& vin, ivector& vout, uint32_t out_size) {
        vout.resize(out_size);
        for (int i = 0; i < out_size; ++i)
            vout[i] = llround(vin[i].real());
        while (vout.size() > 1 && vout.back() == 0)
            vout.pop_back();
    }
    static void invert(cvector& a) {
        for (auto& x : a) x /= a.size();
    }
    static double PI;
};
double FFT::PI = acos(-1.0);

