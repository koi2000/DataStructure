#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <map>
using namespace std;

template<class T>
void changeLength1D(T*& a, int oldLength, int newLength) {
    if (newLength < 0)
        throw std::runtime_error("New length must be >=0");

    T* temp = new T[newLength];
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

    void init(T* element, int size);

    void push(T& element);

    void pop();

    bool empty();

    T top();

    int size();
private:
    T* heap;
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
void minHeap<T>::push(T& element) {
    //由于位置0处元素不使用，故当插入元素后值等于长度时，说明需要扩展
    if (length == heapSize + 1) {
        changeLength1D(heap, length, 2 * length);
        length *= 2;
    }

    int currentNode = ++heapSize;

    //遍历其所有父节点，如果小于父节点，则与父节点进行交换
    while (currentNode != 1 && heap[currentNode / 2] > element) {
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
        if (child<heapSize && heap[child] > heap[child + 1]) {
            child++;
        }
        //如果最后一个节点小于当前子节点，则将其附在这里
        if (lastElement <= heap[child]) {
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
void minHeap<T>::init(T* element, int size) {
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
            if (child < heapSize && heap[child] > heap[child + 1]) {
                child++;
            }
            //当前节点小于子节点，说明他可以作为他们的父节点
            if (rootElement <= heap[child]) {
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
    }
    else {
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

int main() {
    string s;
    cin >> s;
    int len = s.length();
    map<char, int> maps;
    minHeap<int>heap;
    for (int i = 0; i < len; i++) {
        if (maps.find(s[i]) == maps.end()) {
            maps[s[i]] = 1;
        }
        else {
            maps[s[i]]++;
        }
    }
    for (map<char, int>::iterator it = maps.begin(); it != maps.end(); it++) {
        heap.push(it->second);
    }
    //无需建立霍夫曼树即可求出编码长度
    int flag = 0;
    while (heap.size() > 1) {
        int a, b, trans;
        //每次从小根堆弹出两个数
        a = heap.top();
        heap.pop();
        b = heap.top();
        heap.pop();
        //求得两数之和再次push进入小根堆中
        trans = a + b;
        //flag为最终霍夫曼编码的总长度，每次都加上弹出的两数的结果，即该字符的霍夫曼编码的长度有几位就加了几次
        flag += trans;
        heap.push(trans);
    }
    cout << flag << endl;
    return 0;
}

