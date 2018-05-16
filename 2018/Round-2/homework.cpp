#include <bits/stdc++.h> 

using namespace std;

typedef pair<double, int> P;
typedef vector<P> VP;

const int MAXD = 1010101;

int djs[MAXD];

int par(int n) {
    return djs[n] == n ? n : djs[n] = par(djs[n]);
}

int merge(int a, int b) {
    djs[par(a)] = djs[par(b)];
}

int main () {
    int cases = 10;
    while (cases--) {
        int n; 
        cin >> n;
        VP arr(n);
        for (int i = 0; i < n; ++i) {
            double p; 
            int d;
            cin >> d >> p;
            arr[i] = make_pair(p, d);
        }
        sort(arr.begin(), arr.end());

        for (int i = 0; i < MAXD; ++i)
            djs[i] = i;

        double ans = 0;
        for (int i = n-1; i >= 0; --i) {
            double p = arr[i].first;
            int d = arr[i].second;
            if (par(d) == 0)
                continue;
            ans += p;
            djs[par(d)] = par(par(d) - 1);
        }
        cout << fixed << setprecision(4) << ans << "\r\n";
    }
}
