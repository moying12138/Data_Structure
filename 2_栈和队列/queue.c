/*************************************************************************
	> File Name: queue.c
	> Author: moying
	> Mail: 
	> Created Time: 2018年07月19日 星期四 09时55分15秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define data_type int
#define NULL_VALUE 0

typedef struct Queue {
    data_type *data;
    int length, tail, head, size;
}Queue;


Queue *init(int );
data_type front(Queue  *);
int push(Queue *, data_type );
int pop(Queue *);
int empty(Queue *);
void output(Queue *);
void clear(Queue *);

Queue *init(int size) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (data_type *)malloc(sizeof(data_type) * size);
    q->length = 0;
    q->size = size;
    q->head = 0;
    q->tail = -1;
    return  q;
}

int push(Queue *q, data_type value) {
    if(q->length ==  q->size) return 0;
    q->data[(++q->tail) % q->size] = value;
    q->length++;
    return 1;
}

int pop(Queue *q) {
    if(empty(q)) return 0;
    q->length--;
    q->head = (q->head + 1) % q->size;
}

int empty(Queue *q) {
    return q->length == 0;
}

data_type front(Queue *q) {
    if(empty(q)) return NULL_VALUE;
    return q->data[0];
}

void output(Queue *q) {
    if(empty(q)) {
        printf("[]\n");
        return ;
    }
    printf("[ ");
    for(int i = 0, head = q->head; i < q->length; ++i, head = (head + 1) %q->size) {
        printf("%d ", q->data[head]);
    }
    printf("]\n");
    return ;
}
void clear(Queue *q) {
    if(q == NULL) return ;
    free(q->data);
    free(q);
}

int main() {
    srand((time(0)));
    Queue *q = init(10);
    for(int i = 0; i < 20; ++i) {
        int op = rand() % 2, value = rand() % 100;
        if(op == 1) {
            printf("insert %d to queue\n", value);
            push(q, value);
            output(q);
        } else{
            printf("pop element from queue \n");
            pop(q);
            output(q);
        }
    }
    clear(q);
    return 0;
}
