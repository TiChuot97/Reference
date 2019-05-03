struct Point {
    double x, y;
};

struct Line {
    double eval(const Point& p) const {
        return a * p.x + b * p.y + c;
    }

    double a, b, c;
};

namespace distance {

double point_to_point(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double point_to_line(const Point& p, const Line& d) {
    return abs(d.eval(p)) / point_to_point({d.a, d.b}, {0, 0});
}
} // namespace distance
