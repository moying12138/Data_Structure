/*************************************************************************
	> File Name: 2_string_algorithm-2.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年08月04日 星期六 11时54分23秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>


#define TEST(func) {\
    printf("%s = %d\n", #func, func);\
}


int sunday(const char *text, const char *pattern) {
    int len = strlen(pattern), len2 = strlen(text);
    int ind[128] = {0};
    for(int i = 0; i < 127; ++i) ind[i] = len + 1;
    for(int i = 0; pattern[i]; ++i) ind[pattern[i]] = len - i;
    for(int i = 0; i <= len2 - len + 1; ) {
        int j = 0;
        for(; j < len; ++j) {
            if(pattern[j] != text[i + j])break;
        }
        if(j == len) return 1;
        i += ind[text[i + len]];
    }
    return 0;
    
}

int shift_and(const char *text, const char *pattern) {
    int d[127] = {0}, n = 0;
    for(; pattern[n]; ++n) {
        d[pattern[n]] |= (1 << n);
    }
    int p = 0;
    for(int i = 0; text[i]; ++i) {
        p = (p << 1 | 1) & d[text[i]];
        if(p & (1 << (n - 1))) return 1;
    }
    return 0;
}






int main() {
    TEST(sunday("hello world", "wor"));
    TEST(shift_and("hello world", "wor"));
    TEST(sunday("hello world", "wr"));
    TEST(shift_and("hello world", "wr")); 
    return  0;
}
