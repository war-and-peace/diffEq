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

vector<vector<pair<LD, LD> > > solve(LD x, LD y, LD h, LD X){
    vector<vector<pair<LD, LD> > > t(5);
    for(size_t i = 0;i < 5;i ++)t[i] = vector<pair<LD, LD> >();
    for(LD i{x}; i < X + eps; i += 0.1L)t[1].push_back(make_pair(i, i));
    t[0] = exactSolution(x, y, h, X);
    t[2] = euler_method(x, y, h, X);
    t[3] = euler_improved_method(x, y, h, X);
    t[4] = runge_kutte(x, y, h, X);
    return t;
}