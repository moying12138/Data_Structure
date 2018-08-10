/*************************************************************************
	> File Name: 1_字典树.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年08月08日 星期三 15时29分02秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 256

typedef struct Node {
    int flag;
    char *str;
    struct Node *next[SIZE];
}Node;
int node_cnt = 0;
Node *get_node() {
    node_cnt++;
    return calloc(sizeof(Node), 1);
}


void clear(Node *root) {
    if(!root) return;
    for(int i = 0; i < SIZE; ++i) {
        if(!root->next[i]) continue;
        clear(root->next[i]);
    }
    if(root->flag) free(root->str);
    free(root);
    return ;
}
int word_cnt = 0;
Node *insert(Node *root, char *str) {
    int cnt = 0;
    if(!root) root = get_node();
    Node *p = root;
    for(int i = 0; str[i]; ++i) {
        if(str[i] > 0) continue;
        cnt++;
        if(!p->next[str[i] * -1]) p->next[str[i] * -1] = get_node();
        p = p->next[str[i] * -1];
    }
    p->str = strdup(str);
    p->flag = 1;
    word_cnt += cnt / 3;
    return root;
}

int search(Node *root, char *str) {
    if(!root) return 0;
    Node *p = root;
    int i = 0;
    while(p && str[i]){
        if(str[i] > 0) continue;
        int ind = str[i] * -1;
        p = p->next[ind];
        i++;
    }
    if(p && p->flag == 1) return 1;
    return 0;
}

void output(Node *root) {
    if(!root) return ;
    if(root->flag) printf("find string : %s\n", root->str);
    for(int i = 0; i < SIZE; ++i) {
        if(!root->next[i]) continue;
        output(root->next[i]);
    }
}

int main() {
    char str[100000];
    Node *root = NULL;
    while(~scanf("%s", str)) {
        root = insert(root, str);
    }
    output(root);
    printf("storagr rate : %lf\n", 1.0 * word_cnt / (1.0 * node_cnt * sizeof(Node)));
    clear(root);

    
    
    return 0;
}
