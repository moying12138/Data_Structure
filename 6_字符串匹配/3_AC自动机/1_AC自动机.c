/*************************************************************************
	> File Name: 1_AC自动机.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年08月06日 星期一 10时46分28秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define BASE 26
#define BL 'a'
typedef struct Node {
    char *str;
    int flag;
    struct Node *next[26];
    struct Node *fail;
}Node;

Node *get_new_node() {
    return  (Node *)calloc(sizeof(Node), 1);
}




void clear(Node *p) {
    if(!p) return ;
    for(int i = 0; i < BASE; ++i) {
        if(!p->next[i]) continue;
        clear(p->next[i]);
    }
    if(p->flag) free(p->str);
    free(p);
    return ;
}

Node *insert(Node *root, const char *str) {
    if(!root) root = get_new_node();
    Node *p = root;
    for(int i = 0; str[i]; ++i) {
        if(!p->next[str[i] - BL]) p->next[str[i]- BL] = get_new_node();
        p = p->next[str[i] - BL];
    }
    p->flag = 1;
    p->str = strdup(str);
    return root;
}








void build_ac(Node *root) {
    #define MAX_N 100000
    if(!root) return ;
    Node **queue = (Node **)malloc(sizeof(Node *) * MAX_N);
    int head = 0, tail = 0;
    queue[tail++] = root;
    while(head < tail) {
        Node *node = queue[head++];
        for(int i = 0; i < BASE; ++i) {
            if(!node->next[i]) continue;
            Node *p = node->fail;
            while(p && !p->next[i]) p = p->fail;
            if(!p) node->next[i]->fail = root;
            else node->next[i]->fail = p->next[i];
            queue[tail++] = node->next[i];
        }
    }
    free(queue);
    return ;
    #undef MAX_N
}


void search_ac(Node *root, const char *text) {
    Node *p = root;
    for(int i = 0; text[i]; ++i) {
        while(p && !p->next[text[i] - BL]) p = p->fail;
        if(!p ) p = root;
        else p = p->next[text[i] - BL];
        Node *q = p;
        while(q) {
            if(q->flag) q->flag = 0,printf("find string : %s\n", q->str); 
            q = q->fail;
        }
    }
    return ;
}

int main() {
    Node *root = NULL;
    root = insert(root, "she");
    root = insert(root, "say");
    root = insert(root, "he");
    root = insert(root, "shr"); 
    root = insert(root, "her");
    build_ac(root);
    search_ac(root, "sashershe");
    
    return 0;
}
