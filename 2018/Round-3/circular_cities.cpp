#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> VI;

struct S {
    int s, t;
    ll f, b;

    vector<ll> ls, lt;
    vector<ll> rs, rt;
    vector<ll> vs, vt;

    S(int s, int t, int f, int b) : s(s), t(t), f(f), b(b),
        ls(s+1, 0), rs(s+1, 0), vs(s+1, 0),
        lt(t+1, 0), rt(t+1, 0), vt(t+1, 0) {}
};

S dnc(vector<pair<int, int>> &a, int l, int r) {
    if (r - l == 1) {
        return S(a[l].second > 0, a[l].second < 0, a[l].first, a[l].first);
    }

    int m = (l+r)/2;
    S left = dnc(a, l, m);
    S right = dnc(a, m, r);

    S ret(left.s+right.s, left.t + right.t, left.f, right.b);

    for (int i = 0; i <= ret.t; ++i) {
        int lc = min(i, left.t);
        ret.lt[i] = left.lt[lc] + right.lt[i-lc] + (i-lc)*(right.f - left.f);
        ret.vt[i] = left.vt[lc];
        int res = left.s - (left.t-lc);
        if (res >= 0) {
            if (res + (i-lc) > right.t) {
                int diff = res + (i-lc) - right.t;
                ll lrt = diff > lc ? left.rs[diff-lc] : left.rt[lc-diff];
                ret.vt[i] += lrt + (right.lt[right.t] - right.lt[i-lc]) + (res-diff)*(right.f - left.b) + right.vt[right.t];
                ret.rt[i] = right.rt[right.t] + (left.rt[lc] - lrt) + diff*(right.b - left.b);
            } else {
                ret.vt[i] += left.rt[lc] + (right.lt[res + (i-lc)] - right.lt[i-lc]) + res*(right.f - left.b) + right.vt[res + (i-lc)];
                ret.rt[i] = right.rt[res + (i-lc)];
            }
        } else {
            // i-lc == 0 here.
            res = -res;
            if (res > right.s) {
                int diff = res - right.s;
                ll lrt = left.rt[lc+diff];
                ret.vt[i] += lrt + right.ls[right.s] + (res-diff)*(right.f - left.b) + right.vs[right.s];
                ret.rt[i] = right.rs[right.s] + (left.rt[lc] - lrt) + diff*(right.b - left.b);
            } else {
                ret.vt[i] += left.rt[lc] + right.ls[res] + res*(right.f - left.b) + right.vs[res];
                ret.rt[i] = right.rs[res];
            }
        }
    }
    for (int i = 0; i <= ret.s; ++i) {
        int lc = min(i, left.s);
        ret.ls[i] = left.ls[lc] + right.ls[i-lc] + (i-lc)*(right.f - left.f);
        ret.vs[i] = left.vs[lc];
        int res = left.t - (left.s-lc);
        if (res >= 0) {
            if (res + (i-lc) > right.s) {
                int diff = res + (i-lc) - right.s;
                ll lrs = diff > lc ? left.rt[diff-lc] : left.rs[lc-diff];
                ret.vs[i] += lrs + (right.ls[right.s] - right.ls[i-lc]) + (res-diff)*(right.f - left.b) + right.vs[right.s];
                ret.rs[i] = right.rs[right.s] + (left.rs[lc] - lrs) + diff*(right.b - left.b);
            } else {
                ret.vs[i] += left.rs[lc] + (right.ls[res + (i-lc)] - right.ls[i-lc]) + res*(right.f - left.b) + right.vs[res + (i-lc)];
                ret.rs[i] = right.rs[res + (i-lc)];
            }
        } else {
            // i-lc == 0 here.
            res = -res;
            if (res > right.t) {
                int diff = res - right.t;
                ll lrs = left.rs[lc+diff];
                ret.vs[i] += lrs + right.lt[right.t] + (res-diff)*(right.f - left.b) + right.vt[right.t];
                ret.rs[i] = right.rt[right.t] + (left.rs[lc] - lrs) + diff*(right.b - left.b);
            } else {
                ret.vs[i] += left.rs[lc] + right.lt[res] + res*(right.f - left.b) + right.vt[res];
                ret.rs[i] = right.rt[res];
            }
        }
    }
    return ret;
}

int main () {
    int tt = 10;
    while (tt--) {
        long long n, m;
        cin >> n >> m;

        vector<pair<int, int>> a(2*n);
        for (int i = 0; i < n; ++i) {
            int s;
            cin >> s;
            a[i] = make_pair(s, 1);
        }
        for (int i = 0; i < n; ++i) {
            int t;
            cin >> t;
            a[n+i] = make_pair(t, -1);
        }
        sort(a.begin(), a.end());

        S ret = dnc(a, 0, 2*n);

        ll ans = 1e18;
        for (int i = 0; i <= ret.t; ++i) {
            ans = min(ans, ret.vt[i] + ret.lt[i] + ret.rt[i] + ret.f*i + (m - ret.b)*i);
        }
        for (int i = 0; i <= ret.s; ++i) {
            ans = min(ans, ret.vs[i] + ret.ls[i] + ret.rs[i] + ret.f*i + (m - ret.b)*i);
        }
        cout << ans << endl;
    }
}
