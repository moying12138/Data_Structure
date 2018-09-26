/*************************************************************************
	> File Name: 2_avl二叉平衡树.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年09月21日 星期五 20时17分06秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define MAX(a, b) ({\
    __typeof(a) _a = (a);\
    __typeof(b) _b = (b);\
    _a > _b  ? _a : _b;\
                  })
typedef struct Node{
    int val, h;
    struct Node *lchild, *rchild; 
}Node;

Node *NIL;
__attribute__((constructor)) void init_nil() {
    NIL = (Node *)malloc(sizeof(Node ) );
    NIL->val = 0;
    NIL->lchild = NIL->rchild = NIL;
    NIL->h = 0;
}
Node *getNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node ));
    p->val = val;
    p->lchild = p->rchild = NIL;
    p->h = 1;
    return p;
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    root->h = MAX(root->lchild->h, root->rchild->h) + 1;
    temp->h = MAX(temp->lchild->h, temp->rchild->h) + 1;
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    root->h = MAX(root->lchild->h, root->rchild->h) + 1;
    temp->h = MAX(temp->lchild->h, temp->rchild->h) + 1;
    return temp;
}

Node *maintain(Node *root) {
    if(abs(root->lchild->h - root->rchild->h) < 2) return root;
    if(root->lchild->h > root->rchild->h) {
        if(root->lchild->lchild->h < root->lchild->rchild->h) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    } else {
        if(root->rchild->lchild->h > root->rchild->rchild->h) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root); 
    }
}


Node *insert(Node *root, int val) {
    if(root == NIL) return getNode(val);
    if(root->val == val) return root;
    if(root->val < val) {
        root->rchild = insert(root->rchild, val);

    } else {
        root->lchild = insert(root->lchild, val);

    }
    root->h = MAX(root->lchild->h, root->rchild->h) + 1;   //加入NIL可以省代码,这里没有空了,只有NIL高度位0
    root = maintain(root);

}


void clear(Node *root) {
    if(root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void output(Node *root) {
    if(root == NIL) return ;
    printf("(%d, %d, %d)\n", root->val, root->lchild->val, root->rchild->val);
    output(root->lchild);
    output(root->rchild);
}

int main() {
    srand(time(0));
    //init_nil();
    Node *root = NIL;
    for(int i = 1; i <= 5; ++i) {
        root = insert(root, i);
        output(root);
        printf("--------\n");
    }
    clear(root);
    root = NIL;
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        int key;
        scanf("%d", &key);
        insert(root, key);
        output(root);
        printf("-------\n");
    }

    return 0;
}
