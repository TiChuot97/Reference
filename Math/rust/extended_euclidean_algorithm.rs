// Find a * x + b * y = gcd(a, b) = d
//      q = a / b; r = a % b
//      b * x1 + r * y1 = d
// =>   b * x1 + (a - q * b) * y1 = d
// =>   b * x1 + a * y1 - q * b * y1 = d
// =>   a * y1 + (x1 - q * y1) * b = d
// =>   x = y1, y = x1 - q * y1
fn extended_gcd(a: i64, b: i64) -> (i64, i64) {
    if b == 0 {
        (1, 0)
    } else {
        let (x, y) = extended_gcd(b, a % b);
        (y, x - (a / b) * y)
    }
}

fn inverse_modulo(a: i64, m: i64) -> i64 {
    let (x, _y) = extended_gcd(a, m);
    (x + m) % m
}
