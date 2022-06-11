#include<iostream>

using namespace std;

template<class K, class V>
class pairNode {
public:
    K first;
    V second;
    pairNode<K, V> *next;

    pairNode(K fir, V sec) : first(fir), second(sec) {};
};

template<class K, class V>
class hashTable {
private:
    pairNode<K, V> **table;

    int hash(K key);

    int dSize;
    int divisor;
public:
    hashTable(int divisor);

    void search(K key);

    void insert(pairNode<K, V> kv);

    void erase(K key);
};

template<class K, class V>
int hashTable<K, V>::hash(K key) {
    //定义哈希函数，此处为求余
    return key % divisor;
}

template<class K, class V>
hashTable<K, V>::hashTable(int div) {
    divisor = div;
    dSize = 0;
    table = new pairNode<K, V> *[div];
    //数组初始化
    for (int i = 0; i < div; i++) {
        table[i] = NULL;
    }
}

template<class K, class V>
void hashTable<K, V>::search(K key) {
    int i = hash(key);
    //如果当前位置对应的链表为空，说明肯定不含该元素
    if (table[i] == nullptr) {
        cout << "Not Found" << endl;
    } else {
        //获得链表头节点
        pairNode<K, V> *firstPair = table[i];
        int cnt = 0;
        int flag = 0;
        //遍历链表，若找到元素则将flag置为1
        while (firstPair != NULL) {
            if (firstPair->first == key) {
                flag = 1;
            }
            firstPair = firstPair->next;
            cnt++;
        }
        //若flag为1，说明已找到
        if (flag == 1) {
            cout << cnt << endl;
        } else {
            cout << "Not Found" << endl;
        }
    }
}

template<class K, class V>
void hashTable<K, V>::insert(pairNode<K, V> kv) {
    int i = hash(kv.first);
    //若当前位置为空，则直接插入
    if (table[i] == nullptr) {
        table[i] = new pairNode<K, V>(kv.first, kv.second);
        table[i]->next = nullptr;
    } else {
        pairNode<K, V> *firstPair = table[i];
        int cnt = 0;
        int flag = 0;
        //遍历链表，查看有没有相同元素
        if (firstPair->first == kv.first) {
            cout << "Existed" << endl;
            return;
        } else {
            while (firstPair->next != NULL) {
                if (firstPair->first == kv.first) {
                    cout << "Existed" << endl;
                    flag = 1;
                    break;
                }
                firstPair = firstPair->next;
            }
            if (flag == 0) {
                firstPair->next = new pairNode<K, V>(kv.first, kv.second);
                firstPair->next->next = nullptr;
            }
        }
    }
}

template<class K, class V>
void hashTable<K, V>::erase(K key) {
    int i = hash(key);
    //如果链表为空，说明不存在
    if (table[i] == nullptr) {
        cout << "Delete Failed" << endl;
        return;
    } else {
        pairNode<K, V> *first = table[i];
        int cnt = 0;
        int flag = 0;
        //特判第一个即是待删除元素的情况
        if (first->first == key) {
            table[i] = first->next;
            flag = 2;
            first = first->next;
        } else {
            //遍历链表，找到待删除节点的前一个节点
            while (first != NULL && first->next != NULL) {
                if (first->next->first == key) {
                    flag = 1;
                    //直接删除该节点
                    first->next = first->next->next;
                    break;
                }
                first = first->next;
            }
        }
        //遍历链表，求出被删除后的长度
        first = table[i];
        while (first != NULL) {
            first = first->next;
            cnt++;
        }

        if (flag == 0) {
            cout << "Delete Failed" << endl;
        } else {
            cout << cnt << endl;
        }
    }
}

int main() {
    int D, m;
    cin >> D >> m;
    hashTable<int, int> tables = hashTable<int, int>(D);
    for (int i = 0; i < m; i++) {
        int opt;
        int x;
        cin >> opt;
        if (opt == 0) {
            cin >> x;
            pairNode<int, int> pair = pairNode<int, int>(x, 0);
            tables.insert(pair);
        }
        if (opt == 1) {
            cin >> x;
            tables.search(x);
        }
        if (opt == 2) {
            cin >> x;
            tables.erase(x);
        }
    }
    return 0;
}