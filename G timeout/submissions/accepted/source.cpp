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

#define MOD 1000000007
#define MAX_ENDPOINT 20001
#define MAX_TASK 101

ll endpointRuntimeCache[MAX_ENDPOINT];
ll taskRuntimeCache[MAX_ENDPOINT][MAX_TASK];
pii endpointInstructions[MAX_ENDPOINT][MAX_TASK];
ll taskCount[MAX_ENDPOINT];
vector<ll> taskDependencies[MAX_ENDPOINT][MAX_TASK];

ll calcRuntimeEndpoint(ll endpointNum);

ll calcRuntimeTask(ll endpointNum, ll taskNum) {
    if (taskRuntimeCache[endpointNum][taskNum] != -1) {
        return taskRuntimeCache[endpointNum][taskNum];
    }
    
    ll runtime = 0;

    vector<ll> &instructionDependencies = taskDependencies[endpointNum][taskNum];
    for(auto dep: instructionDependencies) {
        runtime = max(runtime, calcRuntimeTask(endpointNum, dep));
    }

    pii instruction = endpointInstructions[endpointNum][taskNum];
    if (instruction.first == 0) {
        runtime += instruction.second;
    } else {
        runtime += calcRuntimeEndpoint(instruction.second) + 1;
    }
    runtime %= MOD;

    dbgp("CRT " << endpointNum << " " << taskNum << " DPC " << instructionDependencies.size() << " " << runtime);

    taskRuntimeCache[endpointNum][taskNum] = runtime;
    return runtime;
}

ll calcRuntimeEndpoint(ll endpointNum) {
    if (endpointRuntimeCache[endpointNum] != -1) {
        return endpointRuntimeCache[endpointNum];
    }

    ll runtime = 0;

    ll tc = taskCount[endpointNum]; 
    REP(i, tc) {
        runtime = max(runtime, calcRuntimeTask(endpointNum, i));
    }
    runtime %= MOD;

    dbgp("CRE " << endpointNum << " " << runtime);
    endpointRuntimeCache[endpointNum] = runtime;
    return runtime;
}

int main(){
    std::ios_base::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
        dbgp("m is " << m);

    memset(endpointRuntimeCache, -1, sizeof(endpointRuntimeCache));
    memset(taskRuntimeCache, -1, sizeof(taskRuntimeCache));
    memset(endpointInstructions, 0, sizeof(endpointInstructions));
    memset(taskCount, 0, sizeof(taskCount));

    REP(i, n) {
        int tn;
        cin >> tn;

        taskCount[i] = tn;

        REP(ii, tn) {
            vector<ll> deps;
            ll dc;
            cin >> dc;
            REP(i, dc) {
                ll dep;
                cin >> dep;
                dep--;
                deps.push_back(dep);
            }

            taskDependencies[i][ii] = deps;

            pii instruction;
            cin >> instruction.first >> instruction.second;
            if (instruction.first == 1) {
                instruction.second--;
            }
            endpointInstructions[i][ii] = instruction;
        }
    }

    dbgp("running");

    REP(i, m) {
        int q;
        cin >> q;
        q--;

        cout << calcRuntimeEndpoint(q) << endl;
    }
}
