//
// Created by DELL on 2021/12/14.
//
#include <iostream>
#include <list>
#include <queue>
#include <algorithm>

using namespace std;

class edge {
public:
    int u, v, w;

    edge() {}

    edge(int u, int v, int w) : u(u), v(v), w(w) {}

    bool operator-(edge e) const {
        return this->w - e.w;
    }
};

bool operator<(edge a, edge b) {
    return a.w >= b.w;
}

bool cmp(edge e1, edge e2) {
    return e1.w < e2.w;
}

int father[1000001];

//并查集的查找，此处使用路径压缩
int find(int x) {
    if (x == father[x]) {
        return x;
    }
    father[x] = find(father[x]);
    return father[x];
}

//y为被merge的数
void merge(int x, int y) {
    int f1 = find(x);
    int f2 = find(y);
    if (f1 != f2) {
        father[f2] = f1;
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        father[i] = i;
    }
    //建立一个小根堆
    priority_queue<edge> q;
    vector<edge> arr;
    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        edge e = edge(u, v, w);
        q.push(e);
        arr.push_back(e);
    }
    /*
    chapter-2(arr.begin(),arr.end(),cmp);
    long long sum = 0;
    for(int i=0;i<arr.size();i++){
        int a = find(arr[i].u);
        int b = find(arr[i].v);
        if (a == b) {
            continue;
        }
        else {
            sum += arr[i].w;
            father[a] = b;
        }
    }
    cout<<sum<<endl;*/
    int num = m;
    int k = 0;
    long long sum = 0;
    while (k < n - 1 && num > 0) {
        edge top = q.top();
        q.pop();
        num--;
        //得到当前节点的出点和入点，分别查看他们的父节点，若父节点一致，则说明连接后会导致图联通
        int a = find(top.u);
        int b = find(top.v);
        if (a == b) {
            continue;
        } else {
            sum += top.w;
            //将这两个节点merge，使他们拥有相同的父亲
            merge(a, b);
            k++;
        }
    }
    cout << sum << endl;
    return 0;
}