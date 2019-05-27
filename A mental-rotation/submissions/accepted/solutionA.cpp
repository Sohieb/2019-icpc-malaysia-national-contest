#include <bits/stdc++.h>

using namespace std;

map<char, char> changes_to_right = {{'>','v'}, {'v','<'}, {'<','^'}, {'^','>'}, {'.','.'}};

vector<string> rotateRight(vector<string> grid){
    vector<string> temp (grid);
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[i].size();j++){
            temp[i][j] = changes_to_right[grid[grid.size()-j-1][i]];
        }
    }
    return temp;
}

int rightRotationCount(string rotations){
    int sum = 0, cnt = 0;
    for(int i=0;i<rotations.length();i++){
        sum += (rotations[i]=='R' ? 1:3);
    }
    return sum%4;
}

vector<string> solution(vector<string> grid, string rotations){
    int rCount = rightRotationCount(rotations);
    for(int j=0;j<rCount;j++){
        grid = rotateRight(grid);
    }
    return grid;
}

void printGrid(vector<string> grid){
    for(int i=0;i<grid.size();i++){
        cout<<grid[i]<<endl;
    }
}

int main(){
    int n;
    string rotations;
    cin>>n>>rotations;
    vector<string> grid;
    for(int i=0;i<n;i++){
        string line;
        cin>>line;
        grid.push_back(line);
    }
    grid = solution(grid, rotations);
    printGrid(grid);
    return 0;
}