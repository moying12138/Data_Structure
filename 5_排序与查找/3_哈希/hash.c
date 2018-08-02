/*************************************************************************
	> File Name: hash_table.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年07月28日 星期六 16时04分42秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
typedef struct Data {
    char *str;
    struct Data *next;
}Data;


typedef struct HashTable{
    Data *data;
    int size;
    int cnt;
    int (*hash_func)(const char *);

}HashTable;




int BKDR(const char *str) {
    int hash = 0, seed = 3;
    for(int i = 0; str[i]; ++i) {
        hash = hash * seed + str[i];
    }
    return hash & 0x7fffffff;
}


int APHash(const char *str) {
    int hash = 0;
    for(int i = 0; str[i]; ++i) {
        if(i & 1) {
            hash ^= (hash << 7) ^ str[i] ^ (hash >> 3);
        } else {
            hash ^= (~((hash << 11) ^ str[i] ^ (hash >> 5)));
        }
    }
    return ( hash & 0x7fffffff);
}

int zobrist_table[50][256] = {0};

void init_zobrist_table() {
    for (int i = 0; i < 50; i++) {
        for(int j = 0; j < 256; ++j) {
            zobrist_table[i][j] = rand();
        }
    }
}
int zobrist_hash(const char *str) {
    static int flag = 1;
    if(flag) {
        init_zobrist_table();
        flag = 0;
    }
    int hash = 0;
    for(int i = 0; str[i]; ++i) {
        hash ^= zobrist_table[i][str[i]];
    }
    return hash & 0x7fffffff;
}

int MyHash(const char *str) {
    int hash = 1;
    for(int i = 0; str[i]; ++i) {
        hash *= str[i];
    }
    return hash & 0x7fffffff;
}



HashTable *init(int size, int (*func)(const char *)) {
    HashTable *p = (HashTable *)malloc(sizeof(HashTable));
    p->data = (Data *)calloc(size, sizeof(Data));
    p->size = size;
    p->cnt = 0;
    p->hash_func = func;
    return p;
}

void clear(HashTable *p) {
    if(!p) return ;
    free(p->data);
    free(p);
    return ;
}

int query(HashTable *h, const char *str) {
    int ind = h->hash_func(str) % h->size;
    Data *p = h->data[ind].next;
    while(p){
        if(strcmp(p->str, str) == 0) return -1;
        p = p->next;
        h->cnt += 1;
    }
    return ind;
}


void insert(HashTable *h, const char *str) {
    int ind = query(h, str);
    if(ind == -1) return ;
    Data *data = (Data *)malloc(sizeof(Data));
    data->str = strdup(str);
    data->next = h->data[ind].next;
    h->data[ind].next = data;
    return ;
}



int main() {
    #define HASH_TABLE_SIZE 100
    HashTable *aphash = init(HASH_TABLE_SIZE, APHash);
    HashTable *bkdrhash = init(HASH_TABLE_SIZE, BKDR);
    HashTable *zobristhash = init(HASH_TABLE_SIZE, zobrist_hash);
    HashTable *MyHashx = init(HASH_TABLE_SIZE, MyHash);
    #define MAX_TEST_CNT 10000
    for(int i = 0; i < MAX_TEST_CNT; ++i) {
        char str[7] = {0};
        for (int j = 0; j < 6; ++j) {
            str[j] = rand() % 26 + 'a';
        }
        str[6] = 0;
        insert(aphash, str);
        insert(bkdrhash, str);
        insert(zobristhash, str);
        insert(MyHashx, str);
    }
    printf("aphash = %d\n", aphash->cnt);
    printf("bkdrhash = %d\n", bkdrhash->cnt);
    printf("zobristhash = %d\n", zobristhash->cnt);
    printf("MyHash = %d\n", MyHashx->cnt);
    #undef MAX_TEST_CNT
    clear(aphash);
    clear(bkdrhash);
    clear(zobristhash);
    clear(MyHashx);
    return 0;
}


/*
int main() {
    srand(time(0));
    char str1[50] = {0}, str2[50] = {0};
    for(int i = 0; i < 16; ++i) {
        str1[i] = (i & 1) ? 'a' : 'b';
    }
    for(int i = 0; i < 32; ++i) {
        str2[i] = (i & 1) ? 'a' : 'b';
    }
    printf("hash(%s) = %d\n", str1,BKDR(str1));
    printf("hashi(%s) = %d\n", str2,BKDR(str2));
    printf("aphash(%s) = %d\n", str1,APHash(str1));
    printf("aphashi(%s) = %d\n", str2,APHash(str2));
    printf("zorhash(%s) = %d\n", str1,zobrist_hash(str1));
    printf("zorhash(%s) = %d\n", str2,zobrist_hash(str2)); 
    return 0;
}*/


