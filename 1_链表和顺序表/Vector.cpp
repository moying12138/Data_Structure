/*************************************************************************
	> File Name: vector.cpp
	> Author: moying 
	> Mail: 
	> Created Time: 2018年06月04日 星期一 19时58分02秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
typedef struct Vector {
    int size, length;
    int *data;
} Vector;
#define malloc2(size) my_malloc(size, __FILE__, __func__, __LINE__)

void *my_malloc(int size, const char *file, const char *func, int line_no) {
    void *data = malloc(size);
    if (data == NULL) {
        fprintf(stderr, "[%s : %s-> %d] malloc error\n", file, func, line_no);
        fflush(stderr);
        exit(-1);   
    }
    return data;
}
Vector* init(int n) {
    Vector *p = (Vector *)malloc2(sizeof(Vector));
    p->data = (int *) malloc(sizeof(int) * n);
    p->size = n;
    p->length = 0;
    return p;
}
int expand(Vector *v) {
    int new_size = v->size;
    int *data;
    while(new_size) {
        data = (int *)realloc(v->data, sizeof(int) * (v->size + new_size));
        if(data == NULL) {
            new_size /= 2;
            continue;
        }
        break;
    }
    if(new_size == 0) return 0;
    v->data = data;
    v->size += new_size;
    printf("vector expand\n");
    return 1;
}
//memcpy(data, v->data, sizeof(int) * v->length);
// v->data = data;
/*int expand(Vector *v){
    int *data = (int *)realloc(v->data, sizeof(int) * (v->size * 2));
    if(data == NULL) return 0;
    v->data = data;
    v->size *= 2;
    printf("Vector expand\n");
    return 1;
}*/

int insert(Vector *v, int x, int ind) {
    if(v->length >= v->size) {
        if(!expand(v)) {
            return 0;
        }
    }
    if(ind > v->length || ind < 0) {
        return 0;
    }
    for(int i = v->length - 1; i >= ind; i-- ) {
        v->data[i + 1] = v->data[i];
    }
    v->data[ind] = x;
    v->length++;
    return 1;
}
int delete_element(Vector *v, int ind) {
    if(ind >= v->length || ind < 0) {
        return 0;
    }
    for(int i = ind + 1; i < v->length; i++) {
        v->data[i - 1] = v->data[i];
    }
    v->length--;
    return 1;
}
void print(Vector *v) {
    printf("[");
    for(int i = 0; i < v->length; i++) {
        if(i > 0) printf(" ");
        printf("%d", v->data[i]);
    }
    printf("]\n");
    return ;
}
void clear(Vector *v) {
    if(v == NULL) return ;
    free(v->data);
    free(v);
}

int main() {
    srand(time(0));
    Vector *v = NULL;
    v = init(5);
    for(int i = 0; i < 10; i++) {
        int x, index;
        x = rand() % 100;
        index = rand() % (i + 3) - 1;
        int res = insert(v, x ,index);
        printf("insert(%d, %d)  == %d  ",x, index, res);
        print(v);
    }
    for(int i = 0; i < 5; ++i) {
        int ind = rand() % (v->length + 2) - 1;
        int ret = delete_element(v, ind);
        printf("%d : delete_element(%d) = %d", i + 1, ind, ret);
        print(v);
    }
    clear(v);
    return 0;
}

