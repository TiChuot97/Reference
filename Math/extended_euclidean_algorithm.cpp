// Find a * x + b * y = gcd(a, b) = d
//      q = a / b; r = a % b
//      b * x1 + r * y1 = d
// =>   b * x1 + (a - q * b) * y1 = d
// =>   b * x1 + a * y1 - q * b * y1 = d
// =>   a * y1 + (x1 - q * y1) * b = d
// =>   x = y1, y = x1 - q * y1
typedef LL long long;
pair < LL, LL > extended_gcd(LL a, LL b) {
    if (b == 0) return make_pair(1, 0);
    pair < LL, LL > xy = extended_gcd(b, a % b);
    return make_pair(xy.second, xy.first - (a / b) * xy.second);
}

LL inverse_modulo(LL a, LL m) {
    pair < LL, LL > xy = extended_gcd(a, m);
    return (xy.first + m) % m;
}
