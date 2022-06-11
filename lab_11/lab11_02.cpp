#include <iostream>

using namespace std;

template<class T>
struct binaryfindByIdNode {
    T value;
    binaryfindByIdNode<T> *left;
    binaryfindByIdNode<T> *right;
    int index;

    binaryfindByIdNode(const T &thevalue) {
        value = thevalue;
        left = NULL;
        right = NULL;
        index = 0;
    }

    binaryfindByIdNode(const T &thevalue, binaryfindByIdNode<T> *theLeft, binaryfindByIdNode<T> *theRight,
                       int LeftTreeSize) {
        value = thevalue;
        left = theLeft;
        right = theRight;
        index = LeftTreeSize;
    }
};

template<class T>
class bianryfindByIdTree {
public:
    bianryfindByIdTree() {
        root = NULL;
        size = 0;
    }

    int insert(const T &thevalue);

    int erase(const T &thevalue);

    int deleteById(int a);

    int find(const T &thevalue);

    int findById(int a);

private:
    binaryfindByIdNode<T> *root;
    int size;
};

template<class T>
int bianryfindByIdTree<T>::insert(const T &thevalue) {
    binaryfindByIdNode<T> *p = root;
    binaryfindByIdNode<T> *pp = NULL;
    int sum = 0;
    while (p != NULL) {
        if (p->value < thevalue) {
            sum ^= p->value;
            pp = p;
            p = p->right;
        } else if (p->value > thevalue) {
            sum ^= p->value;
            pp = p;
            p = p->left;
        } else if (p->value == thevalue) {
            return 0;
        }
    }
    binaryfindByIdNode<T> *newNode = new binaryfindByIdNode<T>(thevalue);
    if (pp != NULL) {
        if (thevalue > pp->value)
            pp->right = newNode;
        else if (thevalue < pp->value)
            pp->left = newNode;
    } else {
        root = newNode;
    }
    size++;
    p = root;
    while (p->value != thevalue) {
        if (p->value < thevalue) {
            p = p->right;
        } else if (p->value > thevalue) {
            p->index++;
            p = p->left;
        }
    }
    return sum;
}

template<class T>
int bianryfindByIdTree<T>::erase(const T &thevalue) {
    binaryfindByIdNode<T> *p = root;
    binaryfindByIdNode<T> *pp = NULL;
    int sum = 0;
    while (p != NULL && p->value != thevalue) {
        sum ^= p->value;
        pp = p;
        if (p->value < thevalue) {
            p = p->right;
        } else if (p->value > thevalue) {
            p = p->left;
        }
    }
    if (p == NULL) {
        return 0;
    }
    sum ^= p->value;
    p = root;
    while (p != NULL && p->value != thevalue) {
        if (p->value < thevalue) {
            p = p->right;
        } else if (p->value > thevalue) {
            p->index--;
            p = p->left;
        }
    }

    if (p->left != NULL && p->right != NULL) {
        binaryfindByIdNode<T> *ps = p->right;
        binaryfindByIdNode<T> *s = p;
        while (ps->left != NULL) {
            ps->index--;
            s = ps;
            ps = ps->left;
        }

        binaryfindByIdNode<T> *newNode = new binaryfindByIdNode<T>(ps->value, p->left, p->right, p->index);
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

    binaryfindByIdNode<T> *c;
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
    size--;
    delete p;
    return sum;
}

template<class T>
int bianryfindByIdTree<T>::deleteById(int a) {
    binaryfindByIdNode<T> *p = root;
    binaryfindByIdNode<T> *pp = NULL;
    int sum = 0;
    while (p != NULL && p->index != a) {
        sum ^= p->value;
        pp = p;
        if (p->index > a) {
            p = p->left;
        } else if (p->index < a) {
            a = a - p->index - 1;
            p = p->right;
        }
    }
    if (p == NULL)
        return 0;
    sum ^= p->value;
    int thevalue = p->value;
    p = root;
    while (p != NULL && p->value != thevalue) {
        if (p->value < thevalue) {
            p = p->right;
        } else if (p->value > thevalue) {
            p->index--;
            p = p->left;
        }
    }

    if (p->left != NULL && p->right != NULL) {
        binaryfindByIdNode<T> *ps = p->right;
        binaryfindByIdNode<T> *s = p;
        while (ps->left != NULL) {
            ps->index--;
            s = ps;
            ps = ps->left;
        }

        binaryfindByIdNode<T> *newNode = new binaryfindByIdNode<T>(ps->value, p->left, p->right, p->index);
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

    binaryfindByIdNode<T> *c;
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
    size--;
    delete p;
    return sum;
}

template<class T>
int bianryfindByIdTree<T>::find(const T &thevalue) {
    binaryfindByIdNode<T> *p = root;
    int sum = 0;
    while (p != NULL && p->value != thevalue) {
        sum ^= p->value;
        if (p->value > thevalue) {
            p = p->left;
        } else if (p->value < thevalue) {
            p = p->right;
        }
    }
    if (p == NULL)
        return 0;
    else {
        sum ^= p->value;
        return sum;
    }
}

template<class T>
int bianryfindByIdTree<T>::findById(int a) {
    binaryfindByIdNode<T> *p = root;
    int sum = 0;
    while (p != NULL && p->index != a) {
        sum ^= p->value;
        if (p->index > a) {
            p = p->left;
        } else if (p->index < a) {
            a = a - p->index - 1;
            p = p->right;
        }
    }
    if (p == NULL)
        return 0;
    else {
        sum ^= p->value;
        return sum;
    }
}

int main() {
    bianryfindByIdTree<int> x;
    int m, a, b;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        if (a == 0) {
            cout << x.insert(b) << endl;
        }
        if (a == 1) {
            cout << x.find(b) << endl;
        }
        if (a == 2) {
            cout << x.erase(b) << endl;
        }
        if (a == 3) {
            b = b - 1;
            cout << x.findById(b) << endl;
        }
        if (a == 4) {
            b = b - 1;
            cout << x.deleteById(b) << endl;
        }
    }
}

