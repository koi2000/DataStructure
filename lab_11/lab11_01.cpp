#include <iostream>

using namespace std;

template<class T>
class treeNode {
public:
    treeNode(treeNode<T> *left, treeNode<T> *right, int first, int second) : left(left), right(right) {
        this->value = pair<int, int>(first, second);
    }

    treeNode(T value) : value(value) {
        this->left = NULL;
        this->right = NULL;
    }

    treeNode<T> *left;
    treeNode<T> *right;
    T value;
};

template<class K, class V>
class bsTree {
private:
    treeNode<pair<K, V>> *root;
    int treeSize;
public:
    bsTree() {
        root = nullptr;
        treeSize = 0;
    }

    bsTree(treeNode<pair<K, V>> *value) {
        root = value;
        treeSize = 0;
    }

    int find(K key);

    void insert(K thePair);

    void erase(K key);

    int findById(int id);

    void deleteById(int id);

    int eraseById(int id);
};

template<class K, class V>
int bsTree<K, V>::find(K key) {
    int sum = 0;
    //复制根节点
    treeNode<pair<K, V>> *p = root;
    sum ^= key;
    while (p != nullptr) {
        if (key < p->value.first) {
            sum ^= p->value.first;
            p = p->left;
        } else if (key > p->value.first) {
            sum ^= p->value.first;
            p = p->right;
        } else {
            return sum;
            //cout << sum << endl;
        }
    }
    //cout << 0 << endl;
    return 0;
}

template<class K, class V>
void bsTree<K, V>::insert(K key) {
    treeNode<pair<K, V>> *p = root;
    treeNode<pair<K, V>> *pp = NULL;
    int sum = 0;
    //pp存储当前节点的父节点
    while (p != nullptr) {
        pp = p;
        if (key < p->value.first) {
            //如果需要移到他的左子树，则对他的index++
            sum ^= p->value.first;
            //p->value.second++;
            //thePair.second++;
            p = p->left;
        } else if (key > p->value.first) {
            sum ^= p->value.first;
            p = p->right;
        } else {
            cout << 0 << endl;
            return;
        }
    }

    treeNode<pair<K, V>> *node = new treeNode<pair<K, V>>(pair<K, V>(key, 0));
    //不在使用之前方法进行计算，而是再次遍历，进行计算
    if (root != nullptr) {
        //如果小于当前节点，则为左子树
        if (key < pp->value.first) {
            pp->left = node;
        } else {
            pp->right = node;
        }
    } else {
        root = node;
    }
    //插入结束后，开始遍历所有节点，若大于key，则说明新插入的节点在当前节点的前面，当前节点的index++
    p = root;
    while (p->value.first != key) {
        if (p->value.first < key) {
            p = p->right;
        } else if (p->value.first > key) {
            p->value.second++;
            p = p->left;
        }
    }
    cout << sum << endl;
}

template<class K, class V>
void bsTree<K, V>::erase(K key) {
    treeNode<pair<K, V>> *p = root,
            *pp = nullptr;
    int sum = 0;
    sum ^= key;
    //遍历，直接找到p节点
    while (p != nullptr && p->value.first != key) {
        pp = p;
        if (key < p->value.first) {
            //如果删除的树在其左子树，则对当前值--
            sum ^= p->value.first;
            //p->value.second--;
            p = p->left;
        } else {
            sum ^= p->value.first;
            p = p->right;
        }
    }
    if (p == nullptr) {
        cout << 0 << endl;
        return;
    } else {
        cout << sum << endl;
    }
    p = root;
    //次数为遍历更新每一个节点的左孩子数量
    while (p != NULL && p->value.first != key) {
        if (p->value.first < key) {
            p = p->right;
        } else if (p->value.first > key) {
            //如果节点元素大于key，说明该元素在其左子树，则他的左孩子数量减1
            p->value.second--;
            p = p->left;
        }
    }
    //存在两个孩子节点
    if (p->left != nullptr && p->right != nullptr) {
        //找到右子树中最小值
        treeNode<pair<K, V>> *s = p->right,
                *ps = p;
        while (s->left != nullptr) {
            s->value.second--;
            ps = s;
            s = s->left;
        }
        treeNode<pair<K, V>> *q = new treeNode<pair<K, V>>(p->left, p->right, s->value.first, p->value.second);
        //如果待删除节点为根节点的话
        if (pp == nullptr) {
            root = q;
        } else if (p == pp->left) {
            pp->left = q;
        } else {
            pp->right = q;
        }
        //若其左子树根节点直接为左子树最大值
        if (ps == p) {
            //让其父节点直接为左子树最大值，此时ps值为p，pp仍然为当前被删除位置后补节点的父节点
            pp = q;
        } else {
            pp = ps;
        }
        //直接赋值待删除节点为左子树最大值
        p = s;
    }
    //若只有一个节点
    treeNode<pair<K, V>> *c;
    if (p->left != NULL) {
        c = p->left;
    } else {
        c = p->right;
    }

    if (p == root) {
        root = c;
    } else {
        if (p == pp->left) {
            pp->left = c;
        } else {
            pp->right = c;
        }
    }
    delete p;
    treeSize--;
}

template<class K, class V>
int bsTree<K, V>::findById(int id) {
    treeNode<pair<K, V>> *p = root;
    int temp = id;
    int sum = 0;
    while (p != nullptr && p->value.second != temp) {
        if (temp < p->value.second) {
            sum ^= p->value.first;
            p = p->left;
        } else if (temp > p->value.second) {
            //如果当前还剩的索引大于当前节点的左孩子数量，则减去其左孩子数量和其本身
            //此时temp值变为在其右子树中的索引
            sum ^= p->value.first;
            temp = temp - (p->value.second + 1);
            /*if(temp==0){
                break;
            }*/
            p = p->right;
        }
    }
    if (p != nullptr) {
        sum ^= p->value.first;
        return sum;
    } else {
        //未有对应索引直接使结果为0，并且没有对应index
        return 0;
    }
}

template<class K, class V>
void bsTree<K, V>::deleteById(int id) {
    pair<int, int> *node = findById(id);
    if (node == nullptr) {
        cout << 0 << endl;
    } else {
        this->erase(node->second);
    }
}


template<class K, class V>
int bsTree<K, V>::eraseById(int a) {
    treeNode<pair<K, V>> *p = root;
    treeNode<pair<K, V>> *pp = NULL;
    int sum = 0;
    while (p != NULL && p->value.second != a) {
        sum ^= p->value.first;
        pp = p;
        if (p->value.second > a) {
            p = p->left;
        } else if (p->value.second < a) {
            //如果当前还剩的索引大于当前节点的左孩子数量，则减去其左孩子数量和其本身
            a = a - p->value.second - 1;
            p = p->right;
        }
    }
    if (p == NULL)
        return 0;
    sum ^= p->value.first;
    int theElement = p->value.first;
    //删除直接调用删除方法
    erase(theElement);
    return sum;
    /*p = root;
    while (p != NULL && p->value.first != theElement) {
        if (p->value.first < theElement) {
            p = p->right;
        } else if (p->value.first > theElement) {
            p->value.second--;
            p = p->left;
        }
    }

    if (p->left != NULL && p->right != NULL) {
        treeNode<pair<K,V>> *ps = p->right;
        treeNode<pair<K,V>> *s = p;
        while (ps->left != NULL) {
            ps->value.second--;
            s = ps;
            ps = ps->left;
        }

        treeNode<pair<K,V>> *newNode = new treeNode<pair<K,V>>( p->left, p->right,ps->value.first, p->value.second);
        if (pp == NULL)
            root = newNode;
        else if (p == pp->left)
            pp->left = newNode;
        else
            pp->right = newNode;

        if (s == p)
            pp = newNode;
        else
            pp = s;

        delete p;
        p = ps;
    }

    treeNode<pair<K,V>> *c;
    if (p->left != NULL)
        c = p->left;
    else
        c = p->right;

    if (p == root)
        root = c;
    else {
        if (p == pp->left)
            pp->left = c;
        else
            pp->right = c;
    }
    delete p;
    return sum;*/
}

int main() {
    int m;
    cin >> m;
    bsTree<int, int> bs = bsTree<int, int>();
    for (int i = 0; i < m; ++i) {
        int opt;
        cin >> opt;
        if (opt == 0) {
            int a;
            cin >> a;
            bs.insert(a);
        }
        if (opt == 1) {
            int a;
            cin >> a;
            cout << bs.find(a) << endl;
        }
        if (opt == 2) {
            int a;
            cin >> a;
            bs.erase(a);
        }
        if (opt == 3) {
            int a;
            cin >> a;
            //在树中存储的是从0开始
            a -= 1;
            cout << bs.findById(a) << endl;
        }
        if (opt == 4) {
            int a;
            cin >> a;
            a -= 1;
            bs.eraseById(a);
            //cout<<bs.eraseById(a)<<endl;
        }

    }
    return 0;
}
