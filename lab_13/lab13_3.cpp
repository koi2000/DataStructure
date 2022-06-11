#include <iostream>
#include <list>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;
int father[1000001];
//并查集中的find
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

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {
        return;
    } else {
        father[y] = x;
    }
}

//创建一个节点类，存储所有可到达节点的信息
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
        return this->w - e.w;
    }
};

bool operator<(edge a, edge b) {
    return a.w >= b.w;
}

template<class T>
class graph {
private:
    int nodeSize;
    list<T> *head;
public:
    graph(int size);

    void addEdge(int u, int v, int w);

    void delEdge(int u, int v);

    void prim();
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
    head[u].push_back(e);
}

template<class T>
void graph<T>::delEdge(int u, int v) {
    for (auto it = head[u].begin(); it != head[u].end(); it++) {
        if (((*it).u) == u && ((*it).v == v)) {
            head[u].erase(it);
            break;
        }
    }
}

template<class T>
void graph<T>::prim() {
    //创建一个set，存储当前已存储的点
    set<int> nodes;
    nodes.insert(1);
    //创建一个队列，存储最新加入的点
    queue<int> queue;
    queue.push(1);
    int k = 0;
    int n = this->nodeSize;
    long long sum = 0;
    //创建一个小根堆，存储当前所有可用的边
    priority_queue<node> qq;
    while (k < n - 1) {
        //得到最新加入的点
        int x = queue.front();
        queue.pop();
        //将最新的可用的边接入小根堆中
        for (auto it = head[x].begin(); it != head[x].end(); it++) {
            if (nodes.find((*it).v) != nodes.end()) {
                continue;
            }
            qq.push(node((*it).v, (*it).w));
        }

        //每次从小根堆中取出一条边接入其中，但要保障不会成为连通图
        while (!qq.empty()) {
            node tt = qq.top();
            int a = find(1);
            int b = find(tt.pos);
            //若两点的父节点相同，说明其被加入后会导致图联通
            if (a == b) {
                qq.pop();
                continue;
            } else {
                //之后将其联通
                merge(1, qq.top().pos);
                sum += qq.top().dis;
                k++;
                //将最新的点加入队列
                queue.push(qq.top().pos);
                qq.pop();
                break;
            }
        }
    }
    cout << sum << endl;
}


int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        father[i] = i;
    }

    graph<edge> g = graph<edge>(n);

    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        edge e = edge(u, v, w);
        g.addEdge(v, u, w);
        g.addEdge(u, v, w);
    }
    g.prim();
    return 0;
}