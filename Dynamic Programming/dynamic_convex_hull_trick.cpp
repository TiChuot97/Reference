// Tested with https://dmoj.ca/submission/908117
// Slow but correct. Takes O(log n) per add and query.

typedef long long htype;
// Representing a line. To query value x,
// set m = x, is_query = true.
struct Line {
    bool operator < (const Line& rhs) const {
        // Compare lines
        if (!rhs.is_query) return m < rhs.m;

        // Compare queries
        const Line* s = nxt();
        if (s == NULL) return false;
        htype x = rhs.m;
        return s->m * x + s->b > m * x + b;
    }

    htype m, b;
    bool is_query;
    mutable function < const Line*() > nxt;
};

class ConvexHullTrick : public set < Line > {
  public:
    void add(htype m, htype b) {
        auto p = insert({m, b, false});
        if (!p.second) return;
        iterator y = p.first;
        y->nxt = [=] { return (next(y) == end()) ? NULL : &(*next(y)); };
        if (is_bad(y)) {
            erase(y);
            return;
        }
        while (next(y) != end() && is_bad(next(y))) erase(next(y));
        while (y != begin() && is_bad(prev(y))) erase(prev(y));
    }

    htype get(htype x) {
        iterator y = lower_bound({x, 0, true});
        return y->m * x + y->b;
    }
  private:
    bool is_bad(iterator y) {
        iterator z = next(y);
        if (y == begin())
            return ((z == end()) ? false : y->m == z->m && y->b <= z->b);
        iterator x = prev(y);
        if (z == end())
            return (y->m == x->m && y->b <= x->b);
        return (x->b - y->b) * (z->m - y->m) >= (y->b - z->b) * (y->m - x->m);
    }
};
