#include <iostream>
#include <vector>

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