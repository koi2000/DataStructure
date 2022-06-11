#include<iostream>
#include<vector>
#include<queue>
using namespace std;
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
};

treeNode<int>* create(vector<int>&pre, vector<int>&mid)
{
    if (pre.size() == 0 || mid.size() == 0){
        return nullptr;
    }
    //根据前序遍历得到根节点的值
    int rootvalue = pre[0];

    treeNode<int>* root = new treeNode<int>(rootvalue);
    int i = 0;
    //得到根节点在中序遍历中的位置，其前面为左子树，后面为右子树
    while (mid[i] != rootvalue){
        i++;
    }
    //得到二叉树左子树的中序遍历
    vector<int>lmid(mid.begin(), mid.begin() + i);
    //得到二叉树右子树的中序遍历
    vector<int>rmid(mid.begin() + i + 1, mid.end());
    //得到二叉树左子树的前序遍历
    vector<int>lpre(pre.begin() + 1, pre.begin() + i + 1);
    //得到二叉树的右子树的前序遍历
    vector<int>rpre(pre.begin() + i + 1, pre.end());
    //根据左子树的前序遍历和中序遍历创建左子树
    root->left = create(lpre, lmid);
    //根据右子树的前序遍历和中序遍历创建右子树
    root->right = create(rpre, rmid);
    //返回根节点
    return root;
}
//树的后序遍历
void postorder(treeNode<int>* root)
{
    if (root == NULL){
        return;
    }
    //遍历左子树
    postorder(root->left);
    //遍历右子树
    postorder(root->right);
    //输出根节点
    cout << root->value << " ";
}
int main()
{
    int n;
    cin>>n;
    int temp;
    vector<int>pre;
    vector<int>mid;
    for(int i=0;i<n;i++){
        cin>>temp;
        pre.push_back(temp);
    }
    for(int i=0;i<n;i++){
        cin>>temp;
        mid.push_back(temp);
    }
    queue<treeNode<int>*>q;
    //根据前序遍历和中序遍历得到树
    treeNode<int>* root=create(pre, mid);
    //后序遍历
    postorder(root);
    cout << endl;
    return 0;
}