#include <bits/stdc++.h>
using namespace std;
int main(){
    string s = "ABCDE";
    vector<string> ans ;
    ans.push_back(s);
    while(next_permutation(s.begin(),s.end())){
        ans.push_back(s);
    }
    string ar[5];
    for(int i=0;i<5;i++){
        cin >> ar[i];
    }
    for(int i=0;i<ans.size();i++){
        map<char,int> m ;
        for(int j=0;j<ans[i].size();j++){
            m[ans[i][j]] = j ;
        }
        bool flag = true ;
        for(int j=0;j<5;j++){
            if ( ar[j][1] == '>' && m[ar[j][0]] < m[ar[j][2]] ) {
                flag = false ;
                break;
            }
            if ( ar[j][1] == '<' && m[ar[j][0]] > m[ar[j][2]] ) {
                flag = false ;
                break;
            }
        }
        if ( flag ) {
            cout << ans[i] << endl;
            return 0;
        }
    }
    cout << "impossible" << endl;
    return 0 ;
}
