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

ll aTree[MAX_N*3];
ll bTree[MAX_N*3];

void increment(ll *tree, ll treeStart, ll rangeStart, ll rangeEnd, ll targetStart, ll targetEnd, ll incrementBy) {
    if (rangeStart >= targetEnd || rangeEnd <= targetStart) {
        return;
    }
    if (targetStart <= rangeStart && rangeEnd <= targetEnd) {
        tree[treeStart]+=incrementBy;
        return;
    }
    ll middle = (rangeStart + rangeEnd)/2;
    increment(tree, treeStart*2, rangeStart, middle, targetStart, targetEnd, incrementBy);
    increment(tree, treeStart*2+1, middle, rangeEnd, targetStart, targetEnd, incrementBy);
}

void fillTree(ll *tree, ll treeStart, ll rangeStart, ll rangeEnd, ll *target) {
    if (rangeEnd - rangeStart == 1) {
        target[0] += tree[treeStart];
        return;
    }

    ll n = rangeEnd - rangeStart;
    REP(i, n) {
        target[i] += tree[treeStart];
    }
    
    ll middle = (rangeStart + rangeEnd)/2;
    fillTree(tree, treeStart*2, rangeStart, middle, target);
    fillTree(tree, treeStart*2+1, middle, rangeEnd, target + (middle - rangeStart));
}

ll slowCalculateIt(ll a, ll b) {

    ll buff = b+1;
    ll arr[buff];
    memset(arr, 0, sizeof(arr));

    REP(i, a) {
        ll ip = i+1;
        if (ip <= b) {
            arr[ip%buff] = 1;
        } else {
            arr[ip%buff] = 0;
            REP(ii, b) {
                arr[ip%buff] += arr[(ip+buff-1-ii)%buff];
                arr[ip%buff] %= MOD;
            }
        }
    }

    dbgp("calc " << a << " " << b << " " << arr[a%buff]);
    REP(i, buff) {
        dbgp(arr[i]);
    }
    return arr[a%buff];
}

void matrixMult(ll **first, ll **second, ll **target, ll dimension) {
    REP(i, dimension) {
        REP(ii, dimension) {
            target[i][ii] = 0;
        }
    }

    REP(i, dimension) {
        REP(ii, dimension) {
            REP(iii, dimension) {
                target[i][ii] += first[i][iii]*second[iii][ii];
                target[i][ii] %= MOD;
            }
        }
    }
}

void copyMatx(ll **first, ll **second, ll dimension) {
    REP(i, dimension) {
        REP(ii, dimension) {
            second[i][ii] = first[i][ii];
        }
    }
}

void matrixPower(ll **base, ll **target, ll dimension, ll pow) {
    if (pow == 0) throw "unexpected";
    if (pow == 1) {
        copyMatx(base, target, dimension);
        return;
    }

    ll **newMat = new ll*[dimension];
    REP(i, dimension) {
        newMat[i] = new ll[dimension];
        REP(ii, dimension) {
            newMat[i][ii] = 0;
        }
    }

    matrixPower(base, newMat, dimension, pow/2);
    matrixMult(newMat, newMat, target, dimension);
    if (pow%2) {
        copyMatx(target, newMat, dimension);
        matrixMult(newMat, base, target, dimension);
    }

    REP(i, dimension) {
        delete newMat[i];
    }
    delete newMat;
}

ll calculateIt(ll a, ll b) {
    if (a <= b) return 1;
    b = b%MAX_DIM;

    ll dimension = b;
    ll **baseMat = new ll*[dimension];
    REP(i, dimension) {
        baseMat[i] = new ll[dimension];
        REP(ii, dimension) {
            if (i == 0 || (ii-i) == -1) {
                baseMat[i][ii] = 1;
            } else {
                baseMat[i][ii] = 0;
            }
        }
    }

    ll **newMat = new ll*[dimension];
    REP(i, dimension) {
        newMat[i] = new ll[dimension];
        REP(ii, dimension) {
            newMat[i][ii] = 0;
        }
    }

    ll raiseCount = a-b;
    matrixPower(baseMat, newMat, dimension, raiseCount);
    ll answer = 0;
    REP(i, dimension) {
        answer += newMat[0][i];
        answer %= MOD;
    }

    REP(i, dimension) {
        delete newMat[i];
        delete baseMat[i];
    }
    delete newMat;
    delete baseMat;

    /*
    dbg(
    ll slowAnswer = slowCalculateIt(a, b);
    dbgp("CI " << answer << " " << slowAnswer);
    if (answer != slowAnswer) {
        throw string("answer mismatch");
    }
    )
    */
    dbgp("CIT " << a << " " << b << " " << answer);
    return answer;
}

int main(){
    int n, m;
    cin >> n >> m;

    memset(aTree, 0, sizeof(aTree));
    memset(bTree, 0, sizeof(bTree));

    // First value
    aTree[1] = 1;
    bTree[1] = 1;

    REP(i, m) {
        char c;
        ll j, k, h;
        cin >> c >> j >> k >> h;
        j--;
        k--;
        ll *tree;
        if (c == 'a') {
            tree = aTree;
        } else {
            tree = bTree;
        }
        if (k >= j) {
            increment(tree, 1, 0, n, j, k+1, h);
        } else {
            increment(tree, 1, 0, n, j, n, h);
            increment(tree, 1, 0, n, 0, k+1, h);
        }
    }
 
    ll finalA[n];
    ll finalB[n];
    memset(finalA, 0, sizeof(finalA));
    memset(finalB, 0, sizeof(finalB));

    fillTree(aTree, 1, 0, n, finalA);
    fillTree(bTree, 1, 0, n, finalB);

    ll total = 0;
    REP(i, n) {
        ll ans = calculateIt(finalA[i], finalB[i]);
        total += ans;
        // dbgp(ans);
    }
    cout << total << endl;
}
