/*************************************************************************
	> File Name: 1_BST二叉搜索树.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年09月14日 星期五 18时50分36秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct BSTNode {
    int key;
    struct BSTNode *lchild, *rchild;
}BSTNode;


BSTNode *init(int key) {
    BSTNode *p = (BSTNode *)malloc(sizeof(BSTNode));
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}
BSTNode *insert(BSTNode *root, int key) {
    if(root == NULL) return init(key);
    if(root->key == key) return root;
    if(key < root->key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    return root;
}    

BSTNode *predecesor(BSTNode *node) {
    BSTNode *temp = node->lchild;
    while(temp->rchild ) temp = node->rchild;
    return temp;
}


BSTNode *delete_node(BSTNode *root, int key) {
    if(!root) return root;
    if(root->key == key) {
        if(!root->lchild && !root->rchild) {
            free(root);
            return NULL;
        }
        else if(root->lchild || root ->rchild) {
            BSTNode *temp = root->lchild ? root->lchild : root->rchild;
            free(root);
            return temp;
        } else {
            BSTNode *temp = predecesor(root);
            temp->key ^= root->key;
            root->key ^= temp->key;
            temp->key ^= root->key;
            root->lchild = delete_node(root->lchild, key);
        }
    } else {
        if(root->key < key) root->rchild = delete_node(root->rchild, key);
        else root->lchild =  delete_node(root->lchild, key);
    }
    return root;
}



void clear(BSTNode *root) {

}


void output(BSTNode *root) {
    if(!root) return ;
    output(root->lchild);
    printf("%d ", root->key);
    output(root->rchild);
}

int main() {
    srand(time(0));
    BSTNode *root = NULL;
    #define OP_NUM 20
    for(int i = 0; i < OP_NUM; ++i) {
        int key = rand() % 30;
        root = insert(root, key);
        printf("insert %d to tree\n", key);
        output(root), printf("\n");
    }
    for(int i = 0; i < OP_NUM; ++i) {
        int key = rand() % 30;
        root = delete_node(root, key);
        printf("delete_node %d to tree\n", key);
        output(root), printf("\n");
    } 
    
    return 0;
}
