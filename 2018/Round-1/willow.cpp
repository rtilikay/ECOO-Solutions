#include <bits/stdc++.h> 

using namespace std;

int main () {
    int cases = 10;
    while (cases--) {
        int t, n;
        cin >> t >> n;
        int delay = 0;
        while (n--) {
            char c;
            cin >> c;
            if (c == 'B')
                delay += t;
            if (delay > 0)
                --delay;
        }
        cout << delay << "\n";
    }
}
