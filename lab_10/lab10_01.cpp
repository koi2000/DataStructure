//
// Created by DELL on 2021/11/9.
//
#include <iostream>
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
        if (child < heapSize && heap[child] > heap[child + 1]) {
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
            if (child < heapSize && heap[child] > heap[child + 1]) {
                child++;
            }
            //当前节点小于子节点，说明他可以作为他们的父节点
            if (rootElement <= heap[child]) {
                break;
            }
            //否则继续向下移
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

int main() {
    int n;
    cin >> n;
    int arr[n + 1];
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    minHeap<int> heap;
    heap.init(arr, n);
    cout << heap.top() << endl;
    int m;
    cin >> m;
    int opt;
    for (int j = 0; j < m; j++) {
        cin >> opt;
        if (opt == 1) {
            int num;
            cin >> num;
            heap.push(num);
            cout << heap.top() << endl;
        }
        if (opt == 2) {
            heap.pop();
            cout << heap.top() << endl;
        }
        if (opt == 3) {
            int num;
            cin >> num;
            int waitSort[num + 1];
            for (int i = 1; i <= num; i++) {
                cin >> waitSort[i];
            }
            heap.init(waitSort, num);
            while (!heap.empty()) {
                cout << heap.top() << " ";
                heap.pop();
            }
        }
    }
    return 0;
}