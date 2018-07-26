/*************************************************************************
	> File Name: heap.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年07月23日 星期一 17时20分09秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
typedef struct Heap{
    int *data;
    int n, size;
}Heap;

Heap *init(int );
void clear(Heap *);
void push(Heap *, int );
void pop(Heap *);
void output(Heap *);

int main() {
    srand(0);
    Heap *h = init(21);
    for(int i = 0; i < 20; ++i) {
        int value = rand() % 100;
        printf("insert %d to Heap\n", value);
        push(h, value);
        output(h);
    }
    for(int i = 0; i < 20; ++i) {
        pop(h);
        output(h);
    }
    clear(h);
    return 0;
}

Heap *init(int n) {
    Heap *p = (Heap *)malloc(sizeof(Heap));
    p->data = (int * )malloc(sizeof(int) * n);
    memset(p->data, 0, sizeof(int) * n);
    p->n = 0;
    p->size = n;
    return p;
}

void clear(Heap *p) {
    if(p == NULL) return ;
    free(p->data);
    free(p);
    return ;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void push(Heap *h, int value) {
    if(h->n ==  h->size) return;
    h->n++;
    h->data[h->n] = value;
    int i = h->n;
    while(i > 1) {
        if(h->data[i] <= h->data[i >> 1]) break;
        h->data[i] ^= h->data[i >> 1];
        h->data[i >> 1] ^= h->data[i];
        h->data[i] ^= h->data[i >> 1];
        i >>= 1;
    }
}

void pop(Heap *h) {
    if(h->n <= 1) {
        h->n = 0;
        return;
    }
    h->data[1] ^= h->data[h->n];
    h->data[h->n] ^= h->data[1];
    h->data[1] ^= h->data[h->n];
    h->n--;
    int ind = 1;
    while(ind * 2 < h->n) {
        int swap_ind = ind;
        if(h->data[ind * 2] > h->data[swap_ind]) swap_ind = ind * 2;
        if(ind * 2 + 1 <= h->n && h->data[ind * 2 + 1] > h->data[swap_ind]) swap_ind = ind * 2 + 1;
        if(swap_ind == ind) break;
        swap(&h->data[swap_ind], &h->data[ind]);
        ind = swap_ind;
    }
    return ;
}


void output(Heap *h) {
    printf("Heap = [ ");
    for(int i = 0; i < h->size; ++i) {
        printf("%d ", h->data[i]);
    }
    printf("]\n");
}
