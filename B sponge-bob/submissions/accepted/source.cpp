#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll,ll> pii;
#define REP(i,n) for(ll i=0;i<n;i++)

#ifdef DEBUG
#define dbg(x) x
#define dbgp(x) cerr << x << endl;
#else
#define dbg(x) //x
#define dbgp(x) //cerr << x << endl;
#endif

#define MOD 100007
#define MAX_N 100002
#define MAX_DIM 7

int main() {
    int N;
    cin >> N;

    REP(i, N) {
        int a, b;
        cin >> a >> b;

        if (a == b){
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
