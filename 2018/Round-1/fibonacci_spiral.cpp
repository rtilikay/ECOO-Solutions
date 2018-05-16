#include <bits/stdc++.h> 

using namespace std;

typedef long long ll;

ll fib [51];

bool contains (ll x, ll y, int i, ll tx, ll ty) {
    return tx >= x && tx <= x + fib[i] && ty <= y && ty >= y - fib[i];
}

int main () {
    fib[1] = fib[2] = 1;
    for (int i = 3; i <= 50; ++i)
        fib[i] = fib[i-1] + fib[i-2];

    int cases = 10;
    while(cases--) {
        ll tx, ty;
        cin >> tx >> ty;

        ll x = 0, y = 0;
        for (int i = 1; i <= 50; ++i) {
            if (contains(x, y, i, tx, ty)) {
                cout << i << "\r\n";
                break;
            }
            if (i % 4 == 1) {
                x -= fib[i+1];
                y += fib[i-1];
            } else if (i % 4 == 2) {
                y += fib[i+1];
            } else if (i % 4 == 3) {
                x += fib[i];
            } else {
                x -= fib[i-1];
                y -= fib[i];
            }
        }
    }
}
