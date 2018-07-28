/*************************************************************************
	> File Name: raddix_sort.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年07月28日 星期六 11时48分51秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MY_NUM_MAX 0x3f3f3f3f
#define MY_NUM 17191 
#define TEST(n, func) { \
   int num[30] = {0}; \
    printf("["); \
    for(int i = 0; i < 30; ++i) { \
        num[i] = rand() % 100000; \
        printf("%d ", num[i]); \
    } \
    printf("]\n"); \
    func; \
    output(num, n, #func);\
}
#define lowbit(x) (x & 0xffff)
#define heightbit(x) ((x >> 16) & 0xffff)


void raddix_sort(int *num, int n);
void output(int *num, int n, const char *str) {
    printf("%s = [", str);
    for(int i = 0; i < n; ++i) {
        printf("%d ", num[i]);
    }
    printf("]\n");
}
int main() {
    //printf("%d\n", 0xffff);
    TEST(20, raddix_sort(num, 20));
    return 0;
}

void raddix_sort(int *num, int n) {    //排完低八位，排高八位，从后往前赋值数组，保证了稳定性
    #define MAX_N 65536
    int *temp = (int *)malloc(sizeof(int) * n);
    int cnt[MAX_N] = {0};
    for(int i = 0; i < n ;++i)  cnt[lowbit(num[i])]++;
    for(int i = 1; i < MAX_N; ++i) cnt[i] += cnt[i - 1];   
    for(int i = n -1; i >= 0; i--) 
        temp[--cnt[lowbit(num[i])]] = num[i];
     
   memset(cnt, 0, sizeof(int) * MAX_N); 
    for(int i = 0; i < n ;++i) cnt[heightbit(temp[i])]++;
    for(int i = 1; i < MAX_N; ++i) cnt[i] += cnt[i - 1];
    for(int i = n -1; i >= 0; i--) 
        num[--cnt[heightbit(temp[i])]] = temp[i];
    free(temp);
}


