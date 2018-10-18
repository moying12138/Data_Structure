#include<stdio.h>
#include<stdlib.h>
typedef struct Node {
    int key, color;
    struct Node *lchild, *rchild;
}Tree;
Tree *NIL;
void init_NIL() {
    NIL = (Tree *)malloc(sizeof(Tree));
    NIL->key = 0;
    NIL->color = 1;
    NIL->lchild = NIL->rchild = NIL;
}
Tree *get_node(int key) {
    Tree *p = (Tree *)malloc(sizeof(Tree));
    p->key = key;
    p->color = 0;
    p->lchild = p->rchild = NIL;
    return p;
}

int hasredc(Tree *root) {
    return root->lchild->color == 0 || root->rchild->color == 0;
}

Tree *left(Tree *root) {
    Tree *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    return temp;
}
Tree *right(Tree *root) {
    Tree *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}
Tree* insert_maintain(Tree *root){
    if(root == NIL || root == NULL ) return root;
    if(!hasredc(root))return root;
    if(root->lchild->color == 0 && root->rchild->color == 0) {
        if(hasredc(root->lchild) || hasredc(root->rchild)) {
            root->color = 0;
            root->lchild->color = root->rchild->color = 1;
        }
        return root;
    } else if(root->lchild->color == 0 && hasredc(root->lchild)){
        if(root->lchild->rchild->color == 0) {
            root->lchild = left(root->lchild);
        }
        root = right(root);
        root->color = 0;
        root->lchild->color = root->rchild->color = 1;
    }else if(root->rchild->color == 0 && hasredc(root->rchild)){
        if(root->rchild->lchild->color == 0) {
            root->rchild = right(root->rchild);
        }
        root = left(root);
        root->color = 0;
        root->lchild->color = root->rchild->color = 1;
    } 
    return root;
}
Tree *__insert(Tree *root, int key) {
    if(root == NIL || root == NULL ) return get_node(key);
    if(root->key < key) root->rchild = __insert(root->rchild, key);
    else if(root->key > key) root->lchild = __insert(root->lchild, key);
    else return root;
    return insert_maintain(root);
}

Tree *insert(Tree *root, int key) {
    root = __insert(root, key);
    root->color = 1;
    return root;
}
Tree *erase_maintain(Tree *root) {
    if(root == NIL || root == NULL ) return root;
    if(root->lchild->color != 2 && root->rchild->color != 2) return root;
    if(hasredc(root)) {
        root->color = 0;
        if(root->lchild->color == 0) {
            root = right(root);
            root->color = 1;
            root->rchild  = erase_maintain(root->rchild);
        }else {
            root = left(root);
            root->color = 1;
            root->lchild  = erase_maintain(root->lchild);
        }
        return root;
    } else if(root->lchild->color == 2) {
        if(!hasredc(root->rchild)) {
            root->rchild->color = 0;
            root->lchild->color = 1;
            root->color += 1;
            return root;
        } else if(root->rchild->rchild->color != 0) {
            root->rchild = right(root->rchild);
            root->rchild->color = 1;
            root->rchild->rchild->color = 0;
        }
        root->lchild->color = 1;
        root = left(root);
        root->color = root->lchild->color;
        root->lchild->color = root->rchild->color = 1;
    }else if(root->rchild->color == 2) {
        if(!hasredc(root->lchild)) {
            root->lchild->color = 0;
            root->rchild->color = 1;
            root->color += 1;
            return root;
        } else if(root->lchild->lchild->color != 0) {
            root->lchild = left(root->lchild);
            root->lchild->color = 1;
            root->lchild->lchild->color = 0;
        }
        root->rchild->color = 1;
        root = right(root);
        root->color = root->rchild->color;
        root->lchild->color = root->rchild->color = 1;
    }
    return root;
}

Tree *pres(Tree *root) {
    root = root->lchild;
    while(root->rchild !=  NIL) root = root->rchild;
    return root;
}

Tree *__erase(Tree *root, int key) {
    if(root == NIL || root == NULL ) return root;
    if(root->key < key) root->rchild = __erase(root->rchild, key);
    else if(root->key > key) root->lchild = __erase(root->lchild, key);
    else {
        if(root->lchild == root->rchild) {
            NIL->color += root->color;
            free(root);
            return NIL;
        } else if(root->lchild == NIL || root->rchild == NIL) {
            Tree *temp = root->lchild == NIL ? root->rchild : root->lchild;
            temp->color += root->color;
            free(root);
            return temp;
        } else {
            Tree *temp = pres(root);
            root->key = temp->key;
            root->lchild = __erase(root->lchild, temp->key);
        }
    }
    return erase_maintain(root);
}

Tree *erase(Tree *root, int key) {
    root = __erase(root, key);
    root->color = 1;
    return root;
}

