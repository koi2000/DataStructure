//
// Created by DELL on 2021/11/8.
//
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n;
template<class T>
class treeNode {
public:
    treeNode(T value) {
        this->value = value;
        left = NULL;
        right = NULL;
    }

    treeNode(treeNode<T> *left, treeNode<T> *right, T value) : left(left), right(right), value(value) {};
    treeNode *left;
    treeNode *right;
    T value;

    bool operator < (treeNode<T>a){
        return this->value < a.value;
    }
};

template<class T>
class binaryTree {
public:
private:
    treeNode<T> *root;
    int size;

    void levelOrder(treeNode<T> *node);

    int height(treeNode<T> *node);

    int count(treeNode<T> *node);

    void numOrder(treeNode<T> *node ,int type);

public:
    binaryTree() {
        root = NULL;
        size = 0;
    };

    binaryTree(treeNode<T> *root) {
        this->root = root;
    }

    void levelOrder() {
        this->levelOrder(this->root);
    };

    int height() {
        this->numOrder(this->root, 1);
    }

    int count() {
        this->numOrder(this->root, 2);
    }
};
template<class T>
struct cmp1{

    bool operator()(treeNode<T>* x,treeNode<T>* y)
    {
        return x->value>y->value;//小的优先级高 ,从小到大排
    }
};

template<class T>
void binaryTree<T>::numOrder(treeNode<T> *node,int type){
    queue<treeNode<T> *> q = queue<treeNode<T> *>();
    priority_queue<treeNode<T> *,vector<treeNode<T>*>,cmp1<T>>p;
    while (node != NULL) {
        //cout << node->value << " ";
        p.push(node);
        if (node->left != NULL) {
            q.push(node->left);
        }

        if (node->right != NULL) {
            q.push(node->right);
        }

        if (q.empty()) {
            break;
        }

        node = q.front();
        q.pop();
    }

    while (!p.empty()){
        auto node = p.top();
        if(type==1){

            cout<<height(p.top())<<" ";
            p.pop();
        } else{
            cout<<count(p.top())<<" ";
            p.pop();
        }
    }
    cout<<endl;
}

template<class T>
void binaryTree<T>::levelOrder(treeNode<T> *node) {
    queue<treeNode<T> *> q = queue<treeNode<T> *>();
    while (node != NULL) {
        cout << node->value << " ";

        if (node->left != NULL) {
            q.push(node->left);
        }

        if (node->right != NULL) {
            q.push(node->right);
        }

        if (q.empty()) {
            break;
        }

        node = q.front();
        q.pop();
    }
    cout << endl;
}

template<class T>
int binaryTree<T>::height(treeNode<T> *node) {
    if (node == nullptr) {
        return 0;
    }
    int hl = height(node->left);
    int hr = height(node->right);
    if (hl > hr) {
        return ++hl;
    } else {
        return ++hr;
    }
}

template<class T>
int binaryTree<T>::count(treeNode<T> *node) {
    queue<treeNode<int> *> q = queue<treeNode<int> *>();
    int cnt = 0;
    while (node != NULL) {

        if (node->left != NULL) {
            q.push(node->left);
            cnt++;
        }

        if (node->right != NULL) {
            q.push(node->right);
            cnt++;
        }

        if (q.empty()) {
            break;
        }

        node = q.front();
        q.pop();
    }
    return ++cnt;
}

int main() {
    cin >> n;
    int number = 0;
    treeNode<int> *root = new treeNode<int>(1);
    number++;
    //queue<treeNode<int> *> q = queue<treeNode<int> *>();
    priority_queue<treeNode<int> *,vector<treeNode<int>*>,cmp1<int>>q;
    q.push(root);
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        if (q.empty()) {
            break;
        }
        treeNode<int> *top = q.top();
        if (top->value == i) {
            q.pop();
        } else {
            continue;
        }

        if (x != -1) {
            treeNode<int> *node = new treeNode<int>(x);
            number++;
            top->left = node;
            q.push(top->left);
        }
        if (y != -1) {
            treeNode<int> *node = new treeNode<int>(y);
            number++;
            top->right = node;
            q.push(top->right);
        }
    }
    binaryTree<int> tree = binaryTree<int>(root);
    tree.levelOrder();
    tree.count();
    tree.height();
    return 0;
}