//
// Created by DELL on 2021/11/23.
//

#include <iostream>
#include <vector>
using namespace std;

vector<int> RANK(0);

template<class T>
struct binarySearchTreeNode{
    T element;
    binarySearchTreeNode<T> *leftChild,*rightChild;
    binarySearchTreeNode() {leftChild = rightChild = NULL;}
    binarySearchTreeNode(const T& theElement):element(theElement) {
        leftChild = rightChild = NULL;
    }
    binarySearchTreeNode(const T& theElement,binarySearchTreeNode *theLeftChild,binarySearchTreeNode *theRightChild,int leftsize):element(theElement){
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }
};
template<class T>
class binarySearchTree{
public:
    binarySearchTree(){root=NULL;treeSize=0;}

    int find(const T& element) const;
    int insert(const T& element);
    int erase(const T& element);
//    int findbyindex(int index);
//    int deletebyindex(int index);
    void inOrder(binarySearchTreeNode<T>* t);
    binarySearchTreeNode<T> *top(){return root;}
private:
    binarySearchTreeNode<T>* root;
    int treeSize;
};
template<class T>
void binarySearchTree<T>::inOrder(binarySearchTreeNode<T> *t) {
    if (t!=NULL){
        inOrder(t->leftChild);
        RANK.push_back(t->element);
        inOrder(t->rightChild);
    }
}

template<class T>
int binarySearchTree<T>::find(const T &element) const {
    int result=0;
    result ^= element;
    binarySearchTreeNode<T>*p=root;
    while (p!=NULL){
        if(element<p->element) {
            result ^= p->element;
            p = p->leftChild;
        }
        else {
            if (element > p->element) {
                result ^= p->element;
                p = p->rightChild;
            } else {
                return result;
            }
        }
    }
    return 0;
}

template<class T>
int binarySearchTree<T>::insert(const T &element) {
    int result=0;
    binarySearchTreeNode<T>*p=root,*pp=NULL;
    while (p!=NULL) {
        pp = p;
        if (element < p->element) {
            result^=pp->element;
            p = p->leftChild;
        } else {
            if (element > p->element) {
                result ^= pp->element;
                p = p->rightChild;
            } else {
                return 0;
            }
        }
    }
    binarySearchTreeNode<T> *newNode=new binarySearchTreeNode<T>(element);
    if (root!=NULL) {
        if (element<pp->element) {
            pp->leftChild = newNode;
        }
        else {
            pp->rightChild = newNode;
        }
    }else
        root=newNode;
    treeSize++;
    return result;

//    p = root;
//    while (p->element != element)
//    {
//        if (p->element < element)
//        {
//            p = p->rightChild;
//        }
//        else if (p->element > element)
//        {
//            p->leftsize++;
//            p = p->leftChild;
//        }
//    }
}
template<class T>
int binarySearchTree<T>::erase(const T &element) {
    int result=0;
    result^=element;
    binarySearchTreeNode<T>*p=root,*pp=NULL;
    while (p!=NULL&&p->element!=element){
        pp=p;
        if (element<p->element) {
            result^=p->element;
            p = p->leftChild;
        }
        else {
            result^=p->element;
            p = p->rightChild;
        }
    }
    if (p==NULL) return 0;
    if (p->leftChild!=NULL&&p->rightChild!=NULL){
        binarySearchTreeNode<T>*s=p->rightChild,*ps=p;
        while (s->leftChild!=NULL){
            ps=s;
            s=s->leftChild;
        }
        p->element=s->element;
        binarySearchTreeNode<T>*q=new binarySearchTreeNode<T>(s->element,p->leftChild,p->rightChild,0);
        if (pp==NULL)
            root=q;
        else {
            if (p == pp->leftChild)
                pp->leftChild = q;
            else
                pp->rightChild = q;
        }
        if(ps==p)
            pp=q;
        else
            pp=ps;
//        delete p;
        p=s;
    }
    binarySearchTreeNode<T>*c;
    if (p->leftChild!=NULL)
        c=p->leftChild;
    else
        c=p->rightChild;
    if (p==root)
        root=c;
    else{
        if (p==pp->leftChild)
            pp->leftChild=c;
        else
            pp->rightChild=c;
    }
    treeSize--;
//    delete p;
    return result;
}


int main() {
    int m,a,b;
    cin >> m;
    binarySearchTree<int> SearchTree;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        if (a==0){
            RANK.clear();
            int result;
            result=SearchTree.insert(b);
            SearchTree.inOrder(SearchTree.top());
            if (result==0) RANK.pop_back();
            cout <<result << endl;
        }else if (a==1){
            RANK.clear();
            int result;
            result=SearchTree.find(b);
            SearchTree.inOrder(SearchTree.top());
            cout << result << endl;
        }else if (a==2){
            RANK.clear();
            int result;
            result=SearchTree.erase(b);
            SearchTree.inOrder(SearchTree.top());
            cout << result << endl;
        }else if (a==3){
            int result;
//            for (int j = 0; j < RANK.size(); ++j) {
//                cout << RANK[j] << " ";
//            }
            int element = RANK[b-1];
            result=SearchTree.find(element);
            cout <<result << endl;
        }else if (a==4){
            int result;
            int element = RANK[b-1];
            RANK.clear();
            result=SearchTree.erase(element);
            SearchTree.inOrder(SearchTree.top());
            cout <<result << endl;
        }
    }
    return 0;
}




//template <class T>
//int binarySearchTree<T>::findbyindex(int index)
//{
//    binarySearchTreeNode<T>* p = root;
//    int sum = 0;
//    while (p != NULL && p->leftsize != index)
//    {
//        sum ^= p->element;
//        if (p->leftsize > index)
//        {
//            p = p->leftChild;
//        }
//        else if (p->leftsize < index)
//        {
//            index = index - p->leftsize - 1;
//            p = p->rightChild;
//        }
//    }
//    if (p == NULL)
//        return 0;
//    else
//    {
//        sum ^= p->element;
//        return sum;
//    }
//}
//template<class T>
//int binarySearchTree<T>::deletebyindex(int index) {
//    {
//        binarySearchTreeNode<T>* p = root;
//        binarySearchTreeNode<T>* pp = NULL;
//        int sum = 0;
//        while (p != NULL && p->noteSize != index)
//        {
//            sum ^= p->element;
//            pp = p;
//            if (p->noteSize > index)
//            {
//                p = p->leftChild;
//            }
//            else if (p->noteSize < index)
//            {
//                index = index - p->noteSize - 1;
//                p = p->rightChild;
//            }
//        }
//        if (p == NULL)
//            return 0;
//        sum ^= p->element;
//        int theElement = p->element;
//        p = root;
//        while (p != NULL && p->element != theElement)
//        {
//            if (p->element < theElement)
//            {
//                p = p->rightChild;
//            }
//            else if (p->element > theElement)
//            {
//                p->noteSize--;
//                p = p->leftChild;
//            }
//        }
//
//        if (p->leftChild != NULL && p->rightChild != NULL)
//        {
//            binarySearchTreeNode<T>* ps = p->rightChild;
//            binarySearchTreeNode<T>* s = p;
//            while (ps->leftChild != NULL)
//            {
//                ps->noteSize--;
//                s = ps;
//                ps = ps->leftChild;
//            }
//
//            binarySearchTreeNode<T>* newNode = new binarySearchTreeNode<T>(ps->element, p->leftChild, p->rightChild, p->noteSize);
//            if (pp == NULL)
//                root = newNode;
//            else if (p == pp->leftChild)
//                pp->leftChild = newNode;
//            else
//                pp->rightChild = newNode;
//
//            if (s == p)
//                pp = newNode;
//            else
//                pp = s;
//
//            delete p;
//            p = ps;
//        }
//
//        binarySearchTreeNode<T>* c;
//        if (p->leftChild != NULL)
//            c = p->leftChild;
//        else
//            c = p->rightChild;
//
//        if (p == root)
//            root = c;
//        else
//        {
//            if (p == pp->leftChild)
//                pp->leftChild = c;
//            else
//                pp->rightChild = c;
//        }
//        treeSize--;
//        delete p;
//        return sum;
//    }
//}