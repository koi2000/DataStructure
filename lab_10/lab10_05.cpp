//
// Created by DELL on 2021/11/16.
//

#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

template<class T>
void changeLength1D(T *&a, int oldLength, int newLength) {
    if (newLength < 0)
        throw std::runtime_error("New length must be >=0");

    T *temp = new T[newLength];
    //取两个长度中较小作为后来数据的个数
    int number = std::min(oldLength, newLength);
    //将原数据迁移至新的数组中
    for (int i = 0; i < number; i++) {
        temp[i] = a[i];
    }
    //    delete[] a;
    a = temp;
}

template<class T>
class minHeap {
public:
    minHeap(int initLength = 10);

    void init(T *element, int size);

    void push(T &element);

    void pop();

    bool empty();

    T top();

    int size();

private:
    T *heap;
    int heapSize;
    int length;
};

template<class T>
minHeap<T>::minHeap(int initLength) {
    length = initLength;
    heapSize = 0;
    heap = new T[initLength];
}

template<class T>
void minHeap<T>::push(T &element) {
    //由于位置0处元素不使用，故当插入元素后值等于长度时，说明需要扩展
    if (length == heapSize + 1) {
        changeLength1D(heap, length, 2 * length);
        length *= 2;
    }

    int currentNode = ++heapSize;

    //遍历其所有父节点，如果小于父节点，则与父节点进行交换
    while (currentNode != 1 && heap[currentNode / 2]->weight > element->weight) {
        heap[currentNode] = heap[currentNode / 2];
        //上升到父辈
        currentNode /= 2;
    }

    heap[currentNode] = element;
}

template<class T>
void minHeap<T>::pop() {
    //heapSize--;
    /*if(heapSize==0){
        return;
    }*/
    //删除堆中最小元素

    heap[1].~T();

    T lastElement = heap[heapSize--];
    //设置当前节点为根节点
    int currentNode = 1;
    int child = 2;
    while (child <= heapSize) {
        //找到其子节点中较小的
        if (child < heapSize && heap[child]->weight > heap[child + 1]->weight) {
            child++;
        }
        //如果最后一个节点小于当前子节点，则将其附在这里
        if (lastElement->weight <= heap[child]->weight) {
            break;
        }
        //否则继续向下遍历
        heap[currentNode] = heap[child];
        currentNode = child;
        child *= 2;
    }
    heap[currentNode] = lastElement;

}

template<class T>
void minHeap<T>::init(T *element, int size) {
    //删除原堆
    //delete[] heap;
    heap = element;
    heapSize = size;
    length = size + 1;
    //从数组中间位置开始，即从最后一层,最后一个有孩子的节点，开始向前遍历

    for (int root = heapSize / 2; root >= 1; root--) {

        T rootElement = heap[root];
        //完全二叉树，他的孩子节点在他二倍处
        int child = 2 * root;

        while (child <= heapSize) {
            //选择兄弟之中较小者
            if (child < heapSize && heap[child]->weight > heap[child + 1]->weight) {
                child++;
            }
            //当前节点小于子节点，说明他可以作为他们的父节点
            if (rootElement->weight <= heap[child]->weight) {
                break;
            }
            //否则父节点异位
            heap[child / 2] = heap[child];
            child *= 2;
        }

        heap[child / 2] = rootElement;
    }

}

template<class T>
bool minHeap<T>::empty() {
    //如果heapSize为0则说明当前堆为空
    if (heapSize == 0) {
        return true;
    } else {
        return false;
    }
}

//返回堆顶元素即为返回第一个元素
template<class T>
T minHeap<T>::top() {
    return heap[1];
}

template<class T>
int minHeap<T>::size() {
    return heapSize;
}

//创建了一个霍夫曼节点类
template<class T>
class hTreeNode {
public:
    hTreeNode<T> *left;
    hTreeNode<T> *right;
    int weight;

    hTreeNode() {};

    bool operator>(hTreeNode<T> &a) {
        return this->weight < a.weight;
    }

    bool operator<=(hTreeNode<T> &a) {
        return this->weight >= a.weight;
    }
};

//创建一个层次遍历方法并记录每一个节点所在层级
template<class T>
int levelOrder(hTreeNode<T> *node) {
    //记录每一个节点的层级
    map<hTreeNode<T> *, int> levels;
    queue<hTreeNode<T> *> q = queue<hTreeNode<T> *>();
    int res = 0;
    levels[node] = 0;
    while (node != NULL) {
        if (node->left != NULL) {
            q.push(node->left);
            //子节点的层级为父节点的层级加一
            levels[node->left] = levels[node] + 1;
        }

        if (node->right != NULL) {
            q.push(node->right);
            levels[node->right] = levels[node] + 1;
        }

        if (q.empty()) {
            break;
        }

        node = q.front();
        q.pop();
    }
    //遍历map，只有叶子节点才为可以计算的节点
    for (auto it = levels.begin(); it != levels.end(); it++) {
        if (it->first->left == NULL && it->first->right == NULL) {
            res += (it->first->weight * it->second);
        }
    }
    return res;
}


int main() {
    string s;
    cin >> s;
    int len = s.length();
    map<char, int> maps;
    vector<int> weight;
    //求取字符频率
    for (int i = 0; i < len; i++) {
        if (maps.find(s[i]) == maps.end()) {
            maps[s[i]] = 1;
        } else {
            maps[s[i]]++;
        }
    }
    for (map<char, int>::iterator it = maps.begin(); it != maps.end(); it++) {
        weight.push_back(it->second);
    }
    sort(weight.begin(), weight.end());

    //这是一个存储霍夫曼树节点的最小堆，该堆中存储树
    minHeap<hTreeNode<int> *> heap;
    //为每个节点赋初值
    hTreeNode<int> **nodes = new hTreeNode<int> *[weight.size() + 1];
    for (int i = 1; i <= weight.size(); i++) {
        nodes[i] = new hTreeNode<int>();
        nodes[i]->weight = weight[i - 1];
        nodes[i]->left = NULL;
        nodes[i]->right = NULL;
    }
    hTreeNode<int> *a;
    hTreeNode<int> *b;
    hTreeNode<int> *temp;
    heap.init(nodes, weight.size());
    //一直遍历到只有一个节点
    while (heap.size() > 1) {
        temp = new hTreeNode<int>();
        //取得小根堆第一个元素
        a = heap.top();
        heap.pop();
        //取出第二个
        b = heap.top();
        heap.pop();
        //以上面两个树点创建一个新的树，左右孩子节点分别为上述两个树的根节点，当前根节点为原两节点之和
        temp->weight = a->weight + b->weight;
        temp->left = a;
        temp->right = b;
        //将新的树push进入小根堆
        heap.push(temp);
    }
    //经过上述步骤，小根堆中只剩下了一棵树，其为霍夫曼树
    auto top = heap.top();
    //将霍夫曼树经过一次自定义的层次遍历，即可得到结果
    cout << levelOrder(top);
    return 0;
}



