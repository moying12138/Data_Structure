/*************************************************************************
	> File Name: 2_string_algorithm-2.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年08月04日 星期六 11时54分23秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LEN 100010
#define BASE 127
#define SIZE 30
#define TEST(func) {\
    printf("%s = %d\n", #func, func);\
}

void clear(int **d) {
    if(!d) return ;
    for(int i = 0; i < BASE; ++i) {
        free(d[i]);
    }
    free(d);
    return ;
}

int shift_and(const char *text, const char *pattern) {
    int len = strlen(pattern);
    int **d = (int **)malloc(sizeof(int *) * BASE);
    for(int i = 0; i < BASE; ++i) d[i] = calloc(sizeof(int), len / SIZE + 5);    //给每一个字符申请空间，长度为子串长度除去每位存的状态长度(默认30)
    int n = 0;
    for(; pattern[n]; ++n) {
        d[pattern[n]][n / SIZE] |= (1 << (n % SIZE));     
    }
    int *p = calloc(sizeof(int), len / SIZE + 5), count = len / SIZE + 1; //count从那一位开始操作
    for(int i = 0; text[i]; ++i) {
        for(int x = count; x >= 0 ; --x) {      //从count开始执行左移操作
            p[x] <<= 1;
            if(p[x] & (1 << SIZE)) p[x + 1] += 1, p[x] -= (1 << SIZE);   //如果x位超过当前默认长度，让父亲(高位)加1, 并移除超过的状态     
        }
        p[0] |= 1;            //有可能是第一位是匹配的               
        for(int x = count; x >= 0 ; --x) p[x] &= d[text[i]][x];    //从count开始执行匹配验证    
        if(p[(n - 1) / SIZE] & (1 << ((n - 1) % (SIZE)))) return 1;    //看是否全部匹配 。n - 1 / size是子串的最后一位所在的下标。验证之前是否全部匹配
    }
    clear(d);
    free(p);
    return 0;
}

int main() {
    char str[MAX_LEN];
    char pattern[MAX_LEN];
    scanf("%s%s", str, pattern);
    TEST(shift_and(str, pattern));
    return  0;
}
