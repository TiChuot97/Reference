// Tested with: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3073
// Supported reversing a segment.

struct SplayTree {
    struct Node {
        Node *left, *right, *parent;
        int value, size;
        bool reversed;
    };

    SplayTree() {
        nilt = new Node();
        nilt->left = nilt->right = nilt->parent = nilt;
        nilt->value = nilt->size = 0;
        nilt->reversed = false;
    }

    void set_left(Node* x, Node* y) {
        x->left = y;
        y->parent = x;
    }

    void set_right(Node* x, Node* y) {
        x->right = y;
        y->parent = x;
    }

    void set_child(Node* x, Node* y, bool is_right) {
        if (is_right) set_right(x, y);
        else set_left(x, y);
    }

    void build_tree(vector < int >& arr) {
        root = nilt;
        for (int i = 0; i < arr.size(); ++i) {
            Node* x = new Node();
            x->size = arr[i];
            x->value = arr[i];
            x->reversed = false;
            set_left(x, root);
            x->parent = x->right = nilt;
            root = x;
        }
    }

    void propagate(Node* x) {
        if (x == nilt) return;
        if (x->reversed) {
            swap(x->left, x->right);
            x->left->reversed = !x->left->reversed;
            x->right->reversed = !x->right->reversed;
            x->reversed = false;
        }
    }

    Node* locate(Node* x, int pos) {
        do {
            propagate(x);
            int num = x->left->size + 1;
            if (num == pos) return x;
            if (num > pos) x = x->left;
            else
                pos -= num, x = x->right;
        } while (true);
        return x;
    }

    void update(Node* x) {
        x->size = x->left->size + x->right->size + 1;
    }

    void uptree(Node* x) {
        Node* y = x->parent;
        Node* z = y->parent;
        if (x == y->right) {
            Node* b = x->left;
            set_right(y, b);
            set_left(x, y);
        }
        else {
            Node* b = x->right;
            set_left(y, b);
            set_right(x, y);
        }
        update(y);
        update(x);
        set_child(z, x, z->right == y);
    }

    void splay(Node* x) {
        do {
            Node* y = x->parent;
            if (y == nilt) return;
            Node* z = y->parent;
            if (z != nilt) {
                if ((x == y->left) == (y == z->left))
                    uptree(y);
                else
                    uptree(x);
            }
            uptree(x);
        } while (true);
    }

    void split(Node* t, int pos, Node*& t1, Node*& t2) {
        if (pos == 0) {
            t1 = nilt;
            t2 = t;
            return;
        }
        if (pos >= t->size) {
            t1 = t;
            t2 = nilt;
            return;
        }
        Node* x = locate(t, pos);
        splay(x);
        t1 = x;
        t2 = x->right;
        t1->right = nilt;
        t2->parent = nilt;
        update(t1);
    }

    Node* join(Node* t1, Node* t2) {
        if (t1 == nilt) return t2;
        t1 = locate(t1, t1->size);
        splay(t1); 
        set_right(t1, t2);
        update(t1);
        return t1;
    }

    Node *root, *nilt;
};
