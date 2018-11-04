#include "mproblem.h"

LD funk(LD x, LD y){
    LD ans = - x - y;
    return ans;
}

LD ffunk(LD x0, LD y0, LD x){
    LD c = (1.0L - x0 - y0) / (exp(-x0));
    LD y = 1.0L - x - c * exp(-x);
    return y;
}

vector<pair<LD, LD> > exactSolution(LD x0, LD y0, LD h, LD X){
    vector<pair<LD, LD> > a;
    a.push_back({x0, y0});
    int n = static_cast<int>((X - x0) / h + 0.0001L);
    for(int i{1};i <= n;i ++){
        LD x = a[0].first + static_cast<LD>(i) * h;
        LD y = ffunk(x0, y0, x);
        a.push_back({x, y});
    }
    return a;
}

vector<pair<LD, LD> > euler_method(LD x0, LD y0, LD h, LD X){
    vector<pair<LD, LD> > a;
    a.push_back(make_pair(x0, y0));
    int n = static_cast<int>((X - x0) / h + 0.0001L);
    for (int i = 1; i <= n; i ++){
        LD x = a[0].first + static_cast<LD>(i) * h;
        LD y = a.back().second + h * funk(a.back().first, a.back().second);
        a.push_back(make_pair(x, y));
    }
    return a;
}

vector<pair<LD, LD> > euler_improved_method(LD x0, LD y0, LD h, LD X){
    vector<pair<LD, LD> > a;
    a.push_back(make_pair(x0, y0));
    int n = static_cast<int>((X - x0) / h + 0.0001L);
    for (int i = 1; i <= n; i ++){
        LD xi = a.back().first;
        LD yi = a.back().second;
        LD x = a[0].first + static_cast<LD>(i) * h;
        LD last = funk(xi, yi);
        LD y = yi + (h / 2.0L) * (last + funk(x, yi + h * last));
        a.push_back(make_pair(x, y));
    }
    return a;
}

vector<pair<LD, LD> > runge_kutte(LD x0, LD y0, LD h, LD X){
    vector<pair<LD, LD> > a;
    a.push_back(make_pair(x0, y0));
    int n = static_cast<int>((X - x0) / h + 0.0001L);
    for (int i = 1; i <= n; i ++){
        LD xi = a.back().first;
        LD yi = a.back().second;
        LD k1i = funk(xi, yi);
        LD k2i = funk(xi + h / 2.0L, yi + (h / 2.0L) * k1i);
        LD k3i = funk(xi + h / 2.0L, yi + (h / 2.0L) * k2i);
        LD k4i = funk(xi + h, yi + h * k3i);
        LD x = a.front().first + h * static_cast<LD>(i);
        LD y = yi + (h / 6.0L) * (k1i + 2.0L * k2i + 2.0L * k3i + k4i);
        a.push_back(make_pair(x, y));
    }
    return a;
}

vector<pair<LD, LD> > error_function(const vector<pair<LD, LD> > &euler_val, const vector<pair<LD, LD> > &exact_val){
    vector<pair<LD, LD> > sol;
    LD maximum{static_cast<LD>(numeric_limits<LD>::lowest())};
    cerr << numeric_limits<LD>::lowest() << endl;

    for(size_t i{0};i < euler_val.size();i ++){
        sol.push_back({euler_val[i].first, fabs(euler_val[i].second - exact_val[i].second)});
        maximum = max(maximum, sol.back().second);
    }
    return sol;
}

LD maximum(const vector<pair<LD, LD> > &a){
    LD maxNum{numeric_limits<LD>::lowest()};
    for(auto x: a)maxNum = max(maxNum, x.second);
    return maxNum;
}

vector<vector<pair<LD, LD> > > error_dep_h(LD x, LD y, LD X, LD h0, LD h1, LD hh){
    vector<vector<pair<LD, LD> > > ans(3);
    for(LD h{h0};h <= h1;h += hh){
        vector<pair<LD, LD> > ee = error_function(euler_method(x, y, h, X), exactSolution(x, y, h, X));
                                ans[0].push_back({h, maximum(ee)});
        vector<pair<LD, LD> > eie = error_function(euler_improved_method(x, y, h, X), exactSolution(x, y, h, X));
                                ans[1].push_back({h, maximum(eie)});
        vector<pair<LD, LD> > rk = error_function(runge_kutte(x, y, h, X), exactSolution(x, y, h, X));
                                ans[2].push_back({h, maximum(rk)});
    }
    return ans;
}


vector<vector<pair<LD, LD> > > solve(LD x, LD y, LD h, LD X){
    vector<vector<pair<LD, LD> > > t(11);
    for(size_t i = 0;i < 5;i ++)t[i] = vector<pair<LD, LD> >();
    for(LD i{x}; i < X + eps; i += 0.1L)t[1].push_back(make_pair(i, i));
    t[0] = exactSolution(x, y, h, X);
    t[2] = euler_method(x, y, h, X);
    t[3] = euler_improved_method(x, y, h, X);
    t[4] = runge_kutte(x, y, h, X);
    t[5] = error_function(t[2], t[0]);
    t[6] = error_function(t[3], t[0]);
    t[7] = error_function(t[4], t[0]);
    vector<vector<pair<LD, LD> > > temp = error_dep_h(x, y, X, 0.01L, 1.0L, 0.01L);
    t[8] = temp[0];
    t[9] = temp[1];
    t[10] = temp[2];
    return t;
}

pair<pair<LD, LD>, pair<LD, LD> > arrange(const vector<pair<LD, LD> > &a){
    pair<pair<LD, LD>, pair<LD, LD> > t{{MAX_DOUBLE, MIN_DOUBLE}, {MAX_DOUBLE, MIN_DOUBLE}};
    for(size_t i{};i < a.size(); ++i){
        t.first.first = min(t.first.first, a[i].first);
        t.first.second = min(t.first.second, a[i].second);
        t.second.first = max(t.second.first, a[i].first);
        t.second.second = max(t.second.second, a[i].second);
    }
    return t;
}

size_t fno_of_ticks(const vector<pair<LD, LD> > &a){
    return a.size();
}
