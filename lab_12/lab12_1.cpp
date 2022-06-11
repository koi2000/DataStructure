//
// Created by DELL on 2021/11/29.
//
#include <iostream>
#include <queue>

using namespace std;
const int MAXN = 10010;
struct edge {
    int u, v, w, next;
} edges[MAXN];
int head[MAXN];
bool vis[MAXN] = {false};
int tot = 0;
int n;

void init(int n) {
    tot = 0;
    for (int i = 0; i < n; ++i) {
        head[i] = -1;
    }
}

void addEdge(int u, int v, int w) {
    edges[tot].u = u;
    edges[tot].v = v;
    edges[tot].w = w;
    edges[tot].next = head[u];
    head[u]=tot;
    tot++;
}

void delEdge(int u, int v) {
    //获得头节点
    int root = head[u];
    //若当前点未发出过边，直接break；
    if (root == -1) {
        return;
    }
    //若为头节点，直接break；
    if (edges[root].u == u && edges[root].v == v) {
        head[u] = edges[root].next;
    }
    //循环遍历，知道遍历到尾结点
    while (edges[root].next != -1) {
        int nxt = edges[root].next;
        if (edges[nxt].u == u && edges[nxt].v == v) {
            edges[root].next = edges[nxt].next;
            break;
        }
        root = edges[root].next;
    }
}

void dfs(int u) {
    /*
    int t = head[u];
    if(!vis[edges[t].u]){

    }*/

    for (int i = head[u]; i != -1; i = edges[i].next) {
        //vis数组标记该点是否被访问过
        if (!vis[edges[i].v]) {
            vis[edges[i].v] = true;
            //cout << edges[t].u << " " << edges[t].v << " " << edges[t].w << endl;
            cout<<edges[i].v<<endl;
            dfs(edges[i].v);
        }
    }
}

void bfs(int u) {
    queue<int> q = queue<int>();
    q.push(u);
    vis[u] = true;
    while (!q.empty()) {
        int s = q.front();
        int root = head[s];
        q.pop();
        cout<<edges[root].v<<endl;
        while (root!=-1){
            //int ku = edges[root].u;
            //int kv = edges[root].v;
            if (!vis[edges[root].v]) {
                q.push(edges[root].v);
                vis[edges[root].v] = true;
            }
            root = edges[root].next;
        }
    }
}

int main() {

    cin >> n;
    init(n);
    int d = 0;
    int u, v, w;
    for (int i = 0; i < n; i++) {

        cin >> u >> v >> w;
        addEdge(u, v, w);
        d = u;
    }
    cin>>u>>v>>w;
    delEdge(u,v);
    dfs(d);
    //bfs(d);
    return 0;
}

