//
// Created by DELL on 2021/11/30.
//
#include <iostream>
#include <list>
#include <queue>
#include <algorithm>
#include <vector>
#include <set>
#include <cstring>

using namespace std;

const int MAX = 100001;
vector<int> arr;
set<int> sets;
int dis[MAX];

class node {
public:
    int pos;
    int dis;

    node(int pos, int dis) : pos(pos), dis(dis) {}

    bool operator<(const node &a) const {
        return this->dis > a.dis;
    }
};

class edge {
public:
    int u, v, w;

    edge() {}

    edge(int u, int v, int w) : u(u), v(v), w(w) {}

    bool operator-(edge e) const {
        return this->v - e.v;
    }

    bool operator>(edge e) const {
        return this->v > e.v;
    }

    bool operator<(edge e) const {
        return this->v < e.v;
    }
};

bool cmp(edge e1, edge e2) {
    return e1.v > e2.v;
}

bool vis[1000010] = {false};

template<class T>
class graph {
private:
    int nodeSize;
    list<T> *head;
public:
    graph(int size);

    void addEdge(int u, int v, int w);

    void delEdge(int u, int v);

    void bfs(int n);

    void dfs(int n);

    void rdfs(int n);

    void dijkstra(int u, int n);
};

template<class T>
graph<T>::graph(int size) {
    nodeSize = size;
    head = new list<T>[size + 1];
    for (int i = 1; i < size + 1; i++) {
        head[i].resize(0);
    }
}

template<class T>
void graph<T>::addEdge(int u, int v, int w) {
    edge e = edge(u, v, w);
    //head[u].insert(head[u].begin(),e);
    //head[u].insert(0,e);
    head[u].push_back(e);
}

template<class T>
void graph<T>::delEdge(int u, int v) {
    //list<T>*temp = &head[u];
    for (auto it = head[u].begin(); it != head[u].end(); it++) {
        if (((*it).u) == u && ((*it).v == v)) {
            head[u].erase(it);
            break;
        }
    }
}

template<class T>
void graph<T>::bfs(int u) {
    queue<int> q = queue<int>();
    q.push(u);
    vis[u] = true;
    while (!q.empty()) {
        int s = q.front();
        list<T> list = head[s];
        //cout<<s<<" ";
        sets.insert(s);
        arr.push_back(s);
        q.pop();
        for (auto it = list.begin(); it != list.end(); it++) {
            if (!vis[(*it).v]) {
                q.push((*it).v);
                vis[(*it).v] = true;
                //cout<<(*it).v<<" ";
            }

        }
    }
}

template<class T>
void graph<T>::dfs(int u) {
    if (!vis[u]) {
        vis[u] = true;
        sets.insert(u);
        arr.push_back(u);
    }
    head[u].sort();
    for (auto it = head[u].begin(); it != head[u].end(); it++) {
        //vis数组标记该点是否被访问过
        int v = (*it).v;
        //若某一结点未被查看过，则dfs该节点
        if (!vis[v]) {
            vis[v] = true;
            arr.push_back(v);
            sets.insert(v);
            dfs(v);
        }
    }
}

int flag = 0;

template<class T>
void graph<T>::rdfs(int u) {
    if (flag == 1) {
        return;
    }
    if (!vis[u]) {
        vis[u] = true;
        if (sets.find(u) != sets.end()) {
            flag = 1;
        }
        sets.insert(u);
        arr.push_back(u);
    }
    head[u].sort();
    for (auto it = head[u].begin(); it != head[u].end(); it++) {
        //vis数组标记该点是否被访问过
        int v = (*it).v;
        //若某一结点未被查看过，则dfs该节点
        if (!vis[v]) {
            vis[v] = true;
            arr.push_back(v);
            sets.insert(v);
            dfs(v);
            if (flag == 1) {
                return;
            }
        }

    }
}

template<class T>
void graph<T>::dijkstra(int u, int n) {
    //重写了小于号的方法，默认建立大根堆，但由于重载方法，其实建立的是小根堆
    priority_queue<node> q;
    for (int i = 1; i <= n; ++i) {
        //初始的距离均为极大值
        dis[i] = MAX;
    }
    //到自身的距离为0
    dis[u] = 0;
    q.push(node(u, 0));
    while (!q.empty()) {
        //每次从堆中取出一个数，即为当前的位置
        node sign = q.top();
        q.pop();
        int x = sign.pos;
        //避免两次被取到形成环的情况
        if (vis[x]) continue;
        vis[x] = true;
        //遍历这个点所发出的所有的边
        for (auto it = head[x].begin(); it != head[x].end(); it++) {
            int y = (*it).v;
            //这里计算该点到任意一点的最小距离，若发现新的最小距离，则进行更新
            if (dis[y] > dis[x] + (*it).w) {
                dis[y] = dis[x] + (*it).w;
                //如果目前这个节点没有被走过，就把这个节点放入堆中
                if (!vis[y]) {
                    q.push(node(y, dis[y]));
                }
            }
        }
    }
}

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    graph<edge> g = graph<edge>(n);
    int opt, u, v;
    //此部分处理图的结构
    for (int i = 0; i < m; ++i) {
        cin >> opt >> u >> v;
        if (opt == 0) {
            g.addEdge(u, v, 1);
            g.addEdge(v, u, 1);
        } else {
            g.delEdge(u, v);
            g.delEdge(v, u);
        }
    }
    //此处求图的连通分量个数
    vector<int> mins;
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            g.dfs(i);
            int minus = MAX;
            for (auto k : sets) {
                minus = min(k, minus);
            }
            sets.clear();
            mins.push_back(minus);
        } else {
            continue;
        }
    }
    //使连通分量中最小值以升序输出
    sort(mins.begin(), mins.end());
    cout << mins.size() << endl;

    for (int j = 0; j < mins.size(); ++j) {
        cout << mins[j] << " ";
    }
    cout << endl;
    //将arr数组清楚
    arr.clear();
    memset(vis, false, sizeof(vis));
    //调用dfs方法
    g.dfs(s);
    //输出数组的大小，即为dfs的顺序
    cout << arr.size() << endl;
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    memset(vis, false, sizeof(vis));
    arr.clear();
    g.bfs(t);
    cout << arr.size() << endl;
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    memset(vis, false, sizeof(vis));
    g.dijkstra(s, n);
    if (dis[t] == MAX) {
        cout << -1 << endl;
    } else {
        cout << dis[t] << endl;
    }
    return 0;
}
