/*************************************************************************
	> File Name: 2_二叉字典树.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年08月08日 星期三 10时14分40秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX_N 100000
#define SIZE 260
#define swap(a, b) {\
    typeof(a) (__temp) = (a);\
    (a) = (b);\
    (b) = (__temp);\
}
typedef struct Node{   // huff结点
    int freq;
    unsigned char ch;
    struct Node *lchild, *rchild;
}Node;

typedef struct Heap{   //堆
    Node **data;
    int count, size;
}Heap;

typedef struct D_Node{   //字典树
    int flag;
    char *str;
    struct D_Node *next[2];
}D_Node;
int d_cnt = 0;
D_Node *get_DNode() {
    d_cnt++;
    return calloc(sizeof(D_Node), 1);
}

void clear(D_Node *root) {
    if(!root) return ;
    for(int i = 0; i < 2; ++i) {
        if(!root->next[i]) continue;
        clear(root->next[i]);
    }
    if(root->flag) free(root->str);
    free(root);
    return ;
}
int insert_length = 0;
int insert_cnt = 0;
D_Node *insert(D_Node *root, unsigned char *str, unsigned char (*huff_code)[SIZE]) {
    if(!root) root = get_DNode();
    D_Node *p = root;
    for(int i = 0; str[i]; ++i) {
        int ind = str[i];
        insert_length += strlen(huff_code[ind]);
        for(int j = 0; huff_code[ind][j]; ++j) {
            int x = huff_code[ind][j] - '0';
            if(!p->next[x]) p->next[x] = get_DNode();
            p = p->next[x];
        }
    }
    insert_cnt++;
    if(!p->flag)p->str = strdup(str);
    p->flag += 1;
    return root;
}
int search_cnt = 0, search_length = 0;
int match_search(D_Node *root, unsigned char *str, unsigned char (*huff_code)[SIZE]) {
    #define RETURN(a, b, c) {\
        printf("当前查找字符串个数 : %d\n总查找步数 : %d\n平均查找步数为 : %lf\n", b, c, 1.0 * (c / b));\
        printf("find %s : res : %d\n", str, a);\
        return a;\
    }

    if(!root) RETURN(0, search_cnt, search_length);
    search_cnt++;
    D_Node *p = root;
    for(int i = 0; str[i]; ++i) {
        int ind = str[i];
        for(int j = 0; huff_code[ind][j]; ++j) {
            int x = huff_code[ind][j] - '0';
            if(!p->next[x]) RETURN(0, search_cnt, search_length);
            search_length++;
            p = p->next[x];
        }
    }
    if(p->flag) RETURN(1, search_cnt, search_length);
    RETURN(0, search_cnt, search_length);
    #undef RETURN
}
int find_cnt = 0, find_length = 0;

void find_str_all(D_Node *root) {
    
    for(int i = 0; i < 2; ++i) {
        if(!root->next[i]) continue;
        if(root->next[i]->flag){
            find_cnt++;
            printf("find str : %s\n", root->next[i]->str);
        }
        find_length++;
        find_str_all(root->next[i]);
    }
    
    return ;
}


Heap *Get_Heap(int n) {
    Heap *p = (Heap *)malloc(sizeof(Heap));
    p->data = calloc(sizeof(Node *), n);
    p->count = 0;
    p->size = n;
    return p;
}

int cmp_node(Node *p, Node *q) {
    return p->freq > q->freq;
}

void push(Heap *h, Node *p) {
    if(h->count >= h->size) return ;
    int current = h->count;
    int father = (current - 1) / 2;
    h->data[current] = p;
    while(father >= 0 && cmp_node(h->data[father], h->data[current])) {
        swap(h->data[father], h->data[current]);
        current = father;
        father = (current - 1) / 2;
    }
    h->count++;
    return ;
}

void update_heap(Heap *h, int pos, int n) {
    int l = pos * 2 + 1, r = pos * 2 + 2;
    int min = pos;
    if(l < n && cmp_node(h->data[min], h->data[l])) min = l;
    if(r < n && cmp_node(h->data[min], h->data[r])) min = r;
    if(min != pos) {
        swap(h->data[min], h->data[pos]);
        update_heap(h, min, n);
    }
    return ;
}

void pop(Heap *h) {
    if(!h->count) return;
    h->count--;
    swap(h->data[0], h->data[h->count]);
    update_heap(h, 0, h->count);
    return ;
}

Node *top(Heap *h) {
    if(h->count == 0) return NULL;
    return h->data[0];
}
void clear_heap(Heap *h) {
    if(!h) return ;
    free(h->data);
    free(h);
    return ;
}

int node_cnt = 0;
Node *get_node(int freq, unsigned char ch) {
    Node *p =  calloc(sizeof(Node), 1);
    p->ch = ch;
    p->freq = freq;
    node_cnt++;
    return p;
}

Node *build_huff(Heap *h) {
    while(h->count > 1) {
        Node *p = top(h);pop(h);
        Node *q = top(h);pop(h);
        Node *new_node = get_node(p->freq + q->freq, 'a');
        new_node->lchild = p;
        new_node->rchild = q;
        push(h, new_node);
    }
    return h->data[0];
}

void extract_huff(Node *root, unsigned char *huff, unsigned char (*huff_code)[SIZE], int n) {
    huff[n] = '\0';
    if(!root->lchild && !root->rchild) {
        strcpy(huff_code[root->ch], huff);
        return ;
    }
    huff[n] = '1';
    extract_huff(root->lchild, huff, huff_code, n + 1);
    huff[n] = '0';
    extract_huff(root->rchild, huff, huff_code, n + 1);
    return ;
}

void clear_Node (Node *root) {
    if(!root) return;
    if(root->lchild) clear_Node(root->lchild);
    if(root->rchild) clear_Node(root->rchild);
    free(root);
    return ;
}

void word_count(int *arr) {          //22M的串输入来统计字节频率
    unsigned char str[100000];
    FILE *fp = fopen("./input", "r");
    while(fread(str, 999, 1, fp) > 0) {
        //printf("%s\n", str);
        for(int i = 0; str[i]; ++i){
            if(str[i] == ' ' || str[i] == '\n') continue;
            arr[str[i]]++;
        }
    }
    fclose(fp);
    printf("jieshu\n");
}
D_Node* insert_input_to_droot(D_Node *d_root, unsigned char (*huff_code)[SIZE], int *word_cnt) {
    unsigned char str[100000];
    FILE *fp = fopen("./input_str", "r");
    while(fgets(str, 100000, fp) != NULL){
        printf("%s\n", str);
        int cnt = strlen(str);
        str[cnt - 1] = '\0';
        *word_cnt += cnt - 1;
        d_root = insert(d_root, str, huff_code);
    }
    fclose(fp);
    printf("当前总插入字符串 : %d个\n插入总长度为 : %d步\n平均长度 : %lf步\n", insert_cnt, insert_length, 1.0 * (insert_length / insert_cnt));
    return d_root;
}
D_Node* insert_str_droot(D_Node *d_root, unsigned char (*huff_code)[SIZE], int *word_cnt) {
    printf("输入想插入字符串个数:\n");
    int n;
    fflush(stdin);
    scanf("%d", &n);
    unsigned char str[100000];
	for(int i = 0; i < n; ++i) {
        scanf("%s", str);
        *word_cnt += strlen(str);
        d_root = insert(d_root, str, huff_code);
    }
    return d_root;
}

int IQ_cnt = 0;
void clear_droot_main(D_Node *d_root, int *cnt) {
    if(!d_root) {
        IQ_cnt++;
        if(IQ_cnt >= 5) {
            while(1) printf("操作失误5次，你好像个zz\n");
        }
        printf("当前字典为空不需要清空 剩余机会%d\n", 5 - IQ_cnt);    
        return ;
    }
    clear(d_root);
    printf("清除完毕\n");
    insert_cnt = 0;
    insert_length = 0;
    *cnt = 0;
}

void find_str_droot_main(D_Node *d_root, unsigned char (*huff_code)[SIZE]) {
    if(!d_root) {
        IQ_cnt++;
        printf("请你先建造一颗字典树,我才能查找\n");
        return ;
    }
    char ch;
    while((ch = getchar()) != '\n' && ch != EOF);
    unsigned char str[1000];
    printf("输入查找字符串\n");
    fgets(str, 1000, stdin);
    str[strlen(str) - 1] = '\0';

    match_search(d_root, str, huff_code);
}
Node *word_cnt_build_huff(Node *root, int *arr_count, unsigned char (*huff_code)[SIZE]) {
    clear_Node(root);
    root = NULL;
    memset(arr_count, 0, sizeof(arr_count));
    memset(huff_code, '\0', sizeof(huff_code));
    word_count(arr_count);          //统计词频
    Heap *h = Get_Heap(SIZE);  
    unsigned char huff[SIZE] = {0};
    for(int i = 0; i < SIZE; ++i) {
    	if(arr_count[i]){
       	 	Node *p = get_node(arr_count[i],  i);
        	push(h, p);                               //入堆
        }
    }
    root = build_huff(h);                //构造huffman树
    extract_huff(root, huff, huff_code, 0);     //从huff树上提取huffman编码存到huffcode中  010101
    clear_heap(h);
       
    return root;
}
void show_code(int *arr, unsigned char (*huff_code)[SIZE]) {
    for(int i = 0; i < SIZE; ++i) {
        if(!arr[i]) continue;
        printf("%d : %d\n", i, arr[i]);
    }
    for(int i = 0; i < SIZE; ++i) {
        if(!huff_code[i][0]) continue;
        printf("%d : %s\n", i, huff_code[i]);
    }
}
int main() {
    char input_str[1000];
    unsigned char huff_code[SIZE][SIZE] = {0};
    int arr_count[SIZE] = {0};
    Node *root = NULL;
    D_Node *d_root = NULL;
    int n;
    int word_cnt = 0;
    printf("0 : 查看编码情况，字符个数\n1 : 统计词频+构造huffman树，提取huff编码\n2 : 插入字符串到现有字典树\n");
    printf("3 : 从文件中读取字符串并插入字典树\n4 : 查询字符串\n5 : 查询当前所有字符串， 并输出利用率\n6 : 清除现有字典树\n"); 
    while(1) {
        scanf("%d", &n);
        switch(n) {
            case 0: {
                show_code(arr_count, huff_code);
            }break;
            case 1:  {					//统计词频+构造huffman树，提取
                root = word_cnt_build_huff(root, arr_count, huff_code);
                fflush(stdin);
            }break;
            case 2: {             //插入字符串到现有字典树
                d_root = insert_str_droot(d_root, huff_code, &word_cnt);
            }break;
            case 3:{                  //从文件中读取字符串并插入字典树5000行不重复长文本，输出平均插入长度
                d_root = insert_input_to_droot(d_root, huff_code, &word_cnt);
            }break;
            case 4: {             //查询字符串，输出当前查找长度，和平均查找长度
                find_str_droot_main(d_root, huff_code);
            }break;
            case 5: {              //查询当前所有字符串， 并输出利用率
                find_cnt = 0,find_length = 0;
        		find_str_all(d_root);
                printf("查找到字符串个数 : %d\n查找到字符串总步数 : %d\n", find_cnt, find_length);
                printf("平均步数 : %lf\n", 1.0 * (find_length / find_cnt));
                printf("storagr rate : %lf \n", 1.0 * word_cnt / (1.0 * d_cnt *(sizeof(D_Node) - sizeof(char *))));
            }break;
            case 6: {             //清除现有字典树
                clear_droot_main(d_root, &word_cnt);
                d_root = NULL;
            }break;
            default: {
                IQ_cnt++;
                printf("请输0 - 6\n");
                printf("0 : 查看编码情况，字符个数\n1 : 统计词频+构造huffman树，提取huff编码\n2 : 插入字符串到现有字典树\n");
                printf("3 : 从文件中读取字符串并插入字典树\n4 : 查询字符串\n5 : 查询当前所有字符串， 并输出利用率\n6 : 清除现有字典树\n");
                break;
            }break;
        }
        char ch;
  		while((ch = getchar()) != '\n' && (ch != EOF));
    }
    
    
    
    return 0;
}

