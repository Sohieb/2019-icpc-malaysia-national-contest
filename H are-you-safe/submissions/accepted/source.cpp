#define _USE_MATH_DEFINES
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

#define EPS 0.000000001

double calcangle(ll first, ll second) {
    double angle = atan2(first, second);
    if (angle < 0) angle += 2*M_PI;
    return angle;
}

void solve() {
    int R, Q;
    cin >> R >> Q;
    
    vector<pii> points;
    REP(i, R) {
        pii p;
        cin >> p.first >> p.second;
        points.push_back(p);
    }

    sort(points.begin(), points.end());

    vector<pii> perimeter;
    pii cur = points[0];
    pii prev = make_pair(cur.first, cur.second+1);

    bool firstDone = false;
    double lastAngle = 0;
    while(cur != points[0] || (firstDone == false && cur == points[0])) {
            dbgp("cur " << cur.first << " " << cur.second << " " << lastAngle);
        perimeter.push_back(cur);

        pii nextPii;
        double minDiff = 100;
        for(auto next: points) {
            if (next == cur) continue;

            double angle = calcangle(next.first - cur.first, next.second - cur.second) - lastAngle;
            if (angle < 0) continue;
            if (angle < minDiff) {
                minDiff = angle;
                nextPii = next;
            }
        }

        lastAngle = calcangle(nextPii.first - cur.first, nextPii.second - cur.second);
        cur = nextPii;
        firstDone = true;
    }

    reverse(perimeter.begin()+1, perimeter.end());
    for(auto it: perimeter) {
        cout << it.first << " " << it.second << endl;
    }
    cout << perimeter[0].first << " " << perimeter[0].second << endl;

    vector<pair<pii,pii>> vectorPair;
    REP(i, perimeter.size()) {
        pii p1 = perimeter[i];
        pii p2 = perimeter[(i+1)%perimeter.size()];
        if (p1.second < p2.second) {
            swap(p1, p2);
        }
        vectorPair.push_back(make_pair(p1, p2));
    }

    REP(i, Q) {
        pii q;
        cin >> q.first >> q.second;

        bool onPoint = false;
        int before = 0;
        int after = 0;
        for(auto it: vectorPair) {
            if (it.first.second >= q.second && it.second.second <= q.second) {
                dbgp("igetting " << it.first.first << " " << it.first.second << " " << it.second.first << " " << it.second.second);
                double theX;
                if (it.first.second == it.second.second) {
                    if (q.first > it.first.second && q.first < it.second.second) {
                        onPoint = true;
                        continue;
                    }
                } else if (it.first.first == it.second.first) {
                    theX = it.first.first;
                } else {
                    double grad = (q.second-it.first.second)*
                        (it.second.first-it.first.first)/(it.second.second-it.first.second);
                    dbgp("grad " << grad);
                    theX = it.first.first + grad;
                }
                dbgp("thex " << theX);
                if (q.first > theX) {
                    after++;
                } else {
                    before++;
                }
            }
        }

        if (onPoint || (before >= 1 && after >= 1)){
            cout << q.first << " " << q.second << " is unsafe!" << endl;
        } else {
            cout << q.first << " " << q.second << " is safe!" << endl;
        }
    }
}

int main(){
    int N;
    cin >> N;
    REP(i, N){
        if (i != 0) cout << endl;
        cout << "Case " << i+1 << endl;
        solve();
    }
}
