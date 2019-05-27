#include <bits/stdc++.h>
using namespace std;
const long long md = 100007 ;
map<long long,long long> ff ;
long long fun(long long a,long long &bprime){
    if ( a <= bprime ){
        return 1 ;
    }
    //if ( ff[a] ) return ff[a];
    long long ans = 0 ;
    for(int i=1;i<=bprime;i++){
        ans += fun(a-i,bprime) ;
    }
    //ff[a] = ans ;
    return ans ;
}

int main(){
    int n , m ;
    cin >> n >> m ;
    vector<long long> a(n,1);
    vector<long long> pa(n,0);
    vector<long long> b(n,1);
    vector<long long> pb(n,0);
    vector<long long> bprime(n,0);
    vector<long long> f(n,-1);
    vector<long long> x(n,0);
    while(m--){
        char x ;
        int h , l , r ;
        cin >> x >> l >> r >> h;
        l--,r--;
        if ( x == 'a' ){
            if ( l > r ){
                pa[l] += h ;
                pa[0] += h ;
                pa[min(r+1,n-1)] -= h ;
            }
            else{
                pa[l] += h ;
                pa[min(r+1,n-1)] -= h;
            }
        }
        else{
            if ( l > r ){
                pb[l] += h ;
                pb[0] += h ;
                pb[min(r+1,n-1)] -= h ;
            }
            else{
                pb[l] += h ;
                pb[min(r+1,n-1)] -= h;
            }
        }
    }
    for(int i=1;i<n;i++){
        pa[i] += pa[i-1] ;
    }
    for(int i=0;i<n;i++){
        pa[i] += 1 ;
    }
    for(int i=1;i<n;i++){
        pb[i] += pb[i-1] ;
    }
    for(int i=0;i<n;i++){
        pb[i] += 1 ;
    }
    for(int i=0;i<n;i++){
        bprime[i] = pb[i] % 7 ;
    }
    for(int i=0;i<n;i++){
        f[i] = fun(pa[i],bprime[i]);
    }
    for(int i=0;i<n;i++){
        x[i] = f[i] % md ;
    }
    long long total = 0 ;
    for(int i=0;i<n;i++){
        total += x[i];
    }
    cout << total << endl;
    return 0 ;
}
