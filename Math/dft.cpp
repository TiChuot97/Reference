// Base class for FFT and DFT
// To multiply a, b and put result in c:
// PolyMul::polynomial_multiply(a, b, c);
template < class Transform >
struct DFT {
    #define TAdd Transform::add
    #define TSub Transform::subtract
    #define TMul Transform::multiply
    typedef vector < int64_t > ivector;
    typedef typename Transform::ctype DType;
    typedef vector < DType > dvector;
    typedef vector < vector < dvector > > mdvector;
    static void init() {
        w.resize(NBIT);
        for (int iter = 0, len = 1; iter < NBIT; ++iter, len *= 2) {
            w[iter].resize(2);
            for (int invert = 0; invert < 2; ++invert) {
                w[iter][invert].assign(1 << iter, 0);
                DType wlen = Transform::generate_root(2 * len, invert);
                w[iter][invert][0] = 1;
                for (int j = 1; j < len; ++j)
                    w[iter][invert][j] = TMul(w[iter][invert][j - 1], wlen);
            }
        }
    }
    static void fft(dvector& a, bool invert = false) {
        int n = a.size();
        for (int i = 1, j = 0; i < n; ++i) {
            int bit = n >> 1; 
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (j > i) swap(a[i], a[j]);
        }
        for (int iter = 0, len = 1; len < n; ++iter, len *= 2) {
            DType wlen = Transform::generate_root(2 * len, invert);
            for (int i = 0; i < n; i += 2 * len) {
                for (int j = 0; j < len; ++j) {
                    auto x = a[i + j];
                    auto y = TMul(w[iter][invert][j], a[i + j + len]);
                    a[i + j] = TAdd(x, y);
                    a[i + j + len] = TSub(x, y);
                }
            }
        }
        if (invert) Transform::invert(a);
    }
    static void polynomial_multiply(
        const ivector& a, const ivector& b, ivector& out) {
        uint32_t new_size = a.size() + b.size() - 1;
        for (NBIT = 0, N = 1; N < new_size; N *= 2, ++NBIT) {}
        dvector fa(a.begin(), a.end()), fb(b.begin(), b.end());
        fa.resize(N); fft(fa);
        fb.resize(N); fft(fb);
        for (int i = 0; i < fa.size(); ++i) fa[i] = TMul(fa[i], fb[i]);
        fft(fa, true);
        Transform::prepare_output(fa, out, new_size);
    }
    static int32_t NBIT, N;
    static mdvector w;
};
// Remember to call PolyMul::init() in main().
using PolyMul = DFT < FFT >;
template<> int32_t PolyMul::NBIT = /* max of log(n) */;
template<> int32_t PolyMul::N = 1 << PolyMul::NBIT;
template<> PolyMul::mdvector PolyMul::w = PolyMul::mdvector();
