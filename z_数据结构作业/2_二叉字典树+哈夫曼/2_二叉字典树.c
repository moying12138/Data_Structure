


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct Node {
    int flag;
    struct Node *next[2];
    unsigned char *str;
} Node, *Trie;
int num[256][8] = {0};
void get_num(int (*num)[8]) {
    for (int i = 0; i < 256; i++) {
        int temp = i;
        for (int j = 0; j < 8; j++) {
            num[i][j] = temp % 2;
            temp /= 2;
        }
    }
}
int node_cnt = 0;
Node *get_new_node() {
    node_cnt++;
    return (Node *)calloc(sizeof(Node), 1);
}
int insert_length = 0, insert_cnt = 0, word_cnt = 0;
Node *insert(Trie root, unsigned char *str) {
    if(!root) root = get_new_node();
    Node *p = root;
    insert_cnt++;
    for (int i = 0; str[i]; i++) {
        insert_length += 8;
        for (int j = 0; j < 8; j++) {
            if (p->next[num[str[i]][j]] == NULL) {
                p->next[num[str[i]][j]] = get_new_node();
                node_cnt += 1;
            }
            p = p->next[num[str[i]][j]];
        }
    }
    if(!p->flag) word_cnt += strlen(str);
    p->flag = 1;
    p->str = strdup(str);
    return root;
}
int search(Trie root, unsigned char *str) {
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        for (int j = 0; j < 8; j++) {
            if (p->next[num[str[i]][j]] == NULL) return 0;
            p = p->next[num[str[i]][j]];
        }
    }
    return p->flag;
}
int search_length = 0, search_cnt = 0;
void output(Node *p) {
    if(!p) return ;
    for(int i = 0; i < 2; ++i) {
        if(!p->next[i]) continue;
        if(p->next[i]->flag) {
            search_cnt++;
            printf("find str: %s\n", p->next[i]->str);
        }
        search_length++;
        output(p->next[i]);
    }
    return ;
}
int main() {
    get_num(num);
    Node *root = NULL;
    unsigned char str[10000];
    FILE *fp = fopen("./input_str", "r");
    while(fgets(str, 10000, fp)) {
        str[strlen(str) - 1] = '\0';
        root = insert(root, str);
    }
    
    //printf("总插入字符串 : %d\n总插入长度 : %d\n平均插入长度 : %lf\n", insert_cnt, insert_length, 1.0 * (insert_length / insert_cnt));
    //getchar();
    output(root);

    printf("总查找到字符串 : %d\n总查找长度 : %d\n平均查找长度 : %lf\n", search_cnt, search_length, 1.0 * (search_length / search_cnt));
    printf("空间利用率 : = %lf\n", 1.0 * (word_cnt) / (node_cnt * (sizeof(Node) - sizeof(char *))));
    fclose(fp);
    return 0;
}
