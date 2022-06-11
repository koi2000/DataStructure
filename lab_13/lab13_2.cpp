#include <iostream>
#include <list>
#include <queue>
#include <algorithm>
using namespace std;
int father[1000001];

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
    //使用小根堆存储当前所有可到达的节点
    priority_queue<node>q;
    q.push(node(1,0));
    int k = 0;
    int n = this->nodeSize;
    long long sum = 0;
    while (k < n-1){
        node sign = q.top();
        q.pop();
        for (auto it = head[sign.pos].begin();it!=head[sign.pos].end();it++) {
            int a = find((*it).u);
            int b = find((*it).v);
            if (a == b) {
                continue;
            }
            else {
                //将这两个节点merge，使他们拥有相同的父亲
                merge(a, b);
                k++;
                sum++;
                q.push(node((*it).v,(*it).w));
            }
        }
    }
    cout<<sum<<endl;
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
        //向图中加入边
        g.addEdge(u, v, w);
    }
    g.prim();
    return 0;
}