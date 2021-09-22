const int N = 1e6;
const int LOG = 25;
int sparse[N][LOG];
vector<int> step_2;

void prepare_sparse_table(vector<int> & a){
    for(int i = 1;i <= N;i <<= 1) step_2.push_back(i);
    for(int i = 0;i < a.size();i++) sparse[i][0] = a[i];
    for(int ind = 1;ind < step_2.size();ind++){
        for(int i = 0;i < a.size();i++){
            if (i + step_2[ind] > a.size()) continue;
            int r = i + step_2[ind - 1];
            sparse[i][ind] = min(sparse[i][ind - 1], sparse[r][ind - 1]);
        }
    }
}

int query(int l, int r){
    int gg = r - l + 1;
    int step = (int)log2(gg);
    return min(sparse[l][step],sparse[r - (1 << step) + 1][step]);
}
