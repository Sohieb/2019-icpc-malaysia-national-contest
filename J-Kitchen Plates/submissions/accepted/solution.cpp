#include <bits/stdc++.h>
using namespace std;
string s,ans;
int in[5];
vector<int>g[5];
int main(){
	for(int i = 0;i < 5;i++){
		cin >> s;
		if(s[1] == '>')swap(s[0],s[2]);
		g[s[0] - 'A'].push_back(s[2] - 'A');
		in[s[2] - 'A']++;
	}
	queue<int>q;
	for(int i = 0;i < 5;i++)if(!in[i])q.push(i);
	while(!q.empty()){
		int x = q.front();
		q.pop();
		ans+=x + 'A';
		for(auto i : g[x])
			if(!--in[i])
				q.push(i);
	}
	puts(ans.size() == 5 ? ans.c_str() : "impossible");
}