//
// Created by DELL on 2021/11/30.
//

#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#define MNum 100003					//最大顶点数;

using namespace std;

bool vist[MNum];					//顶点标记数组;
int ff=0;

typedef struct ANode {			//定义边结点;
    int adv;						//该边所指向的顶点的位置;
    struct ANode* next;		//指向下一条边的指针;
    int weight;						//和该边相关的信息,存放权值的地方;
}ArcNode;

typedef struct VNode {				//定义表头结点;
    ANode* firstNode;				//指向第一条依附于该表头的指针;
    int element;						//存放定点信息;
}AdVList;

typedef struct ALGraph {			//邻接表;
    AdVList VLise[MNum];				//创建有MNum个结点的图;
    int Vnum, Anum;				//图的定点数和边数;
};

class Graph {
public:
    int find(int x);
    Graph(int n=100) {
        G.Vnum = n;
        for (int i = 0; i < n; i++)
        {
            G.VLise[i].element = i+1;
            G.VLise[i].firstNode = NULL;
        }
    }
    void insert(int v1, int v2);
    void insert2(int v1, int v2);
    void erase(int v1, int v2);
    void print();
    void bfs(int n);
    void dfs(int n);
    void fdfs(int n);
    void components(int n);
    void dfsCounter(int n);
    void path(int s, int t);
    void path2(int x, int y);
    void everyComponents(int n);
protected:
    ALGraph G;
};

int Graph::find(int x)
{
    for (int i = 0; i < G.Vnum; i++)
    {
        if (x == G.VLise[i].element)
            return i;
    }
}

void Graph::insert2(int v1, int v2) {
    int j, k;
    j = v1 - 1;
    k = v2 - 1;

    ANode* p1 = new ANode;
    ANode* p2 = new ANode;

    p1->adv = k;
    ANode* p= G.VLise[j].firstNode;
    ANode* pp = NULL;
    if (p==NULL||p->adv > k) {
        p1->next = G.VLise[j].firstNode;
        G.VLise[j].firstNode = p1;
    }
    else {
        while (p&&p->adv < k) {
            pp = p;
            p = p->next;
        }
        if (!p) {
            pp->next = p1;
            p1->next = NULL;
        }
        else {
            p1->next = pp->next;
            pp->next = p1;
        }
    }

    ANode* q1 = new ANode;
    ANode* q2 = new ANode;

    q1->adv = j;
    ANode* q = G.VLise[k].firstNode;
    ANode* qq = NULL;
    if (q==NULL||q->adv > j) {
        q1->next = G.VLise[k].firstNode;
        G.VLise[k].firstNode = q1;
    }
    else {
        while (q && q->adv < j) {
            qq = q;
            q = q->next;
        }
        if (!q) {
            qq->next = q1;
            q1->next = NULL;
        }
        else {
            q1->next = qq->next;
            qq->next = q1;
        }
    }
    G.Anum++;
}

void Graph::insert(int v1, int v2) {
    int j, k;
    j = v1-1;						//找到v1在图中的位置;
    k = v2-1;						//找到v2在图中的位置;

    ANode* p1 = new ANode;				//新建一个边表结点*p1;
    ANode* p2 = new ANode;				//新建一个边表结点*p1;

    p1->adv = k;							//p1邻接点的序号为k;
    p1->next = G.VLise[j].firstNode;
    G.VLise[j].firstNode = p1;					//将新结点*p1插入顶点j的边表头部;

    p2->adv = j;							//p1邻接点的序号为j;
    p2->next = G.VLise[k].firstNode;
    G.VLise[k].firstNode = p2;					//将新结点*p2插入顶点k的边表头部;

    G.Anum++;
}

void Graph::erase(int v1, int v2) {
    v1 = v1 - 1;
    v2 = v2 - 1;

    ANode *current = G.VLise[v2].firstNode;
    ANode *trail = NULL;
    while (current != NULL && current->adv != v1) {
        trail = current;
        current = current->next;
    }
    if (current == NULL) {
        cout << "none" << endl;
        return;
    }

    if (trail != NULL)
        trail->next = current->next;
    else
        G.VLise[v2].firstNode = current->next;
    delete current;


    ANode* current2 = G.VLise[v1].firstNode;
    ANode* trail2 = NULL;
    while (current2 != NULL && current2->adv != v2) {
        trail2 = current2;
        current2 = current2->next;
    }
    if (current2 == NULL) {
        cout << "none" << endl;
        return;
    }

    if (trail2 != NULL)
        trail2->next = current2->next;
    else
        G.VLise[v1].firstNode = current2->next;
    delete current2;

    G.Anum--;
}

void Graph::print()
{
    cout<<"---------------"<<endl;
    for (int i = 0; i < G.Vnum; i++)
    {
        cout << G.VLise[i].element;
        ANode* p = G.VLise[i].firstNode;
        while (p)
        {
            cout << " -> " << G.VLise[p->adv].element;
            p = p->next;
        }
        cout << endl;
    }
}

void Graph::dfs(int n)
{
    cout << G.VLise[n].element;
    vist[n] = false;
    ANode* p = G.VLise[n].firstNode;
    while (p)
    {
        if (vist[p->adv]) {
            cout << " ";
            dfs(p->adv);
        }
        p = p->next;
    }
}



void Graph::fdfs(int n)
{
    vist[n] = false;
    ANode* p = G.VLise[n].firstNode;
    while (p)
    {
        if (vist[p->adv]) {
            fdfs(p->adv);
        }
        p = p->next;
    }
}

void Graph::dfsCounter(int n)
{
    vist[n] = false;
    ANode* p = G.VLise[n].firstNode;
    ff++;
    while (p)
    {
        if (vist[p->adv]) {
            dfsCounter(p->adv);
        }
        p = p->next;
    }
}

void Graph::bfs(int n)
{
    queue<int> q;
    q.push(n);
    while (!q.empty())
    {
        cout << G.VLise[q.front()].element << " ";
        vist[q.front()] = false;
        ANode* p = G.VLise[q.front()].firstNode;
        while (p)
        {
            if (vist[p->adv]) {
                vist[p->adv] = false;
                q.push(p->adv);
            }
            p = p->next;
        }
        q.pop();
    }
    cout << endl;
}

void Graph::components(int n) {
    memset(vist, true, sizeof(vist));
    int i,flag=0;
    for (i = 0; i < n; i++) {
        if (vist[i] == true) {
            fdfs(i);
            flag++;
        }
    }
    cout <<flag<<endl;
    memset(vist, true, sizeof(vist));
}

void Graph::everyComponents(int n) {
    memset(vist, true, sizeof(vist));
    int i;
    for (i = 0; i < n; i++) {
        if (vist[i] == true) {
            cout << i + 1 << " ";
            fdfs(i);
        }
    }
    memset(vist, true, sizeof(vist));
}

void Graph::path2(int x, int y) {
    queue<int> q;
    int num = G.Vnum + 1;
    q.push(x);
    vist[q.front()] = false;
    int path[num];
    for (int i = 0; i < num; i++)
        path[i] = 0;
    while (!q.empty())
    {
        int w = q.front();
        q.pop();
        ANode* p = G.VLise[w].firstNode;
        while (p != NULL)
        {
            if (vist[p->adv])
            {
                if (p->adv == y)
                {
                    cout << path[w] + 1 << endl;
                    return;
                }
                path[p->adv] = path[w] + 1;
                q.push(p->adv);
                vist[p->adv] = false;
            }
            p = p->next;
        }
    }
    cout << "-1" << endl;

}

void Graph::path(int s, int t) {

    if (s == t) {
        cout << 0 << endl;
        return;
    }

    int level = 0;
    int tail = s;
    queue<int> q;
    q.push(s);

    while (!q.empty())
    {
        if (q.front() == tail) {
            level++;
        }
//		cout << G.VLise[q.front()].element << " ";
        vist[q.front()] = false;
        ANode* p = G.VLise[q.front()].firstNode;
        while (p)
        {
            if (vist[p->adv]) {
                vist[p->adv] = false;
                if (p->adv == t) {
                    if (q.front()!=tail) level++;
                    cout << level << endl;
                    return;
                }
                q.push(p->adv);
                if (!p->next) tail = p->adv;
            }
            p = p->next;
        }
        q.pop();
    }

    cout << -1 << endl;
}

int main()
{
    int n,s,t;
    int m;
    cin >> n >> m>>s>>t;
    Graph A(n);
    for (int i = 0; i < m; i++) {
        int op;
        cin >> op;
        if (op == 0) {
            int v1, v2;
            cin >> v1 >> v2;
            A.insert2(v1, v2);
        }
        if (op == 1) {
            int v1, v2;
            cin >> v1 >> v2;
            A.erase(v1, v2);
        }
        if (op == 3) {
            A.print();
        }
        if (op == 4) {//第一行输出图中有多少个连通分量
            A.components(n);
        }
        if (op == 5) {//第二行输出所有连通子图中最小点的编号（升序），编号间用空格分隔
            A.everyComponents(n);
            cout << endl;
        }
        if (op == 6) {//第三行输出从s点开始的dfs序列长度
            memset(vist, true, sizeof(vist));
            A.dfsCounter(s - 1);
            cout << ff<<endl;
            ff = 0;
        }
        if (op == 7) {//第四行输出从s点开始的字典序最小的dfs序列
            memset(vist, true, sizeof(vist));
            A.dfs(s - 1);
            cout << endl;
        }
        if (op == 8) {//第五行输出从t点开始的bfs序列的长度
            memset(vist, true, sizeof(vist));
            A.dfsCounter(t - 1);
            cout << ff << endl;
            ff = 0;
        }
        if (op == 9) {//第六行输出从t点开始字典序最小的bfs序列
            memset(vist, true, sizeof(vist));	//初始化标记数组;
            A.bfs(t - 1);
        }
        if (op == 10) {//第七行输出从s点到t点的最短路径，若是不存在路径则输出-1
            memset(vist, true, sizeof(vist));
            A.path(s - 1, t - 1);
        }

    }
    A.components(n);

    A.everyComponents(n);
    cout << endl;

    A.dfsCounter(s - 1);
    cout << ff << endl;
    ff = 0;

    memset(vist, true, sizeof(vist));
    A.dfs(s - 1);
    cout << endl;

    memset(vist, true, sizeof(vist));
    A.dfsCounter(t - 1);
    cout << ff << endl;
    ff = 0;

    memset(vist, true, sizeof(vist));
    A.bfs(t - 1);

    memset(vist, true, sizeof(vist));
    A.path2(s - 1, t - 1);

    return 0;
}


