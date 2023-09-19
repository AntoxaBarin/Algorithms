#include <iostream>
#include <vector>

// Сумма на отрезке {
void build_tree(std::vector<int> &array, std::vector<int> &tree, int v, int l, int r) {
    if (l == r) {
        tree[v] = array[l];
    }
    else {
        int m = (l + r) / 2;
        build_tree(array, tree, v * 2, l, m);
        build_tree(array, tree, v * 2 + 1, m + 1, r);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
}

int segment_sum(std::vector<int> &tree, int v, int l, int r, int req_l, int req_r) {
    if (req_l > req_r)
        return 0;
    if (req_l == l && req_r == r)
        return tree[v];
    int m = (l + r) / 2;
    return segment_sum(tree,v * 2,  l, m, req_l, std::min(req_r, m))
           + segment_sum (tree, v * 2 + 1, m + 1, r, std::max(req_l, m + 1), req_r);
}
// }

// Поиск максимума на отрезке {
struct Node {
    int value;
    int index;
};

void build_tree(std::vector<int> &array, std::vector<Node> &tree, int v, int l, int r) {
    if (l == r) {
        tree[v].value = array[l];
        tree[v].index = l;
    }
    else {
        int m = (l + r) / 2;
        build_tree(array, tree, v * 2, l, m);
        build_tree(array, tree, v * 2 + 1, m + 1, r);

        if (tree[v * 2].value > tree[v * 2 + 1].value) {
            tree[v] = tree[v * 2];
        }
        else {
            tree[v] = tree[v * 2 + 1];
        }
    }
}

Node segment_max(std::vector<Node> &tree, int v, int l, int r, int req_l, int req_r) {
    if (req_l > req_r)
        return {-1000000001, 0};
    if (req_l == l && req_r == r)
        return tree[v];

    int m = (l + r) / 2;
    Node left = segment_max(tree, v * 2, l, m, req_l, std::min(req_r, m));
    Node right = segment_max(tree, v * 2 + 1, m + 1, r, std::max(req_l, m + 1), req_r);

    if (left.value > right.value) {
        return left;
    }
    else {
        return right;
    }
}
 // }

 // НОД всех чисел на подотрезке {
int gcd(int a, int b) { if (a == 0) return b; return gcd(b % a, a); }

void build_gcd_tree(std::vector<int> &array, std::vector<int> &tree, int v, int l, int r) {
    if (l == r) {
        tree[v] = array[l];
    }
    else {
        int m = (l + r) / 2;
        build_tree(array, tree, v * 2, l, m);
        build_tree(array, tree, v * 2 + 1, m + 1, r);
        tree[v] = gcd(tree[v * 2], tree[v * 2 + 1]);
    }
}

int segment_gcd(std::vector<int> &tree, int v, int l, int r, int req_l, int req_r) {
    if (req_l > req_r)
        return 0;
    if (req_l == l && req_r == r)
        return tree[v];

    int m = (l + r) / 2;
    return gcd(segment_gcd(tree,v * 2,  l, m, req_l, std::min(req_r, m)),
               segment_gcd(tree,v * 2 + 1,  m + 1, r, std::max(req_l, m + 1), req_r));
}

void update(std::vector<int> &tree, int v, int l, int r, int position, int new_val) {
    if (l == r) {
        tree[v] = new_val;
    }
    else {
        int m = (l + r) / 2;
        if (position <= m) {
            update(tree, v * 2, l, m, position, new_val);
        }
        else {
            update(tree, v * 2 + 1, m + 1, r, position, new_val);
        }
        tree[v] = gcd(tree[v * 2], tree[v * 2 + 1]);
    }
}
 // }

// Поиск к-того нуля на подотрезке (выдает индекс)

void build_tree_kth(std::vector<int> &array, std::vector<int> &tree, int v, int l, int r) {
    if (l == r) {
        if (array[l] == 0)
            tree[v] = 1;
        else
            tree[v] = 0;
    }
    else {
        int m = (l + r) / 2;
        build_tree(array, tree, v * 2, l, m);
        build_tree(array, tree, v * 2 + 1, m + 1, r);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
}

int find_kth(std::vector<int> &tree, int v, int l, int r, int req_l, int req_r, int k) {
    if (k > tree[v]) {
        return -1;
    }
    if (l == r) {
        return l + 1;
    }
    int m = (l + r) / 2;
    if (req_l > m) {
        return find_kth(tree, v * 2 + 1, m + 1, r, req_l, req_r, k);
    }
    if (req_r <= m) {
        return find_kth(tree, v * 2, l, m, req_l, req_r, k);
    }
    auto abobus = segment_sum(tree,v * 2,  l, m, req_l, std::min(req_r, m));
    if (abobus >= k) {
        return find_kth(tree,v * 2,  l, m, req_l, std::min(req_r, m), k);
    }
    else {
        return find_kth(tree,v * 2 + 1, m + 1, r, std::max(req_l, m + 1), req_r, k - abobus);
    }

}

void update_kth(std::vector<int> &tree, int v, int l, int r, int position, int new_val) {
    if (l == r) {
        if (new_val == 0) {
            tree[v] = 1;
        }
        else {
            tree[v] = 0;
        }
    }
    else {
        int m = (l + r) / 2;
        if (position <= m) {
            update(tree, v * 2, l, m, position, new_val);
        }
        else {
            update(tree, v * 2 + 1, m + 1, r, position, new_val);
        }
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
}

// }


int main() {
    int n, req_l, req_r;
    std::cin >> n >> req_l >> req_r;
    std::vector<int> tree (4 * n);
    std::vector<int> array (n);

    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }

    build_tree(array, tree, 1, 0, n - 1);

    std::cout << std::endl << segment_sum(tree, 1, 0, n - 1, req_l, req_r);

    return 0;
}
