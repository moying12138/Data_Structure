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

#define max(a, b) ((a) > (b) ? (a) : (b))
typedef struct DANode{
    int base, check;
}DANode;

typedef struct Node{
    int flag;
    struct Node *next[26];
}Node;

int node_cnt = 0;



Node *get_node() {
    node_cnt++;
    Node *p = (Node *)malloc(sizeof(Node));
    p->flag = 0;
    memset(p->next, 0, sizeof(Node *) * 26);
    return p;
}

void clear(Node *root) {
    if(!root) return ;
    for(int i = 0; i < SIZE; ++i) {
        clear(root->next[i]);
    }
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

void get_random_string(char *str) {
    int len = rand() % 10 + 2;
    for(int i = 0; i < len; ++i) str[i] = BASE + rand() % SIZE;
    str[len] = 0;
    return ;
}


void output(Node *root, char *str, int level) {
    if(!root) return ;
    str[level] = 0;
    if(root->flag) {
        printf("find word : %s\n", str);
    }
    for(int i = 0; i < SIZE; ++i) {
        if(!root->next[i]) continue;
        str[level] = i + BASE;
        output(root->next[i], str, level + 1);
    }
}
void output_double(DANode *data, char *str, int level, int ind) {
    if(!data) return ;
    str[level] = 0;
    if(data[ind].check < 0) {
        printf("find word : %s\n", str);
    }
    for(int i = 0; i < SIZE; ++i) {
        if(abs(data[data[ind].base + i].check) != ind) continue;
        str[level] = i + BASE;
        output_double(data, str, level + 1, data[ind].base + i);
    }
}

int get_base(Node *node, DANode *data) {
    int base = 2, flag = 0;
    while(!flag) {
        flag = 1;
        for(int i = 0; i < SIZE; ++i) {
            if(node->next[i] == NULL) continue;
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
    if(node->flag) data[ind]. check = -data[ind].check;
    int max_ind = ind;
    data[ind].base = get_base(node, data);
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




int main() {
    srand(time(0));
    #define INSERT_CNT 1000
    Node *root = NULL;
    char str[50];
    int word_cnt = 0;
    for (int i = 0; i < INSERT_CNT; ++i) {
        get_random_string(str);
        if(str[0] == 0) continue;
        word_cnt += strlen(str);
        root = insert(root, str);
        printf("insert %s to Trie \n", str);
    }
    output(root, str, 0);
    printf("storage rate : %lf\n", 1.0 * word_cnt / (1.0 * node_cnt * sizeof(Node)));
    DANode *data = (DANode *)calloc(sizeof(DANode) , INSERT_CNT * 100);
    int da_cnt = build(root, data, 1);
    output_double(data, str, 0, 1);
    printf("storage rate : %lf\n", 1.0 * da_cnt / (1.0 * da_cnt * sizeof(DANode)));
    clear(root);
    #undef INSERT_CNT
    return 0;
}
