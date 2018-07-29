/*************************************************************************
	> File Name: hash_table.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年07月28日 星期六 16时04分42秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
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

int BKDR(const char *str) {
    int hash = 0, seed = 3;
    for(int i = 0; str[i]; ++i) {
        hash = hash * seed + str[i];
    }
    return hash & 0x7fffffff;
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
}


