/*************************************************************************
	> File Name: binary_tree.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年07月23日 星期一 11时43分56秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int key;
    struct Node *lchild, *rchild;
}Node;

Node *get_Node(int);
void clear(Node *);
void preorder(Node *);
void inorder(Node *);
void postorder(Node *);


int main() {
    Node *root = get_Node(1);
    root->lchild = get_Node(2);
    root->rchild = get_Node(3);
    root->lchild->lchild = get_Node(7);
    root->lchild->rchild = get_Node(8);
    root->lchild->rchild->lchild = get_Node(9);
    root->rchild->rchild = get_Node(4);
    root->rchild->rchild->lchild = get_Node(5);
    root->rchild->rchild->rchild = get_Node(6);
    preorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    return 0;
}
Node *get_Node(int data){
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = data;
    p->lchild = NULL;
    p->rchild = NULL;
    return p;
}
void clear(Node *root) {
    if(root == NULL) return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
}
void preorder(Node *root) {
    if(root == NULL) return ;
    printf("%d ", root->key);
    preorder(root->lchild);
    preorder(root->rchild);
}
void inorder(Node *root) {
    if(root  == NULL) return;
    inorder(root->lchild);
    printf("%d ", root->key);
    inorder(root->rchild);
}
void postorder(Node *root) {
    if(root == NULL) return ;
    postorder(root->lchild);
    postorder(root->rchild);
    printf("%d ", root->key);
}
