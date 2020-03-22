#include<cstdio>
#include<vector>
#include<queue>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<iterator>

#define mk make_pair
#define pb push_back

using namespace std;

vector<pair<int, int> > heap(1);

void up(int k){
    if (k == 1) return;
    int p = k / 2;
    if (heap[p].first > heap[k].first){
        swap(heap[p], heap[k]);
        up(p);
    }
}

void add(int x, int q){
    heap.pb(mk(x, q));
    up(heap.size() - 1);
}

void down(int k){
    if (2 * k > heap.size()) return;
    int p = 2 * k;
    if (p + 1 <= heap.size() && heap[p + 1].first < heap[p].first){
        p++;
    }
    if (heap[p].first < heap[k].first){
        swap(heap[p], heap[k]);
        down(p);
    }
}

void extract(){
    heap[1] = heap[heap.size() - 1];
    heap.pop_back();
    down(1);
}

int main(){
    //ifstream fin("input.txt");
    //ofstream fout("output.txt");
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0;i < n;i++){
        cin >> a[i];
    }
    for (int i = 0;i < k;i++){
        add(a[i], i);
    }
    cout << heap[1].first << endl;
    for (int i = 1;i <= n - k;i++){
        while (heap[1].second < i && heap.size() > 1){
            extract();
        }
        add(a[i + k - 1], i + k - 1);
        cout << heap[1].first << endl;
    }

    return 0;
}
