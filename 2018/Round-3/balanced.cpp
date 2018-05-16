#include <bits/stdc++.h> 

using namespace std;

typedef long long ll;

const ll MOD = 1e9+7;

ll f (ll n) {
    ll r = 1;
    while (n--) {
        r = (r*(n+1))%MOD;
    }
    return r;
}

ll mult (ll a, ll b) {
    return (a*b)%MOD;
}

ll valid(ll b, ll g) {
    if (b == 0)
        return 1;
    return g > 1 && (b % (g-1) == 0) && (b / (g-1)) % 2 ==0;
} 

int main () {
    int cases = 10;
    while (cases--) {
        ll b, g;
        cin >> b >> g;

        ll comp = 0;
        for (int i = 0; i <= b; ++i) {
            comp += valid(i, g)*(b-i+1);
            comp %= MOD;
        }

        comp = mult(mult(comp, f(g)), f(b));

        ll ans = ((f(b+g) - comp)%MOD + MOD)%MOD;
        cout << ans << "\n";
    }
}
