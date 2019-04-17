#ifndef _AVL_TREE_HPP_
#define _AVL_TREE_HPP_

#include <iomanip>
#include <iostream>
using namespace std;

template <class T, class  E>
class AVLTreeNode{
    public:
        T key;                // 关键字(键值)
        E value;
        int height,sz;         // 高度
        AVLTreeNode *left;    // 左孩子
        AVLTreeNode *right;    // 右孩子

        AVLTreeNode(T keys, E values, AVLTreeNode *l, AVLTreeNode *r):
            key(keys),value(values), height(0),sz(1),left(l),right(r) {}
};

template <class T, class  E>
class AVLTree {
    private:
        AVLTreeNode<T,E> *mRoot;    // 根结点

    public:
        AVLTree();
        ~AVLTree();

        // 获取树的高度
        int height();
        // 获取a,b中的较大值
        int max(int a, int b);

        // 前序遍历"AVL树"
        void preOrder();
        // 中序遍历"AVL树"
        void inOrder();
        // 后序遍历"AVL树"
        void postOrder();

        // merge 函数
        void merge(AVLTree<T,E>* z);
        void dfs(AVLTreeNode<T,E> * z);
        void dfs1(AVLTree<T,E>*x, AVLTreeNode<T,E>*y, T z);
        void split(AVLTree<T,E>*z, T x);
        // (递归实现)查找"AVL树"中键值为key的节点
        AVLTreeNode<T,E>* search(T key);
        // (非递归实现)查找"AVL树"中键值为key的节点
        AVLTreeNode<T,E>* notIterativeSearch(T key);

        // find index number
        AVLTreeNode<T,E>* indexsearch(int num);
        AVLTreeNode<T,E>* indexsearch(AVLTreeNode<T,E>* x, int num);

        // 查找最小结点：返回最小结点的键值。
        T minimum();
        // 查找最大结点：返回最大结点的键值。
        T maximum();

        // 将结点(key为节点键值)插入到AVL树中
        void insert(T key, E value);

        // 删除结点(key为节点键值)
        void remove(T key);

        // update size of node
        void push(AVLTreeNode<T,E>* tree);
        void push();

        // 销毁AVL树
        void destroy();

        // 打印AVL树
        void print();
    private:
        // 获取树的高度
        int height(AVLTreeNode<T,E>* tree) ;

        // 前序遍历"AVL树"
        void preOrder(AVLTreeNode<T,E>* tree) const;
        // 中序遍历"AVL树"
        void inOrder(AVLTreeNode<T,E>* tree) const;
        // 后序遍历"AVL树"
        void postOrder(AVLTreeNode<T,E>* tree) const;

        void pushup(AVLTreeNode<T,E>* tree) const;

        // (递归实现)查找"AVL树x"中键值为key的节点
        AVLTreeNode<T,E>* search(AVLTreeNode<T,E>* x, T key) const;
        // (非递归实现)查找"AVL树x"中键值为key的节点
        AVLTreeNode<T,E>* notIterativeSearch(AVLTreeNode<T,E>* x, T key) const;

        // 查找最小结点：返回tree为根结点的AVL树的最小结点。
        AVLTreeNode<T,E>* minimum(AVLTreeNode<T,E>* tree);
        // 查找最大结点：返回tree为根结点的AVL树的最大结点。
        AVLTreeNode<T,E>* maximum(AVLTreeNode<T,E>* tree);

        // LL：左左对应的情况(左单旋转)。
        AVLTreeNode<T,E>* leftLeftRotation(AVLTreeNode<T,E>* k2);

        // RR：右右对应的情况(右单旋转)。
        AVLTreeNode<T,E>* rightRightRotation(AVLTreeNode<T,E>* k1);

        // LR：左右对应的情况(左双旋转)。
        AVLTreeNode<T,E>* leftRightRotation(AVLTreeNode<T,E>* k3);

        // RL：右左对应的情况(右双旋转)。
        AVLTreeNode<T,E>* rightLeftRotation(AVLTreeNode<T,E>* k1);

        // 将结点(z)插入到AVL树(tree)中
        AVLTreeNode<T,E>* insert(AVLTreeNode<T,E>* &tree, T key, E value);

        // 删除AVL树(tree)中的结点(z)，并返回被删除的结点
        AVLTreeNode<T,E>* remove(AVLTreeNode<T,E>* &tree, AVLTreeNode<T,E>* z);

        // 销毁AVL树
        void destroy(AVLTreeNode<T,E>* &tree);

        // 打印AVL树
        void print(AVLTreeNode<T,E>* tree, T key, int direction);
};

/* 
 * 构造函数
 */
template <class T, class  E>
AVLTree<T,E>::AVLTree():mRoot(NULL)
{
}

/* 
 * 析构函数
 */
template <class T, class  E>
AVLTree<T,E>::~AVLTree() 
{
    destroy(mRoot);
}

/*
 * 获取树的高度
 */
template <class T, class  E>
int AVLTree<T,E>::height(AVLTreeNode<T,E>* tree) 
{
    if (tree != NULL)
        return tree->height;

    return 0;
}

template<class T, class  E>
void AVLTree<T,E>::pushup(AVLTreeNode<T,E>* tree)const {
    tree -> sz = 1;
    if (tree -> left != NULL) tree -> sz += tree -> left -> sz;
    if (tree -> right != NULL) tree -> sz += tree -> right -> sz;
}

template <class T, class  E>
int AVLTree<T,E>::height() 
{
    return height(mRoot);
}
/*
 * 比较两个值的大小
 */
template <class T, class  E>
int AVLTree<T,E>::max(int a, int b) 
{
    return a>b ? a : b;
}

// update size of node
template<class T, class  E>
void AVLTree<T,E>::push(AVLTreeNode<T,E>* tree){
    if (tree != NULL){
        push(tree -> left);
        push(tree -> right);
        pushup(tree);
    }
}

template<class T, class  E>
void AVLTree<T,E>::push(){
    push(mRoot);
}
/*
 * 前序遍历"AVL树"
 */
template <class T, class  E>
void AVLTree<T,E>::preOrder(AVLTreeNode<T,E>* tree) const
{
    if(tree != NULL)
    {
        cout<< tree->key << " " ;
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

template <class T, class  E>
void AVLTree<T,E>::preOrder() 
{
    preOrder(mRoot);
}

/*
 * 中序遍历"AVL树"
 */
template <class T, class  E>
void AVLTree<T,E>::inOrder(AVLTreeNode<T,E>* tree) const
{
    if(tree != NULL)
    {
        inOrder(tree->left);
        // cout<< tree->key << " " << tree->value<<" "<< tree->sz<<endl;
        cout<< tree -> key<<" ";
        inOrder(tree->right);
    }
}

template <class T, class  E>
void AVLTree<T,E>::inOrder() 
{
    inOrder(mRoot);
}

/*
 * 后序遍历"AVL树"
 */
template <class T, class  E>
void AVLTree<T,E>::postOrder(AVLTreeNode<T,E>* tree) const
{
    if(tree != NULL)
    {
        postOrder(tree->left);
        postOrder(tree->right);
        cout<< tree->key << " " ;
    }
}

template <class T, class  E>
void AVLTree<T,E>::postOrder() 
{
    postOrder(mRoot);
}

template<class T, class  E>
AVLTreeNode<T,E>* AVLTree<T,E>::indexsearch(AVLTreeNode<T,E>* x, int num){
    int sum = 0; 
    if (x -> left != NULL)  sum = x -> left -> sz;
    if (num > sum){
        if (num == (sum + 1)) return x;
        return indexsearch(x->right,num-(sum + 1));
    } else return indexsearch(x->left,num);
}

template<class T, class  E>
AVLTreeNode<T,E>* AVLTree<T,E>::indexsearch(int num){
    if (num > mRoot->sz) return NULL;
    return indexsearch(mRoot,num);
}

/*
 * (递归实现)查找"AVL树x"中键值为key的节点
 */
template <class T, class  E>
AVLTreeNode<T,E>* AVLTree<T,E>::search(AVLTreeNode<T,E>* x, T key) const
{
    if (x==NULL || x->key==key)
        return x;

    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}

template <class T, class  E>
AVLTreeNode<T,E>* AVLTree<T,E>::search(T key) 
{
    return search(mRoot, key);
}

/*
 * (非递归实现)查找"AVL树x"中键值为key的节点
 */
template <class T, class  E>
AVLTreeNode<T,E>* AVLTree<T,E>::notIterativeSearch(AVLTreeNode<T,E>* x, T key) const
{
    while ((x!=NULL) && (x->key!=key))
    {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    return x;
}

template <class T, class  E>
AVLTreeNode<T,E>* AVLTree<T,E>::notIterativeSearch(T key)
{
    return notIterativeSearch(mRoot, key);
}

/* 
 * 查找最小结点：返回tree为根结点的AVL树的最小结点。
 */
template <class T, class  E>
AVLTreeNode<T,E>* AVLTree<T,E>::minimum(AVLTreeNode<T,E>* tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}

template <class T, class  E>
T AVLTree<T,E>::minimum()
{
    AVLTreeNode<T,E> *p = minimum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}
 
/* 
 * 查找最大结点：返回tree为根结点的AVL树的最大结点。
 */
template <class T, class  E>
AVLTreeNode<T,E>* AVLTree<T,E>::maximum(AVLTreeNode<T,E>* tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->right != NULL)
        tree = tree->right;
    return tree;
}

template <class T, class  E>
T AVLTree<T,E>::maximum()
{
    AVLTreeNode<T,E> *p = maximum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}

/*
 * LL：左左对应的情况(左单旋转)。
 *
 * 返回值：旋转后的根节点
 */
template <class T, class  E>
AVLTreeNode<T,E>* AVLTree<T,E>::leftLeftRotation(AVLTreeNode<T,E>* k2)
{
    AVLTreeNode<T,E>* k1;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max( height(k2->left), height(k2->right)) + 1;
    k1->height = max( height(k1->left), k2->height) + 1;

    return k1;
}

/*
 * RR：右右对应的情况(右单旋转)。
 *
 * 返回值：旋转后的根节点
 */
template <class T, class  E>
AVLTreeNode<T,E>* AVLTree<T,E>::rightRightRotation(AVLTreeNode<T,E>* k1)
{
    AVLTreeNode<T,E>* k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max( height(k1->left), height(k1->right)) + 1;
    k2->height = max( height(k2->right), k1->height) + 1;

    return k2;
}

/*
 * LR：左右对应的情况(左双旋转)。
 *
 * 返回值：旋转后的根节点
 */
template <class T, class  E>
AVLTreeNode<T,E>* AVLTree<T,E>::leftRightRotation(AVLTreeNode<T,E>* k3)
{
    k3->left = rightRightRotation(k3->left);

    return leftLeftRotation(k3);
}

/*
 * RL：右左对应的情况(右双旋转)。
 *
 * 返回值：旋转后的根节点
 */
template <class T, class  E>
AVLTreeNode<T,E>* AVLTree<T,E>::rightLeftRotation(AVLTreeNode<T,E>* k1)
{
    k1->right = leftLeftRotation(k1->right);

    return rightRightRotation(k1);
}

/* 
 * 将结点插入到AVL树中，并返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     key 插入的结点的键值
 * 返回值：
 *     根节点
 */

template <class T, class  E>
AVLTreeNode<T,E>* AVLTree<T,E>::insert(AVLTreeNode<T,E>* &tree, T key, E value)
{
    if (tree == NULL) 
    {
        // 新建节点
        tree = new AVLTreeNode<T,E>(key, value, NULL, NULL);
        if (tree==NULL)
        {
            cout << "ERROR: create avltree node failed!" << endl;
            return NULL;
        }
    }
    else if (key < tree->key) // 应该将key插入到"tree的左子树"的情况
    {
        tree->left = insert(tree->left, key, value);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (height(tree->left) - height(tree->right) == 2)
        {
            if (key < tree->left->key)
                tree = leftLeftRotation(tree);
            else
                tree = leftRightRotation(tree);
        }
    }
    else if (key > tree->key) // 应该将key插入到"tree的右子树"的情况
    {
        tree->right = insert(tree->right, key, value);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (height(tree->right) - height(tree->left) == 2)
        {
            if (key > tree->right->key)
                tree = rightRightRotation(tree);
            else
                tree = rightLeftRotation(tree);
        }
    }
    else //key == tree->key)
    {
        cout << "添加失败：不允许添加相同的节点！" << endl;
    }

    tree->height = max( height(tree->left), height(tree->right)) + 1;

    return tree;
}

template <class T, class  E>
void AVLTree<T,E>::insert(T key, E value)
{
    insert(mRoot, key, value);
}

/* 
 * 删除结点(z)，返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     z 待删除的结点
 * 返回值：
 *     根节点
 */
template <class T, class  E>
AVLTreeNode<T,E>* AVLTree<T,E>::remove(AVLTreeNode<T,E>* &tree, AVLTreeNode<T,E>* z)
{
    // 根为空 或者 没有要删除的节点，直接返回NULL。
    if (tree==NULL || z==NULL)
        return NULL;

    if (z->key < tree->key)        // 待删除的节点在"tree的左子树"中
    {
        tree->left = remove(tree->left, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (height(tree->right) - height(tree->left) == 2)
        {
            AVLTreeNode<T,E> *r =  tree->right;
            if (height(r->left) > height(r->right))
                tree = rightLeftRotation(tree);
            else
                tree = rightRightRotation(tree);
        }
    }
    else if (z->key > tree->key)// 待删除的节点在"tree的右子树"中
    {
        tree->right = remove(tree->right, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (height(tree->left) - height(tree->right) == 2)
        {
            AVLTreeNode<T,E> *l =  tree->left;
            if (height(l->right) > height(l->left))
                tree = leftRightRotation(tree);
            else
                tree = leftLeftRotation(tree);
        }
    }
    else    // tree是对应要删除的节点。
    {
        // tree的左右孩子都非空
        if ((tree->left!=NULL) && (tree->right!=NULL))
        {
            if (height(tree->left) > height(tree->right))
            {
                // 如果tree的左子树比右子树高；
                // 则(01)找出tree的左子树中的最大节点
                //   (02)将该最大节点的值赋值给tree。
                //   (03)删除该最大节点。
                // 这类似于用"tree的左子树中最大节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
                AVLTreeNode<T,E>* max = maximum(tree->left);
                tree->key = max->key;
                tree->left = remove(tree->left, max);
            }
            else
            {
                // 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
                // 则(01)找出tree的右子树中的最小节点
                //   (02)将该最小节点的值赋值给tree。
                //   (03)删除该最小节点。
                // 这类似于用"tree的右子树中最小节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
                AVLTreeNode<T,E>* min = minimum(tree->right);
                tree->key = min->key;
                tree->right = remove(tree->right, min);
            }
        }
        else
        {
            AVLTreeNode<T,E>* tmp = tree;
            tree = (tree->left!=NULL) ? tree->left : tree->right;
            delete tmp;
        }
    }

    return tree;
}

template <class T, class  E>
void AVLTree<T,E>::remove(T key)
{
    AVLTreeNode<T,E>* z; 

    if ((z = search(mRoot, key)) != NULL)
        mRoot = remove(mRoot, z);
}

template<class T, class  E>
void AVLTree<T,E>::dfs(AVLTreeNode<T,E>*z){
    if (z != NULL) insert(mRoot,z -> key, z -> value);
    if (z -> left != NULL) dfs(z -> left);
    if (z -> right != NULL) dfs(z -> right);    
}


template<class T, class  E>
void AVLTree<T,E>::merge(AVLTree<T,E>* z){
    dfs(z -> mRoot);
}


template<class T, class  E>
void AVLTree<T,E>::dfs1(AVLTree<T,E>*x, AVLTreeNode<T,E>*y, T z){
    if (y != NULL)  if (y -> key > z) x -> insert(y-> key,y->value), remove(y -> key);
    if (y -> left != NULL) dfs1(x,y->left,z);
    if (y -> right != NULL) dfs1(x,y->right,z); 
}


template<class T, class  E>
void AVLTree<T,E>::split(AVLTree<T,E>*z, T x){
    dfs1(z, mRoot, x);
}


/* 
 * 销毁AVL树
 */
template <class T, class  E>
void AVLTree<T,E>::destroy(AVLTreeNode<T,E>* &tree)
{
    if (tree==NULL)
        return ;

    if (tree->left != NULL)
        destroy(tree->left);
    if (tree->right != NULL)
        destroy(tree->right);

    delete tree;
}

template <class T, class  E>
void AVLTree<T,E>::destroy()
{
    destroy(mRoot);
}

/*
 * 打印"二叉查找树"
 *
 * key        -- 节点的键值 
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
template <class T, class  E>
void AVLTree<T,E>::print(AVLTreeNode<T,E>* tree, T key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    // tree是根节点
            cout << setw(2) << tree->key << " is root" << endl;
        else                // tree是分支节点
            cout << setw(2) << tree->key << " is " << setw(2) << key << "'s "  << setw(12) << (direction==1?"right child" : "left child") << endl;

        print(tree->left, tree->key, -1);
        print(tree->right,tree->key,  1);
    }
}

template <class T, class  E>
void AVLTree<T,E>::print()
{
    if (mRoot != NULL)
        print(mRoot, mRoot->key, 0);
}
#endif