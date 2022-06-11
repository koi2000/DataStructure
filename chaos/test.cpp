
#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <map>
#include <algorithm>
#include<list>
#include<vector>

using namespace std;


class pos {
public:
    int x;
    int y;

    pos(int x, int y) : x(x), y(y) {
    }
};

class Solution {

    bool bfs(vector<vector<char>> board, string word,int x,int y) {
        int m = board.size();
        int n = board[0].size();
        queue<pos> qq;
        bool vis[m][n];
        memset(vis, 0, sizeof(vis));
        vis[x][y]=true;
        pos p = pos(x, y);

        qq.push(p);

        int idx = 1;
        queue<pos>q;
        while(!q.empty()){
            while (!q.empty()){
                qq.push(q.front());
                q.pop();
            }
            int flag = 0;
            while (!qq.empty()) {
                pos temp = qq.front();
                qq.pop();
                if (temp.x + 1 < m &&vis[temp.x + 1][temp.y] == 0 &&  board[temp.x + 1][temp.y] == word[idx]) {
                    vis[temp.x + 1][temp.y] = 1;
                    p.x = temp.x + 1;
                    p.y = temp.y;
                    q.push(p);
                    flag = 1;
                }
                if (temp.y + 1 < n &&vis[temp.x][temp.y + 1] == 0 &&  board[temp.x][temp.y + 1] == word[idx]) {
                    vis[temp.x][temp.y + 1] = 1;
                    p.x = temp.x;
                    p.y = temp.y + 1;
                    q.push(p);
                    flag = 1;
                }
                if (temp.x - 1 >= 0 &&vis[temp.x - 1][temp.y] == 0 &&  board[temp.x - 1][temp.y] == word[idx]) {
                    vis[temp.x - 1][temp.y] = 1;
                    p.x = temp.x - 1;
                    p.y = temp.y;
                    q.push(p);
                    flag = 1;
                }
                if (temp.y - 1 >= 0 &&vis[temp.x][temp.y - 1] == 0 && board[temp.x][temp.y - 1] == word[idx]) {
                    vis[temp.x][temp.y - 1] = 1;
                    p.x = temp.x;
                    p.y = temp.y - 1;
                    q.push(p);
                    flag = 1;
                }
            }
            if(flag==1){
                idx++;
                if(idx==word.size()){
                    return true;
                }
            }else{
                return false;
            }

        }

        return false;
    }

public:
    bool exist(vector<vector<char>> &board, string word) {
        if(word.size()==1){
            return board[0][0]==word[0];
        }
        if(board.size()==1&&board[0].size()==1){
            if(word.size()!=1){
                return false;
            }else{
                return board[0][0]==word[0];
            }

        }
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[i].size();j++){
                if(board[i][j]==word[0]){
                    if(bfs(board,word,i,j)){
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

int main() {
    Solution s;
    int n, m;
    cin >> n >> m;
    vector<vector<char>> mat;
    for (int i = 0; i < n; ++i) {
        vector<char>a;
        mat.push_back(a);
    }
    /*for (int i = 0; i < mat.size(); ++i) {
        mat[i].resize(5);
    }*/

    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < m; ++j) {
            char t;
            cin >> t;
            mat[i].push_back(t);
            //cin >> mat[i][j];
        }
    }
    cout << s.exist(mat, "AAB");
    return 0;
}