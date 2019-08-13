// Tested with https://dmoj.ca/problem/apio10p1
// Finding max.

typedef long long htype;
typedef pair < htype, htype > line;
vector < line > lst;

bool is_bad(line l1, line l2, line l3) {
    return (1.0 * (l1.second - l2.second)) / (l2.first - l1.first) >= (1.0 * (l2.second - l3.second)) / (l3.first - l2.first);
}

// Assuming lines' slopes m are strictly increasing.
void add(htype m, htype b) {
    while (lst.size() >= 2 && is_bad(lst[lst.size() - 2], lst.back(), {m, b}))
        lst.pop_back();
    lst.push_back({m, b});
}

htype get_value(line d, htype x) {
    return d.first * x + d.second;
}

// Assuming queries' x are strictly increasing.
int pointer = 0;
htype get(htype x) {
    if (pointer > lst.size()) pointer = lst.size() - 1;
    while (pointer < lst.size() - 1 && get_value(lst[pointer], x) < get_value(lst[pointer + 1], x))
        ++pointer;
    return get_value(lst[pointer], x);
}

