#include <bits/stdc++.h> 

using namespace std;

typedef long long ll;
typedef vector<ll> VI;
typedef pair<ll, ll> P;
typedef vector<P> VP;

bool f (ll N, ll M, VP factors) {
    for (auto &p : factors) {
        ll m = 0;
        ll b = p.first;
        while (b <= N) {
            m += N/b;
            b *= p.first;
        }
        if (m < p.second*M)
            return false; 
    }
    return true;
}

int main () {
    int cases = 10;
    while (cases--) {     
        ll k, m;
        cin >> k >> m;
        if (k == 1) {
            cout << "0\r\n";
            continue;
        }

        VP factors;
        ll sq = sqrt(k);
        for (ll i = 2; i <= sq; ++i) {
            if (k%i == 0) {
                ll c = 0;
                while (k%i == 0) {
                    k /= i;
                    ++c;
                }
                factors.push_back(make_pair(i, c));
            }
        }
        if (k > 1) {
            factors.push_back(make_pair(k, 1LL));
        }

        ll lo = 0, hi = 1e12, mi;
        while (lo+1 < hi) {
            mi = (lo+hi)/2;
            if (f(mi, m, factors)) hi = mi;
            else lo = mi;
        }
        cout << hi << "\r\n";
    }
}
