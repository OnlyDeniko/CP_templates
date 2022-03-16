#include<bits/stdc++.h>

using namespace std;

mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());

struct node{
    int data, y, size, min;
    node* left;
    node* right;
    node(int val){
        data = val;
        y = gen();
        y = abs(y);
        size = 1;
        min = data;
        left = right = nullptr;
    }
    ~node(){
        if (left) delete left;
        if (right) delete right;
    }
};

int get_size(node* root){
    return (root ? root->size : 0);
}

int get_min(node * root){
    return (root ? root->min : INT_MAX);
}

void update(node * root){
    if (!root) return;
    root->size = 1 + get_size(root->left) + get_size(root->right);
    root->min = min({root->data, get_min(root->left), get_min(root->right)});
}

//numeration from 1!
int & kth(node* root, int k){
    if (k <= get_size(root->left)) return kth(root->left, k);
    if (k == get_size(root->left) + 1) return root->data;
    return kth(root->right,
            k - get_size(root->left) - 1);
}

pair<node*, node*> split_kth(node* root, int k){
    if (root == nullptr){
        return {nullptr, nullptr};
    }
    if (k <= get_size(root->left)){
        auto res = split_kth(root->left, k);
        root->left = res.second;
        update(root);
        return {res.first, root};
    }
    else {
        auto res = split_kth(root->right, k - 1 - get_size(root->left));
        root->right = res.first;
        update(root);
        return {root, res.second};
    }
}

node* merge(node* root1, node* root2){
    if (root1 == nullptr) return root2;
    if (root2 == nullptr) return root1;
    if (root1->y <= root2->y){
        root1->right = merge(root1->right, root2);
        update(root1);
        return root1;
    }
    else {
        root2->left = merge(root1, root2->left);
        update(root2);
        return root2;
    }
}
void print(node* root){
    if (!root) return;
    print(root->left);
    cout << root->data << ' ';
    print(root->right);
}

node* insert(node * root, int place, int val){
    auto sp = split_kth(root, place);
    node * lol = new node(val);
    root = merge(merge(sp.first, lol), sp.second);
    update(root);
    return root;
}

node* erase(node* root, int pos){
    auto kek = split_kth(root, pos);
    auto lol = split_kth(kek.first, pos - 1);
    delete lol.second;
    return merge(lol.first, kek.second);
}

int get_min_on_segment(node * root, int l, int r){
    auto qwe1 = split_kth(root, r);
    int ans;
    auto qwe2 = split_kth(qwe1.first, l - 1);
    ans = get_min(qwe2.second);
    root = merge(merge(qwe2.first, qwe2.second),
                qwe1.second);
    return ans;
}

node* root = nullptr;
// insert, erase, get_min_on_segment, print
