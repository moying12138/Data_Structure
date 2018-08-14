/*************************************************************************
	> File Name: UnionSet.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年08月11日 星期六 11时30分39秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>

typedef struct UnionSet{
    int *data;
    int *rank;
    int n;
    int cnt;
}UnionSet;


UnionSet *init(int n) {
    UnionSet *p = (UnionSet *)malloc(sizeof(UnionSet));
    p->data = (int *)malloc(sizeof(int) * n);
    p->rank = (int *)malloc(sizeof(int) * n);
    p->n = p->cnt = n;
    for(int i = 0; i < n; ++i) {
        p->data[i] = i;
        p->rank[i] = 1;
    }
    return p;
}

void clear(UnionSet *p) {
    if(!p) return ;
    free(p->data);
    free(p->rank);
    free(p);
    return ;
}

int find(UnionSet *u, int n) {
    if(u->data[n] == n) return n;
    int father = find(u, u->data[n]);
    u->data[n] = father;
    return father;
}

int merge(UnionSet *u, int a, int b) {
    int father_a = find(u, a);
    int father_b = find(u, b);
    if(father_a == father_b)  return 0;
    if(u->rank[father_a] > u->rank[father_b]) {
        u->data[father_b] = father_a;
        u->rank[father_a] += u->rank[father_b];
        
    } else {
        u->data[father_a] = father_b;
        u->rank[father_b] += u->rank[father_a];
    }
    u->cnt--;
    return 1;
}




int main() {
    srand(time(0));
    UnionSet *u = init(10);
    #define OP_NUM 20
    for(int i = 0; i < OP_NUM; ++i) {
        int a = rand() % 10, b = rand() % 10;
        printf("union %d with %d = %d\n", a, b, merge(u, a, b));
        printf("UnionSet cnt = %d\n", u->cnt);
    }
    clear(u);
    
    return 0;
}
