#ifndef MPROBLEM_H
#define MPROBLEM_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <ios>
#include <fstream>
#include <numeric>
#include <limits>
#include <algorithm>

using namespace std;
using std::ios_base;
using std::ios;
using LL = long long;
using ULL = unsigned long long;
using LD = long double;
using std::string;

#define _1 first
#define _2 second

const int MAXN = 1000;
const LD eps = 1e-9L;
const LD MAX_DOUBLE = numeric_limits<LD>::max();
const LD MIN_DOUBLE = numeric_limits<LD>::lowest();
const LD H0{0.01L}, H1{1.0L}, HH{0.01L};
vector<vector<pair<LD, LD> > > solve(LD x, LD y, LD h, LD X);
pair<pair<LD, LD>, pair<LD, LD> > arrange(const vector<pair<LD, LD> > &a);
size_t fno_of_ticks(const vector<pair<LD, LD> > &a);
#endif // MPROBLEM_H
