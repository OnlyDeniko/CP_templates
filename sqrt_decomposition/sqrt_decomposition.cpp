struct decomp{
    int gr = 256;
    int n;
    vector<int> a, val, add, minn;
    vector<int> sum;

    decomp(const vector<int> & aa)
        :n(aa.size())
        , a(aa)
        , val(1 + (n-1) / gr, INT_MAX)
        , add(1 + (n- 1) / gr, 0)
        , minn(1 + (n- 1) / gr, INT_MAX)
        , sum(1 + (n- 1) / gr, 0)
    {
        for(int i = 0;i < n;i++){
            minn[i / gr] = min(a[i], minn[i / gr]);
            sum[i / gr] += a[i];
        }
    }
    int grst(int g){
        return g * gr;
    }
    int get(int pos){
        int g = pos / gr;
        if (val[g] != INT_MAX){
            return val[g];
        }
        else return a[pos] + add[g];
    }
    int afterG(int g){
        return min(n, (g + 1) * gr);
    }
    void norm(int g){
        int aft = afterG(g);
        if (val[g] != INT_MAX){
            minn[g] = INT_MAX;
            sum[g] = 0;
            for(int i = grst(g);i < aft;i++){
                a[i] = val[g];
            }
            val[g] = INT_MAX;
            add[g] = 0;
            minn[g] = INT_MAX;
            sum[g] = 0;
        }
        else if (add[g] != 0){
            for(int i = grst(g);i < aft;i++){
                a[i] += add[g];
            }
            add[g] = 0;
        }

    }
    void calc(int g){
        int aft = afterG(g);
        minn[g] = INT_MAX;
        sum[g] = 0;
        for(int i = grst(g);i < aft;i++){
            minn[g] = min(minn[g], a[i]);
            sum[g] += a[i];
        }
    }
    void update(int l, int r, int x){
        int lg = l / gr;
        int rg = r / gr;
        if (lg == rg){
            norm(lg);
            for(int i = l;i < r + 1;i++){
                a[i] = x;
            }
            calc(lg);
        }
        else {
            norm(lg);
            int afterL = afterG(lg);
            for(int i = l;i < afterL;i++){
                a[i] = x;
            }
            calc(lg);
            for(int g = lg + 1;g < rg;g++){
                val[g] = x;
            }
            norm(rg);
            for(int i = grst(rg);i < r + 1;i++){
                a[i] = x;
            }
            calc(rg);
        }
    }
    void add(int l, int r, int x){
        int lg = l / gr;
        int rg = r / gr;
        if (lg == rg){
            norm(lg);
            for(int i = l;i < r + 1;i++){
                a[i] += x;
            }
            calc(lg);
        }
        else {
            norm(lg);
            int afterL = afterG(lg);
            for(int i = l;i < afterL;i++){
                a[i] += x;
            }
            calc(lg);
            for(int g = lg + 1;g < rg;g++){
                if (val[g] == INT_MAX){
                    add[g] += x;
                    minn[g] += x;
                    sum[g] += 1LL * gr * x;
                }
                else val[g] += x;
            }
            norm(rg);
            for(int i = grst(rg);i < r + 1;i++){
                a[i] += x;
            }
            calc(rg);
        }
    }
    int rsq(int l, int r){
        int summ = 0;
        int lg = l / gr;
        int rg = r / gr;
        if (lg == rg){
            norm(lg);
            for(int i = l;i < r + 1;i++){
                summ += a[i];
            }
            calc(lg);
        }
        else {
            norm(lg);
            int afterL = afterG(lg);
            for(int i = l;i < afterL;i++){
                summ += a[i];
            }
            calc(lg);
            for(int g = lg + 1;g < rg;g++){
                if (val[g] == INT_MAX){
                    summ += sum[g];
                }
                else summ += 1LL * gr * val[g];
            }
            norm(rg);
            for(int i = grst(rg);i < r + 1;i++){
                summ += a[i];
            }
            calc(rg);
        }
        return summ;
    }
    int rmq(int l, int r){
        int mi = INT_MAX;
        int lg = l / gr;
        int rg = r / gr;
        if (lg == rg){
            norm(lg);
            for(int i = l;i < r + 1;i++){
                mi = min(mi, a[i]);
            }
            calc(lg);
        }
        else {
            norm(lg);
            int afterL = afterG(lg);
            for(int i = l;i < afterL;i++){
                mi = min(mi, a[i]);
            }
            calc(lg);
            for(int g = lg + 1;g < rg;g++){
                if (val[g] == INT_MAX){
                    mi = min(mi, minn[g]);
                }
                else mi = min(mi, val[g]);
            }
            norm(rg);
            for(int i = grst(rg);i < r + 1;i++){
                mi = min(mi, a[i]);
            }
            calc(rg);
        }
        return mi;
    }
};
