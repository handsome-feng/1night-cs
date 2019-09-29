#include <stdio.h>

typedef ElemType char;

typedef struct BinaryTree
{
    ElemType data;
    struct BinaryTree *lchild;
    struct BinaryTree *rchild;
} TreeNode, * BiTree;

void IniBTree(BiTree BT)
{
    BT = NULL;
    return;
}

/* 先序创建二叉树:根结点->左子树->右子树 */
void CeateBiTree(BiTree T)
{
    char ch;
    ch = getchar();
    if (ch == ' ')
        BT = NULL;
    else
    {
        if (! (BT = (BiTree)malloc(sizeof(TreeNode))))
            exit(1);
        BT->data = ch;
        BT->lchild = NULL;
        BT->rchild = NULL;
        CeateBiTree(BT->lchild);
        CeateBiTree(BT->rchild);
    }
}

/* 利用广义表建立二叉树，既A(B (C, D), E(, F(G))) */
int statckMaxSize = 3;

void CreateBTreeWithGenList(BiTree BT, char *string)
{
    BiTree TempNode;
    Bitree s[statckMaxSize];  //定义数组为存储各结点的指针的栈
    int top = -1;      // 栈顶指针，初始值为-1。
    int branchValue;   // 分支值， 作为处理结点的标志，1表示处理左子树，2表示右
    int i = 0;         // 数组计数元素

    //原二叉树初始化
    BT = NULL;
}
