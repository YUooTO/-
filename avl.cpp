#include <iostream>
#include "avltree.h"
using namespace std;

static int arr[]= {3,2,1,4,6,7,16,15,14,13,12,11,10,8,9};

int main()
{
    int i,ilen,op;
    ilen = 15;
    AVLTree<int,int>* tree=new AVLTree<int,int>();
    cout << "== �������: ";
    for(i=0; i<ilen; i++)
    {
        cout << arr[i] <<" ";
        tree->insert(arr[i],i);
    }
    tree -> push();
    cout << "\n== ǰ�����: ";
    tree->preOrder();

    cout << "\n== �������: ";;
    tree->inOrder();

    cout << "\n== �������: ";
    tree->postOrder();
    cout << endl;
    // ����ĳ���㡣
    op = 6;
    if (tree->search(op) != NULL)    
        cout<<tree->search(i)->value<<endl;
    else cout<<"�����������"<<endl;

    //index ����ĳ����
    i = 10;
    if (tree -> indexsearch(i) != NULL) 
        cout<<tree->indexsearch(i) -> value<<endl;
    else cout<<"�����������"<<endl;

    // index ɾ��ĳ���㡣
    if (tree -> indexsearch(i) != NULL){
        op = tree->indexsearch(i) -> key;
        tree -> remove(op);
    } else{
        cout<<"�����������"<<endl;
    }
    tree->push();

    cout << "== �߶�: " << tree->height() << endl;
    cout << "== ��Сֵ: " << tree->minimum() << endl;
    cout << "== ���ֵ: " << tree->maximum() << endl;
    cout << "== ������ϸ��Ϣ: " << endl;
    tree->print();

    i = 6;
    cout << "\n== ɾ���ڵ�: " << i;
    tree->remove(i);
    tree -> push();
    cout << "\n== �߶�: " << tree->height() ;
    cout << "\n== �������: " ;
    tree->inOrder();
    cout << "\n== ������ϸ��Ϣ: " << endl;
    tree->print();
    // ���ٶ�����
    tree->destroy();
    // �ϲ�����avl����
    AVLTree<int,int>* treea=new AVLTree<int,int>();
    AVLTree<int,int>* treeb=new AVLTree<int,int>();
    AVLTree<int,int>* treee = new AVLTree<int,int>();

    printf("----------------\n");
    cout<<"merge"<<endl;
    for (i = 0; i < 5; ++i)
        treea -> insert(arr[i],i);
    for (i = 5; i < 10; ++i)
        treeb -> insert(arr[i],i);
    treea -> merge(treeb,treee);
    treee -> print();
    printf("----------------\n");
    // ��������avl����
    cout<<"split"<<endl;

    AVLTree<int,int>* treec=new AVLTree<int,int>();
    AVLTree<int,int>* treed=new AVLTree<int,int>();
    AVLTree<int,int>* treef = new AVLTree<int,int>();
    for (i = 0; i < 10; ++i)
        treec -> insert(arr[i],i);
    op = 5;
    treec -> split(treed,treef,op);
    treed -> print();
    printf("------------------\n");
    treef -> print();

    return 0;
}