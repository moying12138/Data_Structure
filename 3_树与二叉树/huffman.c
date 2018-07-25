/*************************************************************************
	> File Name: huffman.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年07月23日 星期一 15时16分40秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define CHAR_NUM 26

#define swap(a, b) {\
    __typeof(a) temp;\
    temp = a;\
    a = b; \
    b = temp;\
}

typedef struct HFNode {
    char ch;
    int freq;
    struct HFNode *lchild, *rchild;
}HFNode;

HFNode *getNode() {
    HFNode *p = (HFNode *) malloc(sizeof(HFNode));
    p->freq = p->ch = 0;
    p->lchild = p->rchild = NULL;
    return p;
}

void build(int n, HFNode *arr[n]) {
    for(int i = 0; i < n - 1; ++i) {
        HFNode *minNode = arr[0];
        int ind = 0;
        for(int j = 1; j < n - i; ++j) {
            if(arr[j]->freq >= minNode->freq) continue;
            minNode = arr[j];
            ind = j;
        }
        swap(arr[ind], arr[n - i - 1]);
        minNode = arr[0];
        ind = 0;
        for(int j = 1; j < n - i - 1; ++j) {
            if(arr[j]->freq >= minNode->freq) continue;
            minNode = arr[j];
            ind = j;
        }
        swap(arr[ind], arr[n - i - 2]);
        HFNode *new_node = getNode();
        new_node->lchild = arr[n - i - 1];
        new_node->rchild = arr[n - i - 2];
        new_node->freq = arr[n - i - 1]->freq + arr[n - i - 2]->freq;
        arr[n - i - 2] = new_node;
    }
    return ;
}

void extract(HFNode *root, char *buff, char (*huffman_code)[100], int n) {
    buff[n] = '\0';
    if(root->lchild == NULL && root->rchild == NULL) {
        printf("%c : %s\n", root->ch, buff);
        strcpy(huffman_code[root->ch], buff);
        return ;
    }
    buff[n] = '0';
    extract(root->lchild, buff, huffman_code, n + 1);
    buff[n] = '1';
    extract(root->rchild, buff, huffman_code, n + 1);
    return ;

}


int main() {
    HFNode *arr[CHAR_NUM] = {0};
    char buff[100];
    char huffman_code[256][100] = {0};
    int freq;
    for(int i = 0; i < CHAR_NUM; ++i) {
        scanf("%s%d", buff, &freq);
        printf("read %s = %d\n", buff, freq);
        HFNode *new_node = getNode();
        new_node->ch = buff[0];
        new_node->freq = freq;
        arr[i] = new_node;
    }
    build(CHAR_NUM, arr);
    extract(arr[0], buff, huffman_code, 0);
    for(int i = 0; i < 256; ++i) {
        if(huffman_code[i][0] == 0) continue;
        printf("%c : %s\n", i, huffman_code[i]);
    }
    return 0;
}
