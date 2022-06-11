//
// Created by DELL on 2021/11/8.
//
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
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

    treeNode(treeNode<T>* left, treeNode<T>* right, T value) : left(left), right(right), value(value) {};
    treeNode* left;
    treeNode* right;
    T value;

    bool operator < (treeNode<T>a) {
        return this->value < a.value;
    }
};

template<class T>
class binaryTree {
public:
private:
    treeNode<T>* root;
    int size;

    void levelOrder(treeNode<T>* node);

    int height(treeNode<T>* node);

    int count(treeNode<T>* node);

    void numOrder(treeNode<T>* node, int type);

public:
    binaryTree() {
        root = NULL;
        size = 0;
    };

    binaryTree(treeNode<T>* root) {
        this->root = root;
    }

    void levelOrder() {
        this->levelOrder(this->root);
    };

    int height() {
        //调用顺序遍历方法求每个节点高度
        this->numOrder(this->root, 1);
        return 0;
    }

    int count() {
        //调用顺序遍历方法求每个节点数量
        this->numOrder(this->root, 2);
        return 0;
    }
};
template<class T>
struct cmp1 {
    bool operator()(treeNode<T>* x, treeNode<T>* y) {
        return x->value > y->value;//小的优先级高 ,从小到大排
    }
};
template<class T >
bool cmp(treeNode<T>* x, treeNode<T>* y)
{
    return x->value < y->value;//小的优先级高 ,从小到大排
}

template<class T>
void binaryTree<T>::numOrder(treeNode<T>* node, int type) {
    //根据value值遍历
    queue<treeNode<T>*> q = queue<treeNode<T>*>();
    vector<treeNode<T>*>p;
    //首先遍历出所有的节点，并压入数组
    while (node != NULL) {
        p.push_back(node);
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
    //对数组按照value大小排序
    sort(p.begin(), p.end(),cmp<int>);
    //遍历数组，求每一个节点的高度或者数量
    while (!p.empty()) {
        auto node = *p.begin();
        if (type == 1) {
            cout << height(node) << " ";
            p.erase(p.begin());
        }
        else {
            cout << count(node) << " ";
            p.erase(p.begin());
        }
    }
    cout << endl;
}

//层次遍历
template<class T>
void binaryTree<T>::levelOrder(treeNode<T>* node) {
    queue<treeNode<T>*> q = queue<treeNode<T>*>();
    while (node != NULL) {
        //首先输出根节点
        cout << node->value << " ";

        //将左节点压入队列
        if (node->left != NULL) {
            q.push(node->left);
        }

        if (node->right != NULL) {
            q.push(node->right);
        }

        if (q.empty()) {
            break;
        }
        //得到新的根节点
        node = q.front();
        //删除根节点
        q.pop();
    }
    cout << endl;
}

//求以该节点为根的树的高度
template<class T>
int binaryTree<T>::height(treeNode<T>* node) {
    //递归遍历，遍历到为null的节点则返回0
    if (node == nullptr) {
        return 0;
    }
    //递归遍历左节点
    int hl = height(node->left);
    //递归遍历右节点
    int hr = height(node->right);
    //返回最大的高度
    if (hl > hr) {
        return ++hl;
    }
    else {
        return ++hr;
    }
}


//求以该节点为根的节点数量
template<class T>
int binaryTree<T>::count(treeNode<T>* node) {
    queue<treeNode<int>*> q = queue<treeNode<int>*>();
    int cnt = 0;
    while (node != NULL) {

        //左节点不为空，则push，并将数量++
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
        //获得新的首节点
        node = q.front();
        //删除首节点
        q.pop();
    }
    return ++cnt;
}

int main() {
    cin >> n;
    treeNode<int>* root = new treeNode<int>(1);
    //以数组加排序的方式模拟优先队列
    vector<treeNode<int>*>arr;
    //将根节点压入数组
    arr.push_back(root);
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        if (arr.empty()) {
            break;
        }
        //获得首节点
        treeNode<int>* top = *arr.begin();
        if (top->value == i) {
            //删除首节点
            arr.erase(arr.begin());
        }
        else {
            continue;
        }

        if (x != -1) {
            treeNode<int>* node = new treeNode<int>(x);
            top->left = node;
            //将新插入的节点压入队列
            arr.push_back(top->left);
        }
        if (y != -1) {
            treeNode<int>* node = new treeNode<int>(y);
            top->right = node;
            arr.push_back(top->right);
        }
        //对数组进行排序，保证小数在前，大数在后
        sort(arr.begin(), arr.end(),cmp<int>);
    }
    binaryTree<int> tree = binaryTree<int>(root);
    tree.levelOrder();
    tree.count();
    tree.height();
    return 0;
}