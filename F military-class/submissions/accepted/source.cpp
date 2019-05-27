#include <bits/stdc++.h>
using namespace std;
const int M = 1e9 + 7,N = 2001;
int dp[1<<9][N],n,e,k;
bool bad[N][N];
int fix(int a,int b){
	a^=1<<b;
	a<<=1;
	a++;
	return a;
}
void add(int &a,int b){
	a+=b;
	if(a >= M)a-=M;
}
int main(){
	scanf("%d%d%d",&n,&e,&k);
	for(int i = 0,a,b;i < k;i++){
		scanf("%d%d",&a,&b);
		bad[a - 1][b - 1] = 1;
	}
	dp[(1<<(e + 1)) - 1][0] = 1;
	for(int i = 0;i < n;i++)
		for(int j = 0;j < (1<<(2*e + 1));j++)
			if(dp[j][i]){
				if(j&(1<<(2*e))){
					if(i - e >= 0 && !bad[i][i - e])add(dp[fix(j,2*e)][i + 1],dp[j][i]);
					continue;
				}
				for(int k = 0;k < 2*e;k++)
					if(i - k + e < n && i - k + e >= 0 && (j&(1<<k)) && !bad[i][i - k + e])
						add(dp[fix(j,k)][i + 1],dp[j][i]);
			}
	printf("%d\n",dp[(1<<(e + 1)) - 1][n]);
}
