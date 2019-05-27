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

int main(){
    int T, N;
    cin >> T;

    while(T != 0) {
        cin >> N;

        vector<int> ns;
        REP(i, N) {
            int ev;
            cin >> ev;
            ns.push_back(ev);
        }

        reverse(ns.begin(), ns.end());

        int dp[N][T+1];
        memset(dp, 0, sizeof(dp));

        REP(i, N) {
            dbgp("nsi is " << ns[i]);
            if (i == 0 ) {
                dp[i][ns[i]] = 1;
            } else {
                dp[i][ns[i]] = 1;
                REP(j, T+1) {
                    if (dp[i-1][j] != 0) {
                        dp[i][j] = 2;
                    }
                }

                for(int j=ns[i];j<=T;j++){
                    if (dp[i-1][j-ns[i]] != 0) {
                        dp[i][j] = 3;
                    } else if (j==ns[i]) {
                        dp[i][j] = 1;
                    }
                }
            }
        }

        dbg(
        REP(i, N) {
            REP(j, T+1) {
                cerr << dp[i][j] << " ";
            }
            cerr << endl;
        }
        )

        vector<int> answer;

        int startI = T;
        for(startI = T; startI > 0; startI--){
            if (dp[N-1][startI] != 0) {
                break;
            }
        }

        if (startI != 0){
            for(int j=N-1;j>=0;j--) {
                if (dp[j][startI] == 3){
                    answer.push_back(ns[j]);
                    startI -= ns[j];
                } else if (dp[j][startI] == 1) {
                    answer.push_back(ns[j]);
                    break;
                } else if (dp[j][startI] == 0) {
                    throw "unexpected";
                }
            }
        }

        int total = 0;
        for(auto it: answer) {
            total += it;
        }

        for(auto it: answer) {
            cout << it << " ";
        }
        cout << total << endl;

        cin >> T;
    }
}
