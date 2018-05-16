#include <bits/stdc++.h> 

using namespace std;

typedef pair<int, int> P;
typedef vector<P> VP;

VP filter (VP &pnts, int minx, int miny, int maxx, int maxy) {
    VP res;
    for (auto &p : pnts) {
        if (!(p.first >= minx && p.first <= maxx && p.second >= miny && p.second <= maxy))
            res.push_back(p);
    }
    return res;
}

bool f (VP pnts, int L, int sq = 3) {
    int minx = 1e9, miny = 1e9, maxx = -1e9, maxy = -1e9;
    for (auto &p : pnts) {
        minx = min(p.first, minx);
        miny = min(p.second, miny);
        maxx = max(p.first, maxx); 
        maxy = max(p.second, maxy);
    }
    if (sq == 1) {
        return max(maxy-miny, maxx-minx) <= L; 
    }

    bool res = false;
    // minx, miny.
    res |= f(filter(pnts, minx, miny, minx+L, miny+L), L, sq-1);
    // minx, maxy
    res |= f(filter(pnts, minx, maxy-L, minx+L, maxy), L, sq-1);
    // maxx, maxy
    res |= f(filter(pnts, maxx-L, maxy-L, maxx, maxy), L, sq-1);
    // maxx, miny
    res |= f(filter(pnts, maxx-L, miny, maxx, miny+L), L, sq-1);
    return res;
}

int main () {
    int cases = 10;
    while (cases--) {
        int n;
        cin >> n;
        VP pnts(n);
        for (int i = 0; i < n; ++i) {
            cin >> pnts[i].first >> pnts[i].second;
        }

        int lo = 0, hi = 2e9+10, mi;
        while (lo + 1 < hi) {
            mi = lo + (hi-lo)/2;
            if (f(pnts, mi)) hi = mi;
            else lo = mi;
        }
        cout << hi << "\r\n";
    }
}
