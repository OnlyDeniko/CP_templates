#include<bits/stdc++.h>

using namespace std;

mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());

struct node{
    int x, y;
    node* left;
    node* right;
    node(int val){
        x = val;
        y = (rand() << 15) + rand();
        left = right = nullptr;
    }
    ~node(){
        if (left) delete left;
        if (right) delete right;
    }
};

bool exist(node* root, int val){
    if (root == nullptr) return false;
    if (root->x == val) return true;
    if (val > root->x) return exist(root->right, val);
    return exist(root->left, val);
}

pair<node*, node*> split(node* root, int val){
    if (root == nullptr){
        return {nullptr, nullptr};
    }
    if (root->x <= val){
        auto res = split(root->right, val);
        root->right = res.first;
        return {root, res.second};
    }
    else {
        auto res = split(root->left, val);
        root->left = res.second;
        return {res.first, root};
    }
}

node* merge(node* root1, node* root2){
    if (root1 == nullptr) return root2;
    if (root2 == nullptr) return root1;
    if (root1->y <= root2->y){
        root1->right = merge(root1->right, root2);
        return root1;
    }
    else {
        root2->left = merge(root1, root2->left);
        return root2;
    }
}

node* insert(node* root, int val){
    if (exist(root, val)) return root;
    auto kek = split(root, val);
    node* newnode = new node(val);
    return merge(merge(kek.first, newnode), kek.second);
}

node* erase(node* root, int val){
    if (!exist(root, val)) return root;
    auto kek = split(root, val);
    auto lol = split(kek.first, val - 1);
    delete lol.second;
    return merge(lol.first, kek.second);
}

void print(node* root){
    if (!root) return;
    print(root->left);
    cout << root->x << ' ';
    print(root->right);
}

int depth(node* root){
    if (root == nullptr) return 0;
    return 1 + max(depth(root->left), depth(root->right));
}

signed main(){
    node* q = nullptr;
    for(int i = 1; i <= 10000000; i++) {
        q = insert(q, i);
    }
    cout << depth(q);
//    for(int i = 2;i < 100;i += 2) q = erase(q, i);
//    print(q);
    return 0;
}
