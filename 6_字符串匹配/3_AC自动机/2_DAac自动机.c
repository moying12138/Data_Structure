/*************************************************************************
	> File Name: 2_双数组字典树.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年08月04日 星期六 15时28分39秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 26
#define BASE 'a'
#define has_child(data, ind ,i) (abs(data[data[ind].base + i].check) == ind) 
#define max(a, b) ((a) > (b) ? (a) : (b))
typedef struct DANode{
    int base, check, fail;
    char *str;
}DANode;

typedef struct Node{
    int flag;
    struct Node *next[26];
    char *str;
}Node;

int node_cnt = 0;



Node *get_node() {
    Node *p = calloc(sizeof(Node), 1);
    node_cnt++;
    return p;
}

void clear(Node *root) {
    if(!root) return ;
    for(int i = 0; i < SIZE; ++i) {
        clear(root->next[i]);
    }
    if(root->flag) free(root->str);
    free(root);
    return ;
}


Node *insert(Node *root, const char *str) {
    if(!root) root = get_node();
    Node *p = root;
    for(int i = 0; str[i]; ++i) {
        int ind = str[i] - BASE;
        if(!p->next[ind]) p->next[ind] = get_node();
        p = p->next[ind];
    }
    p->flag = 1;
    p->str = strdup(str);
    return root;
}

int search(Node *root, const char *str) {
    Node *p = root;
    int i = 0;
    while(p && str[i]) {
        int ind = str[i++] - BASE;
        p = p->next[ind];
    }
    if(p && p->flag == 1) return 1;
    return 0;
}

int get_base(Node *node, DANode *data) {
    int base = 2, flag = 0;
    while(!flag) {
        flag = 1;
        for(int i = 0; i < SIZE; ++i) {
            if(!node->next[i])continue;
            if(data[base + i].check == 0) continue;
            flag = 0;
            break;
        }
        base += (!flag);
    }
    return base;
}


int  build(Node *node, DANode *data, int ind) {
    if(!node ) return 0;
    if(node->flag) data[ind].check = -data[ind].check, data[ind].str = node->str;
    data[ind].base = get_base(node, data);
    int max_ind = ind;
    for(int i = 0; i < SIZE; ++i) {
        if(!node->next[i])continue;
        data[data[ind].base + i].check = ind;
    }
    for(int i = 0; i < SIZE; ++i) {
        if(!node->next[i]) continue;
        int temp = build(node->next[i], data, data[ind].base + i);
        max_ind = max(max_ind, temp);
    }
    return max_ind;
}

void build_ac(DANode *data) {
    #define MAX_N 100000
    int *queue = (int *)malloc(sizeof(int) * MAX_N);
    int head = 0, tail = 0;
    data[1].fail = 0;
    queue[tail++] = 1;
    while(head < tail) {
        int ind = queue[head++];
        for(int i = 0; i < SIZE; ++i) {
            if(!has_child(data, ind, i)) continue;
            int p = data[ind].fail;
            while(p && !has_child(data, p, i)) p = data[p].fail;
            if(p == 0) p = 1;
            else p = data[p].base + i;      
            data[data[ind].base + i].fail = p;
            queue[tail++] = data[ind].base + i;
        }
    }
    return ;
    #undef MAX_N
}


void search_ac(DANode *data, const char *str) {
    int p = 1; 
    for(int i = 0; str[i]; ++i) {
        while(p && !has_child(data, p, str[i] - BASE)) p = data[p].fail;
        if(p == 0) p = 1;
        else p = data[p].base + str[i] - BASE;
        int q = p;
        while(q) {
            if(data[q].check < 0) printf("find string : %s\n", data[q].str);
            q = data[q].fail;
        }
    }
    return ;
    
}
void output_da(DANode *data, int n) {
    for (int i = 1; i <= n; i++) {
        if (i - 1 && i % 5 == 1) printf("\n");
        printf("(%2d %2d %3d %3d)    ", i, data[i].base, data[i].check, data[i].fail);
    }
    printf("\n");
    return ;
}



int main() {
    #define INSERT_CNT 5
    Node *root = NULL;
    root = insert(root, "say");
    root = insert(root, "she");
    root = insert(root, "he");
    root = insert(root, "shr");
    root = insert(root, "her");
    DANode *data = (DANode *)calloc(sizeof(DANode) , INSERT_CNT * 100);
    int da_cnt = build(root, data, 1);
    build_ac(data);
    output_da(data, da_cnt);
    search_ac(data, "sasherhs");
    clear(root);
    #undef INSERT_CNT
    return 0;
}
