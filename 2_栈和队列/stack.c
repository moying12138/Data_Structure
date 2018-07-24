/*************************************************************************
	> File Name: stack.c
	> Author: moying
	> Mail: 
	> Created Time: 2018年07月19日 星期四 11时05分41秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define data_type int
#define NULL_VALUE 0
#define f(a) ((int)(log10(a)) + 1)
typedef struct stack {
    data_type *data;
    int  top, size;
}Stack;
Stack *init(int );
void clear(Stack *);
data_type top(Stack *);
int push(Stack *, data_type );
int pop(Stack *);
int empty(Stack *);
void output(Stack *s);

int main() {
    srand(time(0));
    Stack *s = (init(100));
    for(int i = 0; i < 20; ++i) {
        int op = rand() % 2, value = rand() % 100;
        switch(op) {
            case 0:
                printf("push element = %d\n", value);
                push(s, value);
                output(s);
                break;
            case 1:
                printf("pop element from Stack\n");
                pop(s);
                output(s);
                break;
            default:
                fprintf(stderr, "error operator = %d\n", op);
                break;
        }        
    }
    return 0;
}
void output1(Stack *s, int sign) {
    for(int i = 0; i < sign; ++i) {
        printf(" ");
    }
    for(int i = 0; i < s->top; ++i) {
        printf(" ");
        for(int j = 0; j < f(s->data[j]); ++j) {
            printf(" ");
        }
    }
}
void output(Stack *s) {
    if(s == NULL) return;
    printf("[ ");
    for(int i = 0; i <= s->top; ++i) {
        printf("%d,", s->data[i]);
    }
    printf(" ]\n");
    if(empty(s)) return ;
    output1(s, 2);
    printf("^\n");
    output1(s, 2);
    printf("|\n");
    output1(s, 1);
    printf("top\n");

    
}

Stack *init(int n) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->data = (data_type *) malloc(sizeof(data_type) * n);
    s->top = -1;
    s->size = n;
    return s;
}

void clear(Stack *s) {
    if(s == NULL) return ;
    free(s->data);
    free(s);
}

data_type top(Stack *s) {
    if(empty(s)) return NULL_VALUE;
    return s->data[s->top];
}

int push(Stack *s, data_type value) {
    if(s->top + 1 == s->size) return 0;
    s->data[++s->top] = value;
    return 1;
}

int pop(Stack *s) {
    if(empty(s)) return 0;
    s->top--;
    return 1;
}

int empty(Stack *s) {
    return s->top == -1;
}
