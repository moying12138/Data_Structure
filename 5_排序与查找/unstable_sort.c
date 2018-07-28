/*************************************************************************
	> File Name: unstable_sort.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年07月28日 星期六 09时52分34秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define swap(a, b) {\
    __typeof(a) __temp = (a);\
    (a) = (b);\
    (b) = (__temp);\
}

#define TEST(n, func) { \
   int num[30] = {0}; \
    printf("["); \
    for(int i = 0; i < 30; ++i) { \
        num[i] = rand() % 100; \
        printf("%d ", num[i]); \
    } \
    printf("]\n"); \
    func; \
    output(num, n, #func);\
}
void select_sort(int *, int);
void quick_sort(int *, int , int );
void __quick_sort(int *, int, int);
void __quick_sort4(int *, int, int);
void output(int *, int, const char *);
int main() {
    srand(time(0));
    TEST(20, select_sort(num, 20));
    TEST(20, quick_sort(num, 0, 19));
    TEST(20, __quick_sort4(num, 0, 19));
    TEST(20, __quick_sort(num, 0, 19)); 
    return 0;
}

void output(int *num, int n, const char *str) {
    printf("%s = [", str);
    for(int i = 0; i < n; ++i) {
        printf("%d ", num[i]);
    }
    printf("]\n");
}
void select_sort(int *num, int n) {
    for(int i = 0; i < n - 1; ++i) {
        int ind = i;
        for(int j = i + 1; j < n; ++j) {
            if(num[j] < num[ind]) ind = i;
        }
        if(ind != i) swap(num[i], num[ind]);
    }
    return;
    
    
}
void quick_sort(int *num, int l, int r){        //原始的快速排序
    if(r - l < 1) return;
    int x = l, y = r, z = num[l];
    while(x < y) {
        while(x < y && num[y] >= z) --y;
        if(x < y) num[x++] = num[y];
        while(x < y && num[x] <= z) ++x;
        if(x < y) num[y--] = num[x];
    }
    num[x] = z;
    quick_sort(num, l, x - 1);
    quick_sort(num, x + 1, r); 
}
void ungarded_insert_sort(int *num, int n) { //优化的插入排序

    //printf("进入 %d\n", n);
    //output(num, n, "num");
    int ind = 0; 
    for(int i = 1; i < n; ++i)  {
        if(num[i] < num[ind]) ind = i;
    }
    swap(num[ind], num[0]);
    for(int i = 2; i < n; ++i) {
        int j = i;
        while(num[j] < num[j - 1]) {
            swap(num[j], num[j - 1]);
            j--;
        }
    }
    return ;
} 
void __quick_sort(int *num, int l, int r){  //最终的优化快排
    while(r - l >= 16) {
        int x = l, y = r, z = num[rand() % (r - l + 1) + l];
        do {
            while(num[x] < z) ++x;
            while(num[y] > z) --y;
            if(x <= y) {
                swap(num[x], num[y]);
                ++x, --y;
            }
        }while(x <= y);
        quick_sort(num, l, y);
        l = x;
    }
    ungarded_insert_sort(num + l, r - l + 1);
}
void __quick_sort4(int *num, int l, int r){   //第二次优化
    while(r - l >= 16) {
        int x = l, y = r, z = rand() % (r - l + 1) + l;
        swap(num[z],  num[l]);
        z = num[l];
        while(x < y) {
            while(x < y && num[y] >= z) y--;
            if(x < y) num[x++] = num[y];
            while(x < y && num[x] <= z) x++;
            if(x < y) num[y--] = num[x];
        }
        num[x] = z;
        quick_sort(num, l, x - 1);
        l = x + 1;
    }
    ungarded_insert_sort(num + l, r - l + 1);
}










