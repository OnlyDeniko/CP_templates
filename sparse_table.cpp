template <class B>
struct SparseTable{
  int N, LOG;
  vector<int> step_2;
  vector<vector<int>> sparse;
  B op;

  SparseTable(vector<int> & a, B _op) : N(a.size()), op(_op){
    for(int i = 1;i <= N;i <<= 1) step_2.push_back(i);
    LOG = step_2.size();
    sparse.resize(N, vector<int>(LOG));
    prepare_sparse_table(a);
  }

  void prepare_sparse_table(vector<int> & a){
    for(int i = 0;i < (int)a.size();i++) sparse[i][0] = a[i];
    for(int ind = 1;ind < (int)step_2.size();ind++){
      for(int i = 0;i < a.size();i++){
        if (i + step_2[ind] > a.size()) continue;
        int r = i + step_2[ind - 1];
        sparse[i][ind] = op(sparse[i][ind - 1], sparse[r][ind - 1]);
      }
    }
  }

  int query(int l, int r){
    int len = r - l + 1;
    int step = log2(len);
    return op(sparse[l][step],sparse[r - (1 << step) + 1][step]);
  }
};

//usage: SparseTable<function<int(int, int)>> sparse(a, [](int a, int b){return min(a, b);});