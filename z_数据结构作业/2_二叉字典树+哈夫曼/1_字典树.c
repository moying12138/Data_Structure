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
    unsigned char *str;
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
int insert_length = 0, insert_cnt = 0;
Node *insert(Node *root, unsigned char *str) {
    int cnt = 0;
    if(!root) root = get_node();
    Node *p = root;
    insert_length += strlen(str);
    for(int i = 0; str[i]; ++i) {
        if(!p->next[str[i]]) p->next[str[i]] = get_node();
        p = p->next[str[i]];
    }
    p->str = strdup(str);
    if(!p->flag) insert_cnt++;
    p->flag = 1;
    
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

int search_cnt = 0, search_length = 0;
void output(Node *root) {
    if(!root) return ;
    if(root->flag) {
        search_cnt++;
        printf("find string : %s\n", root->str);
    }
    for(int i = 0; i < SIZE; ++i) {
        if(!root->next[i]) continue;
        search_length++;
        output(root->next[i]);
    }
}

int main() {
    unsigned char str[100000];
    Node *root = NULL;
    FILE *fp = fopen("./input_str", "r");
    while(fgets(str, 10000, fp)) {
        str[strlen(str) - 1] = '\0';
        root = insert(root, str);
    }
    output(root);

    printf("查找字符串个数 : %d\n总查找长度 : %d\n平均查找长度 : %lf\n", search_cnt, search_length, 1.0 * (search_length / search_cnt));
    printf("storagr rate : %lf\n", 1.0 * insert_length / (1.0 * node_cnt * (sizeof(Node) - sizeof(char *))));
    clear(root);

    
    
    return 0;
}
