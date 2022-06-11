#include<iostream>

using namespace std;

template<class K, class V>
class hashTable {
private:
    pair<K, V> **table;

    int hash(K key);
    int dSize;
    int length;
public:
    hashTable(int length);

    int search(K key);

    void insert(pair<K, V> kv);

    void erase(K key);
};

template<class K, class V>
int hashTable<K, V>::hash(K key) {
    //此处为将k转化为索引，这里使用的是求余函数
    return key % length;
}

template<class K, class V>
hashTable<K, V>::hashTable(int div) {
    this->length = div;
    dSize = 0;
    table = new pair<K, V> *[div];
    //将数据初始化为NULL
    for (int i = 0; i < div; i++) {
        table[i] = NULL;
    }
}

template<class K, class V>
int hashTable<K, V>::search(K key) {
    int i = hash(key);
    int j = i;
    do {
        //遍历整个数组，如果key相等则返回对应下标，否则返回-1
        if (table[j] != nullptr) {
            if (table[j]->first == key) {
                return j;
            }
        }
        j = (j + 1) % length;
    } while (j != i);
    return -1;
}

template<class K, class V>
void hashTable<K, V>::insert(pair<K, V> kv) {
    int is = search(kv.first);
    if (is != -1) {
        cout << "Existed" << endl;
        return;
    }

    int i = hash(kv.first);
    int j = i;
    //如果它对应的位置为空，则直接插入
    if (table[i] == nullptr) {
        table[i] = new pair<K, V>;
        table[i]->first = kv.first;
        table[i]->second = kv.second;
        cout << i << endl;
        dSize++;
    } else {
        while (table[j] != nullptr) {
            //若不为空且对应位置已有其他元素，则遍历寻找空位置进行插入
            j = (j + 1) % length;
            if (table[j] == nullptr) {
                table[j] = new pair<K, V>;
                table[j]->first = kv.first;
                table[j]->second = kv.second;
                cout << j << endl;
                dSize++;
                break;
            }
            //如果回到了原来的位置，则说明表已满
            if (j == i) {
                throw "hashTable is full";
            }
        }
    }
}

template<class K, class V>
void hashTable<K, V>::erase(K key) {
    //首先查找是否有key
    int is = search(key);
    if (is == -1) {
        cout << "Not Found" << endl;
        return;
    }
    //直接将对应的元素置为NULL
    table[is] = nullptr;
    int i = is;
    int j = (i + 1) % length;
    int cnt = 0;

    //指导下一个桶为空或者返回到初始位置为止
    while (table[j] != NULL && j != i) {
        //得到下一个元素的哈希值
        int k = hash(table[j]->first);
        //如果下一个元素的哈希值不等于下一个元素的位置并且，哈希值小于等于空元素的位置并且下一个元素
        //的位置大于空元素的位置
        //或者哈希大于当前元素位置（说明该元素是被挤到前面的），此时如果空元素的位置大于等于下一个元素的哈希，说明可以可以交换
        //或者空元素位置小于当下一个元素的位置
        if ((k != j) && (((k <= is) && (j > is)) || ((k > j) && ((is < j) || (is >= k))))) {
            table[is] = table[j];
            table[j] = NULL;
            is = j;
            cnt++;
        }
        j = (j + 1) % length;
    }
    cout << cnt << endl;//输出移动次数
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
            pair<int, int> pair = std::pair<int, int>(x, 0);
            tables.insert(pair);
        }
        if (opt == 1) {
            cin >> x;
            cout << tables.search(x) << endl;
        }
        if (opt == 2) {
            cin >> x;
            tables.erase(x);
        }
    }
    return 0;
}